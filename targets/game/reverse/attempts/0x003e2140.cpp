// ?d_003e2140@@YAXXZ
// partial score=0.3 date=2026-09-27
// cl: /DNDEBUG /MD /Igame/GameEngine/Include/Precompiled
// RVA 003E2140: compare endpoint cells/layers then validate the destination.
// Address retained: no independently established semantic method identity.
#include "PreRTS.h"
float __cdecl floor(float);
#define CELL_FLOOR(x) fast_float2long_round(floor((float)(x)))
struct Coord3D { float x,y,z; };
struct ICoord2D { int x,y; };
enum PathfindLayerEnum { LAYER_INVALID=0 };
class BfmeSubBIA { public: int ask(); };
class Override2140 { public: int m_00; BfmeSubBIA *m_override; char pad08[0xc8-8]; unsigned m_c8;
 Override2140 *finalOverride() { return m_override?(Override2140 *)m_override->ask():this; }
};
class AIUpdateInterface { public: int getIgnoredObstacleID(); char pad00[0x1b8]; unsigned m_1b8; };
class Object { public:
 bool bfmeIsComputerControlled() const;
 int m_00; Override2140 *m_template; char pad08[0x204-8]; AIUpdateInterface *m_ai204;
 char pad208[0x344-0x208]; unsigned m_privateStatus;
};
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
bool Pathfinder::validateEndpoint003E2140(Object *obj,const Coord3D *from,const Coord3D *to)
{
 if(obj->m_privateStatus&1) return true;
 Override2140 *data=obj->m_template;
 if(data && data->m_override) data=(Override2140 *)data->m_override->ask();
 if(data->m_c8&4) return true;
 if(!*((unsigned char *)this+8)) return true;
 AIUpdateInterface *ai=obj->m_ai204;
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
 AIUpdateInterface *curAI=obj->m_ai204;
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
