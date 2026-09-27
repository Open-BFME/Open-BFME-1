// ?d_003dff70@@YAXXZ
// partial score=0.231884 date=2026-09-27
// cl: /DNDEBUG /MD
// RVA 003DFF70: footprint cell checks and occupancy-cost accumulation.
// Complete 816B extent ends after ret 0x1c at 003E029D; INT3 from 003E02A0.
struct Coord3D { float x,y,z; };
struct ICoord2D { int x,y; };
class BfmeSubBIA { public: int ask(); };
class Template003DFF70 { public: int m_00; BfmeSubBIA *m_override; char pad08[0xc8-8]; unsigned m_c8,m_cc,m_d0,m_d4; };
class AIUpdateInterface { public: int getIgnoredObstacleID(); };
enum Relationship { REL_DUMMY=0 };
class Object { public:
 bool bfmeIsComputerControlled() const;
 Relationship getRelationship(const Object *) const;
 int m_00; Template003DFF70 *m_template; char pad08[0x74-8]; int m_id;
 char pad78[0x204-0x78]; AIUpdateInterface *m_ai204; char pad208[12]; Object *m_214;
 Template003DFF70 *data() const {
  Template003DFF70 *t=m_template;
  if(t && t->m_override) t=(Template003DFF70 *)t->m_override->ask();
  return t;
 }
};
class PathfindCellInfo { public: char pad00[0x14]; int m_14,m_18,m_1c,m_20; };
class PathfindCell { public: PathfindCellInfo *m_info; char pad04[8]; unsigned m_word;
 int type() const { return m_word&7; }
 int occupancy() const { return (m_word>>3)&7; }
 int id14() const { return m_info?m_info->m_14:0; }
 int id18() const { return m_info?m_info->m_18:0; }
 int id20() const { return m_info?m_info->m_20:0; }
};
class PathfindLayer { public: PathfindCell *getCell(int,int); char pad00[0x44]; };
class GameLogic { public: Object *findObjectByID(int); };
extern GameLogic *TheGameLogic;
struct Terrain003DFF70 {
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual float height(float,float,int,void *,bool);
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
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual bool slotBC(const Coord3D *);
};
extern Terrain003DFF70 *g_rva012EF4CC;
class Pathfinder { public:
 bool checkFootprint003DFF70(Object *,int,int,int,int,unsigned char,int *);
 char pad00[0x10]; PathfindCell **m_map; struct { ICoord2D lo,hi; } m_extent;
 char pad24[0x85c-0x24]; PathfindLayer m_layers[16];
 __forceinline PathfindCell *getCell(int layer,int x,int y) {
  if(x>=m_extent.lo.x && x<=m_extent.hi.x && y>=m_extent.lo.y && y<=m_extent.hi.y) {
   if(layer>1 && layer<=15) { PathfindCell *cell=m_layers[layer].getCell(x,y); if(cell) return cell; }
   return &m_map[x][y];
  } return 0;
 }
};
bool Pathfinder::checkFootprint003DFF70(Object *obj,int cellX,int cellY,int layer,int radiusArg,unsigned char centerArg,int *cost)
{
 int radius=radiusArg; bool center=centerArg!=0;
 if(obj->data()->m_d4&0x1000) {
  if(layer!=1) { radius=1; center=true; }
  else {
   Coord3D pos; pos.x=(cellX+0.5f)*10.0f; pos.y=(cellY+0.5f)*10.0f;
   pos.z=g_rva012EF4CC->height(pos.x,pos.y,1,0,true);
   if(g_rva012EF4CC->slotBC(&pos)) { radius=1; center=true; }
  }
 }
 if((obj->data()->m_d0&0x2000000) && (obj->data()->m_c8&0x100) && layer!=1) { radius=1; center=false; }
 int maxRadius=radius; if(center) ++maxRadius;
 *cost=0;
 int ignore=0,ownID=0;
 if(obj->m_ai204) { ignore=obj->m_ai204->getIgnoredObstacleID(); ownID=obj->m_id; }
 for(int x=cellX-radius;x<cellX+maxRadius;++x) {
  for(int y=cellY-radius;y<cellY+maxRadius;++y) {
   PathfindCell *cell=getCell(layer,x,y);
   if(!cell) return false;
   if((unsigned char)cell->type()==5) return false;
   if(((unsigned char)(cell->m_word>>21)&1) && obj->bfmeIsComputerControlled()) return false;
   switch(cell->type()) {
   case 2: return false;
   case 4:
    if(!ignore || cell->id20()!=ignore) return false;
    break;
   case 5: case 6: return false;
   default:
    if(((unsigned char)(cell->m_word>>21)&1) && obj->bfmeIsComputerControlled()) return false;
    if(cell->occupancy()!=0) {
     int id=cell->id14();
     if(id!=ownID && (!ignore || ignore!=id)) {
      if(id) {
       Object *unit=TheGameLogic->findObjectByID(id);
       if(unit) {
        if(unit->m_214==obj) continue;
        if(obj->getRelationship(unit)==2) ++*cost;
        else if(cell->occupancy()==3) return false;
       }
      }
      int goal=cell->id18();
      if(goal!=ownID && goal) {
       Object *unit=TheGameLogic->findObjectByID(goal);
       if(unit && unit->m_214!=obj) {
        if(obj->getRelationship(unit)==2) *cost+=3;
        else ++*cost;
       }
      }
     }
    }
   }
  }
 }
 return true;
}
