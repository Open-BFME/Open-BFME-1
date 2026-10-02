// cl: /DNDEBUG /MD /EHsc

// FreeLifeBody::internalChangeHealth, retail 0x002134E0 (344 bytes).
//
// Identity: targets/game/reverse/identity_evidence/002134e0-freelifebody-internalchangehealth.md.
// The body is slot 32 (+0x80) of FreeLifeBody's BodyModuleInterface table
// (VA 0x010A83A0, stored by ??0FreeLifeBody 0x00213390 and ??1FreeLifeBody
// 0x002132B0); the same slot holds ActiveBody::internalChangeHealth 0x002103A0
// in the ActiveBody-derived tables and ImmortalBody's override in its own.
//
// Calls through that table enter with ECX at the +0x10 interface subobject, so
// the object (+0x08) and module data (+0x04) are reached at this-8/this-12 and
// the +0xE4..+0xF0 members set up by the constructor appear at +0xD4..+0xE0.
// When the free life does not fire it forwards to its base's override,
// RespawnBody::internalChangeHealth at 0x002147E0: slot 32 of RespawnBody's
// table 0x010A90D0, stored by ??0RespawnBody 0x00214650 and ??1RespawnBody
// 0x002146A0 (same evidence file).
// Direct dispatch ABI is independently pinned at 001BE220: condition + duration.
class UpgradeTemplate;
class DamageInfo { public: char pad[8]; int source; };
class Player { public: bool hasUpgradeComplete(const UpgradeTemplate*); };
class Object { public:
 Player *getControllingPlayer() const;
 bool hasUpgrade(const UpgradeTemplate*) const;
};
struct Rva001BE220Receiver { void dispatch(int,unsigned int); };
struct BFMEReportDamageSource { void report(Object*,int); };
class GameLogic { public: char pad[0x3c]; unsigned int frame; Object *findObjectByID(int); };
extern GameLogic *TheGameLogic;
struct Rva002134E0Data { char pad[0x70]; int field70; unsigned int field74; char pad78[4]; UpgradeTemplate *field7c; };
#define V(N) virtual void slot##N()
// Both classes seen from their +0x10 BodyModuleInterface subobject.
class RespawnBody { public:
 V(00);V(01);V(02);V(03); virtual float health();
 V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);V(14);V(15);V(16);V(17);V(18);V(19);V(20);
 virtual void restore(float,bool);
 V(22);V(23);V(24);V(25);V(26);V(27);V(28);V(29);V(30);V(31);
 virtual void internalChangeHealth(float,DamageInfo*);
 char pad[0xd0];
};
class FreeLifeBody : public RespawnBody { public:
 virtual void internalChangeHealth(float,DamageInfo*);
 float fieldD4; bool fieldD8; char padD9[3]; unsigned int fieldDC,fieldE0;
};
// ?internalChangeHealth@FreeLifeBody@@UAEXMPAVDamageInfo@@@Z
void FreeLifeBody::internalChangeHealth(float amount,DamageInfo *info) {
 Object *obj=*(Object**)((char*)this-8);
 Rva002134E0Data *md=*(Rva002134E0Data**)((char*)this-12);
 Player *player=obj->getControllingPlayer();
 if(-health()>=amount && fieldD4>0.0f) {
  if(md->field7c) {
   bool has=player && player->hasUpgradeComplete(md->field7c);
   bool objectHas=obj->hasUpgrade(md->field7c);
   if(!has && !objectHas) goto fallback;
  }
  if(fieldD8 && !((float)TheGameLogic->frame-(float)fieldDC > (float)fieldE0)) goto fallback;
  fieldD8=true;
  fieldDC=TheGameLogic->frame;
  if(md->field70 != -1) ((Rva001BE220Receiver*)obj)->dispatch(md->field70,md->field74);
  restore(fieldD4*100.0f,false);
  if(info) {
   Object *source=TheGameLogic->findObjectByID(info->source);
   if(source) ((BFMEReportDamageSource*)source)->report(obj,3);
  }
  return;
 }
fallback:
 RespawnBody::internalChangeHealth(amount,info);
}
