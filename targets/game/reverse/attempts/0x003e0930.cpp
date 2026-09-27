// ?d_003e0930@@YAXXZ
// partial score=0.75 date=2026-09-27
// cl: /DNDEBUG /MD
// 0x003E0930: established bfmeStepE0930 caller ABI. currentCell points to
// the 0x34-byte Rva003D54E0 movement record; previousCell is an ICoord2D.
struct ICoord2D { int x,y; };
enum Relationship { REL_DUMMY=0 };
enum CrushSquishTestType { CRUSH_DUMMY=0 };
enum KindOfType { KIND_DUMMY=0 };
class Thing { public: bool isKindOf(KindOfType) const; };
class Object : public Thing { public:
 bool bfmeIsComputerControlled() const;
 Relationship getRelationship(const Object *) const;
 bool canCrushOrSquish(Object *,CrushSquishTestType) const;
 char pad00[0x74]; int m_id; char pad78[0x204-0x78]; void *m_ai204;
};
class GameLogic { public: Object *findObjectByID(int); };
extern GameLogic *TheBfmeGameLogic;
class PathfindCellInfo { public: char pad00[0x18]; int m_goalUnitID; };
class PathfindCell { public:
 PathfindCellInfo *m_info; char pad04[8]; unsigned m_word;
 int type() const { return m_word&7; }
 int layer() const { return (m_word>>6)&63; }
 int occupancy() const { return (m_word>>3)&7; }
 int goal() const { return m_info?m_info->m_goalUnitID:0; }
};
class PathfindLayer { public: PathfindCell *getCell(int,int); char pad00[0x44]; };
struct Movement003E0930 {
 ICoord2D cell; int layer,radius;
 unsigned char center,considerTransient; unsigned flags; int ignoredID;
 unsigned surfaces; unsigned char field20,field21; int field24;
 int allyFixedCount; unsigned char enemyFixed,allySeen,mobileSeen; int blockedCount;
};
class Pathfinder { public:
 bool bfmeStepE0930(Object *,ICoord2D *,ICoord2D *);
 bool bfmeStepD4F90(void *,PathfindCell *);
 char pad00[0x10]; PathfindCell **m_map; struct { ICoord2D lo,hi; } m_extent;
 char pad24[0x85c-0x24]; PathfindLayer m_layers[16];
 __forceinline PathfindCell *getCell(int layer,int x,int y) {
  if(x>=m_extent.lo.x && x<=m_extent.hi.x && y>=m_extent.lo.y && y<=m_extent.hi.y) {
   if(layer>1 && layer<=15) { PathfindCell *cell=m_layers[layer].getCell(x,y); if(cell) return cell; }
   return &m_map[x][y];
  } return 0;
 }
};
bool Pathfinder::bfmeStepE0930(Object *obj,ICoord2D *currentCell,ICoord2D *previousCell)
{
 Movement003E0930 *info=(Movement003E0930 *)currentCell;
 info->allyFixedCount=0;
 info->allySeen=0;
 info->mobileSeen=0;
 info->enemyFixed=0;
 info->blockedCount=0;
 int maxRadius=info->center?info->radius+1:info->radius;
 int lastID=0;
 for(int x=info->cell.x-info->radius;x<info->cell.x+maxRadius;++x) {
  bool inPreviousX=x>=previousCell->x-info->radius && x<previousCell->x+maxRadius;
  for(int y=info->cell.y-info->radius;y<info->cell.y+maxRadius;++y) {
   PathfindCell *cell=getCell(info->layer,x,y);
   if(!cell) return false;
   if(inPreviousX && y>=previousCell->y-info->radius && y<previousCell->y+maxRadius) {
    if(cell->type()==5) ++info->blockedCount;
    if(((unsigned char)(cell->m_word>>21)&1) && obj->bfmeIsComputerControlled()) ++info->blockedCount;
    if(info->flags&8) {
     int layer=info->layer; int cellLayer=cell->layer();
     if(layer!=cellLayer && ((layer==1 && cellLayer!=16) || (layer>=17 && layer<=64 && cellLayer!=16))) ++info->blockedCount;
    }
    if((info->flags&4) && !bfmeStepD4F90(&info->surfaces,cell)) ++info->blockedCount;
   } else {
    if(cell->type()==5) ++info->blockedCount;
    if(((unsigned char)(cell->m_word>>21)&1) && obj->bfmeIsComputerControlled()) ++info->blockedCount;
    if(info->flags&8) {
     int layer=info->layer; int cellLayer=cell->layer();
     if(layer!=cellLayer && ((layer==1 && cellLayer!=16) || (layer>=17 && layer<=64 && cellLayer!=16))) ++info->blockedCount;
    }
    if((info->flags&4) && !bfmeStepD4F90(&info->surfaces,cell)) ++info->blockedCount;
    int occupancy=cell->occupancy();
    if(occupancy) {
     if(occupancy==1 || occupancy==4) info->mobileSeen=1;
     int id=cell->goal();
     if(id!=obj->m_id && id!=info->ignoredID && id!=lastID) {
      lastID=id;
      Object *unit=TheBfmeGameLogic->findObjectByID(id);
      if(unit) {
       bool consider=false;
       bool allied;
       if(occupancy==2 || occupancy==4) {
        allied=obj->getRelationship(unit)==2;
        if(allied) info->allySeen=1;
        if(info->considerTransient) consider=true;
       }
       Object *object=obj;
       if(occupancy==3) allied=object->getRelationship(unit)==2;
       else if(!consider) continue;
       if(!(allied && object->isKindOf((KindOfType)0x73) && unit->isKindOf((KindOfType)0x73)) &&
          !(object->isKindOf((KindOfType)0x7c) && unit->isKindOf((KindOfType)8))) {
        if(allied) {
         if(!unit->m_ai204 || (info->flags&2)) return false;
         info->allyFixedCount=1;
        } else if(!object->canCrushOrSquish(unit,(CrushSquishTestType)2)) {
         if(info->flags&1) return false;
         info->enemyFixed=1;
        }
       }
      }
     }
    }
   }
  }
 }
 return true;
}
