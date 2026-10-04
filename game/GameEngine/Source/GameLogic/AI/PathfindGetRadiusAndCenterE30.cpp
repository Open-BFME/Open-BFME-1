// cl: /DNDEBUG /MD
// readable body of ?getRadiusAndCenter@Pathfinder@@IAEXPBVObject@@AAHAA_N@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
//
// Retail 0x003DEE30: Pathfinder::getRadiusAndCenter.
// The BFME fork keeps the Zero Hour radius calculation but selects the
// permitted radius from the object's template flags and stores the output
// through the two reference arguments.

typedef int Int;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl floor( double );

__forceinline long fast_float2long_round( float value )
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

extern const float g_bfmeDirectionWeight1285;
extern const float g_Rva010977E0;
extern const float g_rva01075350;
extern float g_Rva01095F98;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride( void );

	BfmeOverridable *getFinalOverride( void )
	{
		if (m_override == 0) return this;
		return m_override->friend_getFinalOverride();
	}

	Int m_unknown00;
	BfmeOverridable *m_override;
	unsigned char m_pad08[0xc8 - 0x08];
	Int m_flagsC8;
	unsigned char m_padCC[0xd4 - 0xcc];
	Int m_flagsD4;
	unsigned char m_padD8[0x408 - 0xd8];
	Real m_level;
};

class AIUpdateInterface
{
public:
	Int getIgnoredObstacleID( void );
	char pad00[0x1b8];
	unsigned m_1b8;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Int m_unknown00;
	BfmeOverridable *m_template;
	unsigned char m_pad08[0xbc - 0x08];
	Real m_boundingCircleRadius;
	unsigned char m_padC0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x344 - 0x208];
	unsigned char m_privateStatus;

	BfmeOverridable *getTemplate( void ) const { return m_template; }
	Bool bfmeIsComputerControlled( void ) const;
};

struct Coord3D { float x,y,z; };
struct ICoord2D { int x,y; };
enum PathfindLayerEnum { LAYER_INVALID=0 };

class Overridable { public: const Overridable *getFinalOverride() const; int m_00; const Overridable *m_nextOverride; };
// ?finalOverride@Override2140@@QAEPAV1@XZ absent-from-retail
class Override2140 { public: int m_00; const Overridable *m_override; char pad08[0xc8-8]; unsigned m_c8; char padcc[0xd4-0xcc]; unsigned m_flagsD4; char padd8[0x408-0xd8]; float m_level;
 Override2140 *finalOverride() { return m_override?(Override2140 *)m_override->getFinalOverride():this; }
};

class Rva003DB4C0 { public: bool field() const; };
class Rva003DB4F0 { public: int value() const; };

// ?layer@PathfindCell@@QBEHXZ absent-from-retail
// ?type@PathfindCell@@QBEHXZ absent-from-retail
class PathfindCell { public: char pad00[12]; unsigned m_word;
 int layer() const { return (m_word>>6)&63; }
 int type() const { return m_word&7; }
};

class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *); };
extern TerrainLogic *TheTerrainLogic;
bool __cdecl rva3d5150(int);
bool __cdecl rva3d5170(int);
float __cdecl floor(float);
#define CELL_FLOOR(x) fast_float2long_round(floor((float)(x)))

struct Movement2140 { unsigned m_surfaces; unsigned char m_field04,m_allowAircraftGoal; int m_maxLayer; };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void bfmeQuery( Object *object, Int *radius, unsigned char *centerInCell );
	Bool validateEndpoint003E2140( Object *obj, const Coord3D *from, const Coord3D *to );
	PathfindCell *bfmeGetCellByIndicesTwin( PathfindLayerEnum layer, Int x, Int y );
	Bool bfmeStepD4F90( void *movementInfo, PathfindCell *cell );

protected:
	void getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell );

public:
	char pad00[0x844];
	Int m_ignoreObstacleID;						// +0x844
};

inline __declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
{
	Real diameter;
	Int maxRadius = 2;
	BfmeOverridable *t1 = object->getTemplate();
	if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		BfmeOverridable *t2 = object->getTemplate();
		if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = object->m_boundingCircleRadius * 2.0f;
	if (diameter > g_bfmeDirectionWeight1285 && diameter < g_Rva010977E0) {
		diameter = 20.0f;
	}

	if ((object->getTemplate() == 0 ? object->getTemplate() :
		object->getTemplate()->getFinalOverride())->m_level > g_rva01075350) {
		diameter = (object->getTemplate() == 0 ? object->getTemplate() :
		object->getTemplate()->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_Rva01095F98 );
	centerInCell = false;
	if (radius == 0) radius++;
	if (radius & 1) {
		centerInCell = true;
	}
	radius /= 2;
	if (radius > maxRadius) {
		radius = maxRadius;
		centerInCell = true;
	}
}

// Retail 0x003E2140: compares the endpoint cells and layers of a move, then validates
// the destination cell with the object's AI ignore-obstacle ID swapped in.
Bool Pathfinder::validateEndpoint003E2140(Object *obj,const Coord3D *from,const Coord3D *to)
{
 if(obj->m_privateStatus&1) {
  return true;
 }
 else {
 Override2140 *data=(Override2140 *)obj->m_template;
 if(data && data->m_override) data=(Override2140 *)data->m_override->getFinalOverride();
 if(data->m_c8&4) return true;
 if(!*((unsigned char *)this+8)) return true;
 AIUpdateInterface *ai=obj->m_ai;
 if(ai==0) return true;
 PathfindCell *b;
 {
 ICoord2D fromCell;
 ICoord2D toCell;
 bool centerInCell;
 getRadiusAndCenter(obj,toCell.x,centerInCell);
 if(centerInCell) {
  fromCell.x=CELL_FLOOR(from->x*0.1f); fromCell.y=CELL_FLOOR(from->y*0.1f);
  toCell.x=CELL_FLOOR(to->x*0.1f); toCell.y=CELL_FLOOR(to->y*0.1f);
 } else {
  fromCell.x=CELL_FLOOR(from->x*0.1f+0.5f); fromCell.y=CELL_FLOOR(from->y*0.1f+0.5f);
  toCell.x=CELL_FLOOR(to->x*0.1f+0.5f); toCell.y=CELL_FLOOR(to->y*0.1f+0.5f);
 }
 PathfindLayerEnum fromLayer=TheTerrainLogic->getLayerForDestination(obj,from);
 PathfindLayerEnum toLayer=TheTerrainLogic->getLayerForDestination(obj,to);
 if(fromCell.x==toCell.x && fromCell.y==toCell.y && fromLayer==toLayer) return true;
 PathfindCell *a=bfmeGetCellByIndicesTwin(fromLayer,fromCell.x,fromCell.y);
 b=bfmeGetCellByIndicesTwin(toLayer,toCell.x,toCell.y);
 if(!a) return false;
 if(!b) return false;
 if(a->layer()!=fromLayer) return false;
 if(b->layer()!=toLayer) return false;
 if(fromLayer==toLayer) { if(a->type()==b->type()) return true; }
 else {
  if(!rva3d5150(toLayer)) {
   if(toLayer==16) goto validate;
   if(!rva3d5170(toLayer) && toLayer!=1) return false;
  }
  if(fromLayer!=16) return false;
 }
 }
 validate:
 {
 int saved=m_ignoreObstacleID;
 m_ignoreObstacleID=ai->getIgnoredObstacleID();
 Movement2140 info;
 AIUpdateInterface *curAI=obj->m_ai;
 unsigned char computer=obj->bfmeIsComputerControlled();
 info.m_surfaces=curAI->m_1b8;
 info.m_field04=!((Rva003DB4C0 *)obj)->field();
 info.m_allowAircraftGoal=computer;
 info.m_maxLayer=((Rva003DB4F0 *)obj)->value()-1;
 bool result=bfmeStepD4F90(&info,b)!=0;
 m_ignoreObstacleID=saved;
 return result;
 }
 }
}
