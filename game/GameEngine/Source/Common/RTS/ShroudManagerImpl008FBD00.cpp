// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stlp_nodealloc
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <deque>

#include "../../../Include/Common/ScalarTypes.h"



#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/Enums/ValueOrThreat.h"





struct Gen_t_008fbc70_p8cd
{
	Int a[2];
};

class Rva008FA150Owner { public: void initialize(unsigned int); };
namespace _STL {
typedef Gen_t_008fbc70_p8cd Type;
// ??1?$vector@_NV?$allocator@_N@_STL@@@_STL@@QAE@XZ
template<> __forceinline vector<bool>::~vector() {}
template<> vector<bool>::vector(unsigned int,bool,const allocator<bool>&);
template<> void deque<Type>::push_back(const Type&);
// ?_M_initialize_map@?$_Deque_base@UGen_t_008fbc70_p8cd@@V?$allocator@UGen_t_008fbc70_p8cd@@@_STL@@@_STL@@IAEXI@Z absent-from-retail
template<> __forceinline void _Deque_base<Type,allocator<Type> >::_M_initialize_map(unsigned int n) {
    ((Rva008FA150Owner*)this)->initialize(n);
}
template<> deque<Type>::~deque();
}

// ?pushXY@@YAXAAV?$deque@UGen_t_008fbc70_p8cd@@V?$allocator@UGen_t_008fbc70_p8cd@@@_STL@@@_STL@@II@Z absent-from-retail
template <class Type>
static __forceinline void pushXY(_STL::deque<Type>& q,unsigned x,unsigned y) { Type p; p.a[0]=x; p.a[1]=y; q.push_back(p); }

class Gen_008F7CD0
{
public:
	Int bfmeCellX(Real value) const;
	Int bfmeCellY(Real value) const;
};

struct ShroudManagerImpl008FBA40Element
{
	void *cellNodes;
	unsigned short playerStates[16][3];
	Int unknown64;
};

class ShroudManagerImpl008FBA40
{
public:
	bool rva008FBD00(const Coord3D *sourceLocation,
		UnsignedInt allowedPlayers, ValueOrThreat valueType,
		Int valueRequired, Coord3D *outLocation);

private:
	Int mode;
	char region[24];
	Real defaultCellSize;
	Real inverseCellSize;
	UnsignedInt width;
	UnsignedInt height;
	ShroudManagerImpl008FBA40Element *elements;
};

// ?rva008FBD00@ShroudManagerImpl008FBA40@@QAE_NPBUCoord3D@@IW4ValueOrThreat@@HPAU2@@Z
// Open BFME 2: Code/GameEngine/Source/Common/RTS/ShroudManagerImplGetNearestGroupWithValue.cpp
bool ShroudManagerImpl008FBA40::rva008FBD00(const Coord3D* sourceLocation,UnsignedInt allowedPlayers,ValueOrThreat valueType,Int valueRequired,Coord3D* outLocation)
{
 if(!allowedPlayers || valueType<0 || valueType>=2)return false;
 allowedPlayers&=0xffff;
 int cellX=((const Gen_008F7CD0*)this)->bfmeCellX(sourceLocation->x);
 int cellY=((const Gen_008F7CD0*)this)->bfmeCellY(sourceLocation->y);
 if(cellX<0)cellX=0;else if(cellX>=(int)width)cellX=width-1;
 if(cellY<0)cellY=0;else if(cellY>=(int)height)cellY=height-1;
 _STL::vector<bool> bitField(width*height,false);
 const _STL::vector<bool>& tested=bitField;
 _STL::deque<Gen_t_008fbc70_p8cd,_STL::allocator<Gen_t_008fbc70_p8cd> > queue;
 { Gen_t_008fbc70_p8cd initial={{cellX,cellY}};queue.push_back(initial); }
 while(!queue.empty()) {
  unsigned x=queue.front().a[0], y=queue.front().a[1];
  unsigned cell=y*width+x;
  queue.pop_front();
  if(x>0 && !tested[cell-1]) { bitField[cell-1]=true;Gen_t_008fbc70_p8cd p={{x-1,y}};queue.push_back(p); }
  if(x<width-1 && !tested[cell+1]) { bitField[cell+1]=true;Gen_t_008fbc70_p8cd p={{x+1,y}};queue.push_back(p); }
  if(y>0 && !tested[cell-width]) { bitField[cell-width]=true;unsigned ny=y-1;pushXY(queue,x,ny); }
  if(y<height-1 && !tested[cell+width]) { bitField[cell+width]=true;unsigned ny=y+1;pushXY(queue,x,ny); }
  ShroudManagerImpl008FBA40Element *element=&elements[cell];
  unsigned value=0;
  unsigned bits=allowedPlayers;
  if(bits) { unsigned short *word=&element->playerStates[0][valueType+1];do { if(bits&1)value+=*word;bits>>=1;word+=3; } while(bits); }
  if(value>=(UnsignedInt)valueRequired) { outLocation->x=(cell%width)*defaultCellSize;outLocation->y=(cell/width)*defaultCellSize;*(int*)&outLocation->z=0;return true; }
 }
 return false;
}
