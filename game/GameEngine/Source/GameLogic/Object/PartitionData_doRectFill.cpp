// cl: /O2 /DNDEBUG /MD /EHs-c- /Ob2

#include "../../../Include/Common/ScalarTypes.h"


Int g_Va0133F408 = 0;
extern const Real g_bfmeK1253;
extern const Real g_bfmeK1266B;
extern const Real g_rva003D2B80NegHalf;
extern "C" Real __cdecl cosf(Real angle);
extern "C" Real __cdecl sinf(Real angle);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

// ?bfmeFloatToIntRectFill@@YAHM@Z absent-from-retail
__forceinline Int bfmeFloatToIntRectFill(Real value)
{
	Int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class CellAndObjectIntersection;

class BfmeCellFD
{
public:
	CellAndObjectIntersection *m_first;
	Int m_data[25];
};

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(Real x, Real y) const;

	unsigned char m_prefix[0x1c];
	Real m_cellSize;
	Real m_scale;
};

class CellAndObjectIntersection
{
public:
	BfmeCellFD *m_cell;
	void *m_partitionData;
	CellAndObjectIntersection **m_previous;
	CellAndObjectIntersection *m_next;
};

class PartitionData
{
private:
	bool doRectFill(Real centerX, Real centerY, Real halfsizeX,
		Real halfsizeY, Real angle);

	Gen_008F7CD0 *m_grid;
	unsigned char m_prefix[0x18];
	CellAndObjectIntersection *m_coiArray;
};

// ?doRectFill@PartitionData@@AAE_NMMMMM@Z
// Open BFME 2: Code/GameEngine/Source/Common/BfmeThingCDEDestructor.cpp
bool PartitionData::doRectFill(float centerX,float centerY,float halfsizeX,float halfsizeY,float angle)
{
 float c=cosf(angle);
 float s=sinf(angle);
 float xdx=c*m_grid->m_cellSize*0.5f;
 float xdy=s*m_grid->m_cellSize*0.5f;
 float ydx=s*m_grid->m_cellSize*0.5f;
 float ydy=c*m_grid->m_cellSize*-0.5f;
 float scaleX=m_grid->m_scale;
 int numStepsX=bfmeFloatToIntRectFill((float)ceil((double)(scaleX*halfsizeX*4.0f)));
 float scaleY=m_grid->m_scale;
 int numStepsY=bfmeFloatToIntRectFill((float)ceil((double)(scaleY*halfsizeY*4.0f)));
 CellAndObjectIntersection *coi=(CellAndObjectIntersection*)m_coiArray;
 ++g_Va0133F408;
 float tl_x=centerX-halfsizeX*c-halfsizeY*s;
 float tl_y=centerY+halfsizeY*c-halfsizeX*s;
 for(int iy=0;iy<numStepsY;++iy,tl_x+=ydx,tl_y+=ydy)
 {
  float sampleX=tl_x,sampleY=tl_y;
  for(int ix=0;ix<numStepsX;++ix,sampleX+=xdx,sampleY+=xdy)
  {
   BfmeCellFD *cell=m_grid->bfmeAt(sampleX,sampleY);
   if(cell && g_Va0133F408!=cell->m_data[24])
   {
    cell->m_data[24]=g_Va0133F408;
    coi->m_cell=cell;
    CellAndObjectIntersection *next=cell->m_first;
    coi->m_next=next;
    if(next)next->m_previous=&coi->m_next;
    coi->m_previous=(CellAndObjectIntersection**)cell;
    cell->m_first=coi;
    ++coi;
   }
  }
 }
 return true;
}
