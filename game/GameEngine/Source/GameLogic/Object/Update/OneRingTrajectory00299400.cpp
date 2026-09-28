// cl: /DNDEBUG /MD
// stlport
// Retail 0x00299400: OneRingPenaltyUpdate trajectory step (string VA 0x010C06B8 names OneRingPenaltyUpdate.cpp); method name unknown.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>
extern "C" float cosf(float);
extern "C" float sinf(float);
struct Coord3D { float x,y,z; };
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS void setPosition(const Coord3D*);
#define OBJECT_TU_MEMBERS AIUpdateInterface* getAIUpdateInterface() { return m_ai; }
#include "../object.h"
#include "../../command_source_type.h"
typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;
class GameLogic { public:
 __declspec(noinline) Object* findObjectByID(int id) { if(!id) return 0; ObjectPtrHash::iterator it=m_objHash.find(id); if(it==m_objHash.end()) return 0; return (*it).second; }
 char pad00[0x3c]; unsigned frame; char pad40[0x70]; ObjectPtrHash m_objHash;
};
extern GameLogic* TheBfmeGameLogic;
class Team; class Waypoint; class PolygonTrigger; class CommandButton; class Path;
enum AICommandType { AICMD_MOVE_TO_POSITION = 0x00 };
struct DamageInfo { char m_bfme_body[0x5C]; };
// Layout and body as landed in AICommandInterfaceMovementOrders.cpp; visible here as in the retail header.
class AICommandParms { public:
 AICommandParms( AICommandType cmd, CommandSourceType commandSource );
 AICommandType m_cmd; CommandSourceType m_cmdSource; Coord3D m_pos; Object *m_obj; Object *m_otherObj; const Team *m_team;
 _STL::vector<Coord3D> m_coords; const Waypoint *m_waypoint; const PolygonTrigger *m_polygon; int m_intValue; DamageInfo m_damage;
 const CommandButton *m_commandButton; Path *m_path;
};
class AICommandInterface { public:
 virtual void aiDoCommand( const AICommandParms *parms ) = 0;
 void aiMoveToPosition( const Coord3D *position, CommandSourceType commandSource )
 {
  AICommandParms parms( AICMD_MOVE_TO_POSITION, commandSource );
  parms.m_pos = *position;
  aiDoCommand( &parms );
 }
};
class AIUpdateInterface { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0a();
 virtual void slot0b();
 virtual void slot0c();
 virtual void slot0d();
 virtual void slot0e();
 virtual void slot0f();
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
 virtual void slot1a();
 virtual void slot1b();
 virtual void slot1c();
 virtual void slot1d();
 virtual void slot1e();
 virtual void slot1f();
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
 virtual void slot2a();
 virtual void slot2b();
 virtual void slot2c();
 virtual void slot2d();
 virtual void slot2e();
 virtual void slot2f();
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
 virtual void slot3a();
 virtual void slot3b();
 virtual void slot3c();
 virtual void slot3d();
 virtual void slot3e();
 virtual void slot3f();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot4a();
 virtual void slot4b();
 virtual void slot4c();
 virtual void slot4d();
 virtual void slot4e();
 virtual void slot4f();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot5a();
 virtual void slot5b();
 virtual void slot5c();
 virtual void slot5d();
 virtual void slot5e();
 virtual void slot5f();
 virtual bool slot180();
};
class TerrainLogic { public: virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14(); virtual float height(float,float,void*); };
extern TerrainLogic* TheTerrainLogic;
class StealthCleanup00299250 { public: void apply(); };
extern float Rva0002CCA5GetGameLogicRandomValueRealThunk(float,float,char*,int);
struct Config00299400 { char pad00[12]; unsigned at0c,at10; char pad14[4]; float at18; };
class OneRingTrajectory00299400 { public: void update(); char pad00[4]; Config00299400* at04; Object* at08; char pad0c[0x18]; int at24; unsigned at28; float at2c; };
inline float lerp00299400(float a,float b,float t) { return a+(b-a)*t; }
void OneRingTrajectory00299400::update() {
 Config00299400* config=at04;
 Object* owner=at08;
 Object* target=TheBfmeGameLogic->findObjectByID(at24);
 unsigned frame=TheBfmeGameLogic->frame;
 unsigned start=config->at0c+at28;
 unsigned end=start+config->at10;
 if(frame>=end) {
  target->setPosition((Coord3D*)&owner->m_cachedPos);
  ((StealthCleanup00299250*)this)->apply();
  return;
 }
 if(target && target->getAIUpdateInterface() && target->getAIUpdateInterface()->slot180()) {
  Coord3D pos;
  pos.x=owner->m_cachedPos.x; pos.y=owner->m_cachedPos.y;
  float angle=at2c+Rva0002CCA5GetGameLogicRandomValueRealThunk(-1.5707963267948966f,1.5707963267948966f,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\OneRingPenaltyUpdate.cpp",185);
  at2c=angle;
  float distance;
  if(frame-start==0) distance=config->at18;
  else distance=lerp00299400(config->at18,config->at18*0.5f,(float)(frame-start)/(float)(end-start));
  pos.x+=cosf(angle)*distance;
  pos.y+=sinf(at2c)*distance;
  pos.z=TheTerrainLogic->height(pos.x,pos.y,0);
  ((AICommandInterface*)((char*)target->m_ai+0x20))->aiMoveToPosition(&pos,(CommandSourceType)2);
 }
}
