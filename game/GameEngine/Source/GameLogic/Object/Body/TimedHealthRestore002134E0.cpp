// RVA002134E0: secondary body interface; owner identity remains unproved.
// Retail reads object at this-8 and module data at this-12.
// Cooldown requires strict greater-than including unordered fallback.
// Direct dispatch ABI is independently pinned at 001BE220: condition + duration.
// cl: /DNDEBUG /MD /EHsc
class UpgradeTemplate;
struct DamageInfo { char pad[8]; int source; };
class Player { public: bool hasUpgradeComplete(const UpgradeTemplate*); };
class Object { public:
 Player *getControllingPlayer() const;
 bool hasUpgrade(const UpgradeTemplate*) const;
};
struct Rva001BE220Receiver { void dispatch(int,unsigned int); };
struct BFMEReportDamageSource { void report(Object*,int); };
class GameLogic { public: char pad[0x3c]; unsigned int frame; Object *findObjectByID(int); };
extern GameLogic *TheBfmeGameLogic;
struct Rva002147E0Owner { void apply(float,DamageInfo*); };
struct Rva002134E0Data { char pad[0x70]; int field70; unsigned int field74; char pad78[4]; UpgradeTemplate *field7c; };
#define V(N) virtual void slot##N()
struct TimedHealthRestore002134E0 {
 V(00);V(01);V(02);V(03); virtual float health();
 V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);V(14);V(15);V(16);V(17);V(18);V(19);V(20);
 virtual void restore(float,bool);
 char pad[0xd0]; float fieldD4; bool fieldD8; char padD9[3]; unsigned int fieldDC,fieldE0;
 void apply(float,DamageInfo*);
};
void TimedHealthRestore002134E0::apply(float amount,DamageInfo *info) {
 Object *obj=*(Object**)((char*)this-8);
 Rva002134E0Data *md=*(Rva002134E0Data**)((char*)this-12);
 Player *player=obj->getControllingPlayer();
 if(-health()>=amount && fieldD4>0.0f) {
  if(md->field7c) {
   bool has=player && player->hasUpgradeComplete(md->field7c);
   bool objectHas=obj->hasUpgrade(md->field7c);
   if(!has && !objectHas) goto fallback;
  }
  if(fieldD8 && !((float)TheBfmeGameLogic->frame-(float)fieldDC > (float)fieldE0)) goto fallback;
  fieldD8=true;
  fieldDC=TheBfmeGameLogic->frame;
  if(md->field70 != -1) ((Rva001BE220Receiver*)obj)->dispatch(md->field70,md->field74);
  restore(fieldD4*100.0f,false);
  if(info) {
   Object *source=TheBfmeGameLogic->findObjectByID(info->source);
   if(source) ((BFMEReportDamageSource*)source)->report(obj,3);
  }
  return;
 }
fallback:
 ((Rva002147E0Owner*)this)->apply(amount,info);
}
