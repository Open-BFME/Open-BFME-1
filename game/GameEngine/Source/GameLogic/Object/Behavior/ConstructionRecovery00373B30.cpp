// cl: /Igame/GameEngine/Source/GameLogic/Object
#define OBJECT_TU_MEMBERS Team* getTeam() const { return m_team; }
#include "object.h"
// Retail 0x00373B30. CastleBehavior receiver witnessed by neighbouring methods;
// semantic method identity remains unknown. Caller: CastleBehavior update
// interface at 0x00377740 through its ILT. Object layout is the canonical header.
// +0xD0/+0xD4 delimit owned ObjectIDs; +0xA0 selects the construction object.
// Body-interface slots +0x3C/+0x40 return the last damage record and frame.
// The record supplies the player mask at +0xC and damage amount at +0x1C.
// Repeated record calls and the shared effects tail reproduce retail exactly.
// getTeam() intentionally returns by value: direct field access rotates the
// scratch registers and changes the second mask load from xor/mov to movzx.
// The sound call preserves the existing ThingTemplate::getSound callee ABI;
// the pointer comes from Object::getDrawable, not a recovered template field.
// No identity correction of that already-landed callee is claimed here.
class Team;
class Object;
enum Relationship { RELATIONSHIP_ENEMIES=0 };
class Player { public: Relationship getRelationship(const Team*) const; };
class GameLogic { public: Object* findObjectByID(int); };
class PlayerList { public: Player* getPlayerFromMask(unsigned short); };
class AudioEventRTS;
class ThingTemplate { public: const AudioEventRTS* getSound(int) const; };
class FXList { public: static void doFXObj(const FXList*,const Object*,const Object*); };
extern GameLogic* TheGameLogic;
extern PlayerList* ThePlayerList;
class AudioManager;
extern AudioManager* TheAudio;
extern void j_00013935();
extern void j_0004B01A();
template<class T> inline T& at(void* p,int n) { return *(T*)((char*)p+n); }
struct DamageRecord00373B30 { char field00[12]; unsigned short field0c; char field0e[14]; float field1c; };
class DamageSource00373B30 {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
 virtual void v30(); virtual void v34(); virtual void v38();
 virtual DamageRecord00373B30* record();
 virtual unsigned frame();
};
class HealingDispatch00373B30 {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void slot28();
 virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
 virtual void dispatch(float,Object*);
};
struct Audio00373B30 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
 virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
 virtual void v40(); virtual void add(const AudioEventRTS*);
};
struct Compare00373B30 {
 int compare(const char* s) { union {void* p; int (Compare00373B30::*f)(const char*); } u; u.p=(void*)j_0004B01A; return (this->*u.f)(s); }
};
class Rva00373B30Receiver {
public:
 void update();
 void reset(bool b) { union {void* p; void (Rva00373B30Receiver::*f)(bool); } u; u.p=(void*)j_00013935; (this->*u.f)(b); }
};
void Rva00373B30Receiver::update() {
 if(at<int*>(this,0xd0)==at<int*>(this,0xd4)) return;
 Object* object=TheGameLogic->findObjectByID(at<int>(this,0xa0));
 if(!object || object->m_constructionPercent<8.0f) return;
 void* data=at<void*>(this,4);
 bool hostile=false;
 bool expired=false;
 for(int i=(at<int*>(this,0xd4)-at<int*>(this,0xd0))-1;i>=0;--i) {
  Object* child=TheGameLogic->findObjectByID(at<int*>(this,0xd0)[i]);
  if(!child) continue;
  DamageSource00373B30* damage=(DamageSource00373B30*)child->m_body;
  if(damage && damage->frame()>=at<unsigned>(this,0xb0) && damage->record() && damage->record()->field1c>0.0f) {
   Player* player=ThePlayerList->getPlayerFromMask(damage->record()->field0c);
   if(player && player->getRelationship(object->getTeam())==0 && ((Compare00373B30*)((char*)player+0x1c))->compare("PlyrCreeps")!=0) { hostile=true; break; }
  }
 }
 DamageSource00373B30* damage=(DamageSource00373B30*)object->m_body;
 if(damage && damage->frame()>=at<unsigned>(this,0xb0) && damage->record() && damage->record()->field1c>0.0f) {
  Player* player=ThePlayerList->getPlayerFromMask(damage->record()->field0c);
  if(player && player->getRelationship(object->getTeam())==0 && ((Compare00373B30*)((char*)player+0x1c))->compare("PlyrCreeps")!=0) hostile=true;
 }
 if(!(object->m_constructionPercent>=99.0f)) {
  if(at<unsigned>(TheGameLogic,0x3c)>=at<unsigned>(this,0xb0)+at<unsigned>(data,0x44)) expired=true;
  if(!hostile || !expired) goto effects;
 }
 {
  reset(false);
  ((HealingDispatch00373B30*)object)->dispatch(9999.0f,object);
  object->m_constructionPercent=100.0f;
  ThingTemplate* t=(ThingTemplate*)object->getDrawable();
  if(t) { const AudioEventRTS* sound=t->getSound(13); if(sound) ((Audio00373B30*)TheAudio)->add(sound); }
 }
effects:
 if((unsigned)(at<int*>(this,0xd4)-at<int*>(this,0xd0))>0 && at<unsigned>(TheGameLogic,0x3c)%at<unsigned>(data,0x48)==0) {
  const FXList* fx=at<FXList*>(data,0x4c);
  if(fx) FXList::doFXObj(fx,at<Object*>(this,8),0);
 }
}
