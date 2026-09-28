// ?validateEndpoint003E2140@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@1@Z
// partial score=0.663 date=2026-09-28
// cl: /DNDEBUG /MD /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing
// RVA 003E2140: compare endpoint cells/layers then validate the destination.
// Address retained: no independently established semantic method identity.
#include "PreRTS.h"
float __cdecl floor(float);
#define CELL_FLOOR(x) fast_float2long_round(floor((float)(x)))
struct Coord3D { float x,y,z; };
struct ICoord2D { int x,y; };
enum PathfindLayerEnum { LAYER_INVALID=0 };
class Overridable { public: const Overridable *getFinalOverride() const; int m_00; const Overridable *m_nextOverride; };
class Override2140 { public: int m_00; const Overridable *m_override; char pad08[0xc8-8]; unsigned m_c8; char padcc[0xd4-0xcc]; unsigned m_flagsD4; char padd8[0x408-0xd8]; float m_level;
 Override2140 *finalOverride() { return m_override?(Override2140 *)m_override->getFinalOverride():this; }
};
class AIUpdateInterface { public: int getIgnoredObstacleID(); char pad00[0x1b8]; unsigned m_1b8; };
// Canonical Object layout has m_ai at +0x204 and a byte m_privateStatus
// at +0x344 (object.h BFME_LAYOUT_CHECK), replacing the bank's partial view.
#define OBJECT_TU_MEMBERS bool bfmeIsComputerControlled() const;
#include "object.h"
class Rva003DB4C0 { public: bool field() const; };
class Rva003DB4F0 { public: int value() const; };
class PathfindCell { public: char pad00[12]; unsigned m_word;
 int layer() const { return (m_word>>6)&63; }
 int type() const { return m_word&7; }
};
class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *); };
extern TerrainLogic *TheTerrainLogic;
bool __cdecl rva3d5150(int);
bool __cdecl rva3d5170(int);
struct Movement2140 { unsigned m_surfaces; unsigned char m_field04,m_allowAircraftGoal; int m_maxLayer; };
class Pathfinder { public:
 void bfmeQuery(Object *,int *,unsigned char *);
 bool validateEndpoint003E2140(Object *,const Coord3D *,const Coord3D *);
protected:
 void getRadiusAndCenter(const Object *,int &,bool &);
public:
 PathfindCell *bfmeGetCellByIndicesTwin(PathfindLayerEnum,int,int);
 bool bfmeStepD4F90(void *,PathfindCell *);
 char pad00[0x844]; int m_ignoreObstacleID;
};
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern const Real g_pathfindCellSize, g_pathfindDoubleCellSize, g_pathfindLevelLimit, g_pathfindCellCenterBias;
__declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
{
	Real diameter;
	Int maxRadius = 2;
	Override2140 *t1 = ((Override2140 *)object->m_template);
	if ((t1 == 0 ? t1 : t1->finalOverride())->m_c8 & 0x400) {
		maxRadius = 4;
	} else {
		Override2140 *t2 = ((Override2140 *)object->m_template);
		if ((t2 == 0 ? t2 : t2->finalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = (*(const float *)((const char *)object+0xbc)) * 2.0f;
	if (diameter > g_pathfindCellSize && diameter < g_pathfindDoubleCellSize) {
		diameter = 20.0f;
	}

	if ((((Override2140 *)object->m_template) == 0 ? ((Override2140 *)object->m_template) :
		((Override2140 *)object->m_template)->finalOverride())->m_level > g_pathfindLevelLimit) {
		diameter = (((Override2140 *)object->m_template) == 0 ? ((Override2140 *)object->m_template) :
		((Override2140 *)object->m_template)->finalOverride())->m_level;
	}

	radius = fast_float2long_round((Real)floor((double)(diameter / 10.0f + g_pathfindCellCenterBias)));
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

bool Pathfinder::validateEndpoint003E2140(Object *obj,const Coord3D *from,const Coord3D *to)
{
 if(obj->m_privateStatus&1) return true;
 Override2140 *data=(Override2140 *)obj->m_template;
 if(data && data->m_override) data=(Override2140 *)data->m_override->getFinalOverride();
 if(data->m_c8&4) return true;
 if(!*((unsigned char *)this+8)) return true;
 AIUpdateInterface *ai=obj->m_ai;
 if(!ai) { yesEarly: return true; }
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
 if(!a || !b || a->layer()!=fromLayer || b->layer()!=toLayer) return false;
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
 bool result=bfmeStepD4F90(&info,b);
 m_ignoreObstacleID=saved;
 return result;
 }
}
