// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// GameLogic::prepareLogicForObjectLoad at0x0038B2C0, complete295B through
// the tail jump at38B3E2. The old285B dump stopped inside the epilogue.
// The source counterpart names this exact bridge/tower/wall cleanup before
// saved objects are loaded. It removes each bridge's four tower IDs and its
// bridge object, removes walkable walls, then immediately drains destruction.
// Object traversal must save next before scheduling destruction. The lookup
// map is the independently recovered BFME ObjectID hash_map atGameLogic+B0.
// Vtable declarations describe positions only for uncalled slots.
#define _STLP_USE_NEWALLOC 1
#include <hash_map>
struct Coord3D {float x,y,z;};
class ThingTemplate {
public:
 ThingTemplate *getFinalOverride();
 char pad0[4]; ThingTemplate *overrideTemplate; char pad8[0xc0]; unsigned kindOf[3];
};
class Object {
public:
 char pad0[4];ThingTemplate *thingTemplate;char pad8[0x30];Coord3D position;char pad44[0x44];Object *next;
 ThingTemplate *getTemplate()const {
  ThingTemplate *t=thingTemplate;
  if(t && t->overrideTemplate)t=t->overrideTemplate->getFinalOverride();
  return t;
 }
};
struct BridgeInfo {char pad0[0x54];int bridgeObjectID;int towerObjectID[4];};
class Bridge {public:char pad0[0xc];BridgeInfo info;const BridgeInfo *peekBridgeInfo(){return &info;}};
class TerrainLogic {public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5C();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6C();
 virtual void slot70();
 virtual void slot74();
 virtual void slot78();
 virtual void slot7C();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8C();
 virtual void slot90();
 virtual void slot94();
 virtual Bridge *findBridgeAt(const Coord3D*)const;
};
extern TerrainLogic *TheTerrainLogic;
class Gen_0038D000 {friend class GameLogic; void bfmeFinish();};
typedef _STL::hash_map<int,Object*,_STL::hash<int>,_STL::equal_to<int> > ObjectPtrHash;
class GameLogic {
public:
 char pad0[0xa8];Object *first;char padAC[4];ObjectPtrHash objects;
 void destroyObject(Object*);
 void processDestroyList(){((Gen_0038D000*)this)->bfmeFinish();}
 Object *findObjectByID(int id) {
  if(id==0)return 0;
  ObjectPtrHash::iterator it=objects.find(id);
  if(it==objects.end())return 0;
  return it->second;
 }
private:
 void prepareLogicForObjectLoad();
};
void GameLogic::prepareLogicForObjectLoad()
{
    Object *obj, *next;
    for (obj = first; obj; obj = next)
    {
        next = obj->next;
        // KINDOF_BRIDGE is bit22, in the first kind-of word.
        if (obj->getTemplate()->kindOf[0] & 0x400000)
        {
            Bridge *bridge = TheTerrainLogic->findBridgeAt(&obj->position);
            const BridgeInfo *info = bridge->peekBridgeInfo();
            Object *oldObject = findObjectByID(info->bridgeObjectID);
            Object *oldTower;
            for (int i = 0; i < 4; ++i)
            {
                oldTower = findObjectByID(info->towerObjectID[i]);
                if (oldTower)
                    destroyObject(oldTower);
            }
            destroyObject(oldObject);
        }
        // KINDOF_WALK_ON_TOP_OF_WALL is bit59, in the second word.
        else if (obj->getTemplate()->kindOf[1] & 0x8000000)
        {
            destroyObject(obj);
        }
    }
    processDestroyList();
}
