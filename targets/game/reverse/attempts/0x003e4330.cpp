// ?d_003e4330@@YAXXZ
// partial score=0.14 date=2026-09-27
// cl: /DNDEBUG /MD /Igame/GameEngine/Include/Precompiled
// RVA 003E4330: matched bfmeCheckAttackViewAlt forwards to this established
// helper name. Behavior: collect up to 16 unique occupying goal IDs.
// Complete terminal ret 0x0c ends at RVA 003E45D6: 678 bytes, not dump's 672.
#include "PreRTS.h"
#define CELL_FLOOR(x) fast_float2long_round((float)floor((double)(x)))
struct Coord3D { float x,y,z; };
struct ICoord2D { int x,y; };
class Object { public: char pad00[0x74]; int m_id; };
class BfmeHolderNS { public: int bfmeQueryNS(); };
class PathfindCellInfo { public: char pad00[0x18]; int m_goalUnitID; };
class PathfindCell { public: PathfindCellInfo *m_info; char pad04[12]; };
class PathfindLayer { public: PathfindCell *getCell(int,int); char pad00[0x44]; };
struct Rva003E4330Terrain {
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual bool slotA4(Object *,int);
};
extern Rva003E4330Terrain *g_rva012EF4CC;
class Pathfinder {
public:
 void bfmeQuery(Object *,int *,unsigned char *);
protected:
 void getRadiusAndCenter(const Object *,int &,bool &);
public:
 int bfmeCheckAttackViewAltHelper(Object *,Coord3D *,void *);
 char pad00[0x10]; PathfindCell **m_map;
 struct { ICoord2D lo,hi; } m_extent;
 char pad24[0x85c-0x24]; PathfindLayer m_layers[16];
 __forceinline PathfindCell *getCell(int layer,int x,int y) {
  if (x>=m_extent.lo.x && x<=m_extent.hi.x && y>=m_extent.lo.y && y<=m_extent.hi.y) {
   if (layer>1 && layer<=15) { PathfindCell *cell=m_layers[layer].getCell(x,y); if (cell) return cell; }
   return &m_map[x][y];
  } return 0;
 }
};
int Pathfinder::bfmeCheckAttackViewAltHelper(Object *obj,Coord3D *pos,void *output)
{
 int radius; bool centerInCell;
 getRadiusAndCenter(obj,radius,centerInCell);
 int minRadius=radius;
 int maxRadius=radius;
 int cellX,cellY;
 if (centerInCell) {
  ++maxRadius;
  cellX=CELL_FLOOR(pos->x*0.1f);
  cellY=CELL_FLOOR(pos->y*0.1f);
 } else {
  cellX=CELL_FLOOR(pos->x*0.1f+0.5f);
  cellY=CELL_FLOOR(pos->y*0.1f+0.5f);
 }
 bool checkGround=false; centerInCell=false; bool &checkLayer=centerInCell;
 int layer=((BfmeHolderNS *)obj)->bfmeQueryNS();
 if (layer!=1 && layer<16) {
  checkLayer=true;
  if (g_rva012EF4CC->slotA4(obj,layer)) checkGround=true;
 } else checkGround=true;
 int count=0;
 int *ids=(int *)output;
 for(int x=cellX-minRadius;x<cellX+maxRadius;++x) {
  for(int y=cellY-minRadius;y<cellY+maxRadius;++y) {
   if(checkLayer) {
    PathfindCell *cell=getCell(layer,x,y);
    if (cell && cell->m_info && cell->m_info->m_goalUnitID && cell->m_info->m_goalUnitID!=obj->m_id) {
     int id=cell->m_info->m_goalUnitID;
     int i; for(i=0;i<count;++i) { if(ids[i]==id) break; }
     if(i==count) { ids[count++]=id; if(count==16) return 16; }
    }
   }
   if(checkGround) {
    PathfindCell *cell=getCell(1,x,y);
    if (cell && cell->m_info && cell->m_info->m_goalUnitID && cell->m_info->m_goalUnitID!=obj->m_id) {
     int id=cell->m_info->m_goalUnitID;
     int i; for(i=0;i<count;++i) { if(ids[i]==id) break; }
     if(i==count) { ids[count++]=id; if(count==16) return 16; }
    }
   }
  }
 }
 return count;
}
