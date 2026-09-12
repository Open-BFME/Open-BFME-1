// ?setPathFromWaypoint@AIUpdateInterface@@QAEXPBVWaypoint@@PBUCoord2D@@@Z
// partial score=0.9824 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
struct Coord3D { Coord3D(){} Coord3D(const Coord3D& c):x(c.x),y(c.y),z(c.z){} float x,y,z; };
struct Coord2D { float x,y; };
enum PathfindLayerEnum { LAYER_GROUND=1 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
class Object { public: char pad[0x38]; Coord3D position; const Coord3D *getPosition() const {return &position;} };
class AIUpdateInterface;
class Path {
 friend class AIUpdateInterface;
public:
 Path();
 void prependNode(const Coord3D *,PathfindLayerEnum);
 void appendNode(const Coord3D *,PathfindLayerEnum);
 void markOptimized() { optimized=true; }
protected:
 virtual ~Path();
private:
 char pad04[8]; bool optimized; char pad0d[0x17];
};
class Waypoint {
public:
 const Coord3D *getLocation() const {return &position;}
 const Waypoint *getLink(int i) const {return links[i];}
 char prefix[12]; Coord3D position; char gap18[8]; const Waypoint *links[1];
};
class Pathfinder {
public: void snapPosition(Object *,Coord3D *); void setDebugPath(Path *);
};
class AI { public: char prefix[12]; Pathfinder *finder; Pathfinder *pathfinder() const {return finder;} };
extern AI *TheAI;
class UpdateModule {
public: virtual void slot00();
protected:
 UpdateSleepTime getWakeFrame() const;
 void setWakeFrame(Object *,UpdateSleepTime);
};
class AIUpdateInterface : public UpdateModule {
public:
 void setPathFromWaypoint(const Waypoint *,const Coord2D *);
 virtual void slot004();
 virtual void slot008();
 virtual void slot00C();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01C();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02C();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03C();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04C();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05C();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06C();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07C();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08C();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09C();
 virtual void slot0A0();
 virtual void slot0A4();
 virtual void slot0A8();
 virtual void slot0AC();
 virtual void slot0B0();
 virtual void slot0B4();
 virtual void slot0B8();
 virtual void slot0BC();
 virtual void slot0C0();
 virtual void slot0C4();
 virtual void slot0C8();
 virtual void slot0CC();
 virtual void slot0D0();
 virtual void slot0D4();
 virtual void slot0D8();
 virtual void slot0DC();
 virtual void slot0E0();
 virtual void slot0E4();
 virtual void slot0E8();
 virtual void slot0EC();
 virtual void slot0F0();
 virtual void slot0F4();
 virtual void slot0F8();
 virtual void slot0FC();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10C();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11C();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12C();
 virtual void slot130();
 virtual void slot134();
 virtual void slot138();
 virtual void slot13C();
 virtual void slot140();
 virtual void slot144();
 virtual void slot148();
 virtual void slot14C();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual void slot15C();
 virtual void slot160();
 virtual void slot164();
 virtual void slot168();
 virtual void slot16C();
 virtual void slot170();
 virtual void slot174();
 virtual void slot178();
 virtual void slot17C();
 virtual void slot180();
 virtual void slot184();
 virtual void slot188();
 virtual void slot18C();
 virtual void slot190();
 virtual void slot194();
 virtual void slot198();
 virtual void slot19C();
 virtual void slot1A0();
 virtual void slot1A4();
 virtual void slot1A8();
 virtual void slot1AC();
 virtual void slot1B0();
 virtual void slot1B4();
 virtual void slot1B8();
 virtual void slot1BC();
 virtual void slot1C0();
 virtual void slot1C4();
 virtual void slot1C8();
 virtual void slot1CC();
 virtual void slot1D0();
 virtual void slot1D4();
 virtual void slot1D8();
 virtual void slot1DC();
 virtual void slot1E0();
 virtual void slot1E4();
 virtual void setLocomotorGoalNone();
private:
 __forceinline void destroyPath() {
  if(path) { Path *old=path; old->Path::~Path(); ::operator delete(old); }
  path=0; waiting=false; blocked=false; attack=false; setLocomotorGoalNone();
 }
 void wakeUpNow() { if(getWakeFrame()>UPDATE_SLEEP_NONE && !inUpdate) setWakeFrame(object,UPDATE_SLEEP_NONE); }
 char pad04[4]; Object *object; char pad0c[0x140-12]; Path *path;
 char pad144[0x31e-0x144]; bool waiting,attack; char pad320[6]; bool blocked;
 char pad327[9]; bool inUpdate;
};
#pragma comment(linker, "/alternatename:?prependNode@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@@Z=?j_0002b7f1@@YAXXZ")
#pragma comment(linker, "/alternatename:?snapPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z=?j_00009d04@@YAXXZ")
#pragma comment(linker, "/alternatename:?setDebugPath@Pathfinder@@QAEXPAVPath@@@Z=?j_0002ea3c@@YAXXZ")
void AIUpdateInterface::setPathFromWaypoint(const Waypoint *way,const Coord2D *offset)
{
 destroyPath();
 path=new Path;
 Coord3D pos=*object->getPosition();
 path->prependNode(&pos,LAYER_GROUND);
 path->markOptimized();
 int count=0;
 while(way) {
  Coord3D wayPos=*way->getLocation();
  wayPos.x+=offset->x;
  wayPos.y+=offset->y;
  if(way->getLink(0)==0) TheAI->pathfinder()->snapPosition(object,&wayPos);
  path->appendNode(&wayPos,LAYER_GROUND);
  way=way->getLink(0);
  ++count;
  if(count>1024) break;
 }
 waiting=false;
 TheAI->pathfinder()->setDebugPath(path);
 wakeUpNow();
}
