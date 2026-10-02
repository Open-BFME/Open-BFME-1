// ActiveBody::attemptHealing secondary BodyModuleInterface view (+0x10).
// Identity: existing DAMAGE_HEALING dispatch and ActiveBody interface slot 1;
// native BFME offsets/callback sequence independently read at RVA0020FBC0.
// The primary subobject is this-16, not a pointer loaded from that address.
// Slot80 receives DamageInfo* here; the older Bool declaration in sibling
// views is not evidence for this call (retail pushes the full info pointer).
// Callee001B0200 consumes a damage-input record, Object*, and unused stack slot;
// both exits ret12 with ST0 holding adjusted float. Healing returns input+18.
// The linked-body local preserves the retail virtual-call receiver lifetime.
// cl: /DNDEBUG /MD /EHsc
class DamageInfo { public: char prefix[0x10]; int damageType; char gap14[0x3c]; float actual,clipped; };
class Object; class FXList;
enum KindOfType { KINDOF_HEALING_149=149,KINDOF_HEALING_22=22,KINDOF_HEALING_24=24,KINDOF_HEALING_7=7 };
class Thing { public: bool isKindOf(KindOfType) const; };
class Overridable { public: void *vtable; Overridable *next; const Overridable *getFinalOverride() const; };
struct HealingTemplate0020FBC0 : Overridable { char pad[0x4ca-8]; bool field4CA; };
struct HealingDamageFacet0020FBC0 { virtual void unused(); virtual void onHealing(DamageInfo*); virtual void onState(DamageInfo*,int,int); };
struct HealingBehaviorFacet0020FBC0 { virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual HealingDamageFacet0020FBC0 *getDamage(); };
struct HealingBehavior0020FBC0 { char prefix[12]; HealingBehaviorFacet0020FBC0 facet; };
#define V(N) virtual void slot##N()
struct HealingBodyFacet0020FBC0 {
 V(00);V(01);V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);V(14);V(15);V(16);V(17);V(18);V(19);V(20);V(21);V(22);V(23);V(24);V(25);V(26);V(27);V(28);V(29);V(30);V(31);V(32);V(33);V(34);V(35);V(36);V(37);V(38); virtual void state(int);
};
class Object { public:
 void *vtable; HealingTemplate0020FBC0 *tmpl; char gap8[0x90-8]; unsigned int m_status; char gap94[0x1f0-0x94]; HealingBehavior0020FBC0 **m_behaviors; char gap1f4[12]; HealingBodyFacet0020FBC0 *body; char gap204[0x344-0x204]; unsigned int m_privateStatus;
 HealingTemplate0020FBC0 *getTemplate() const { HealingTemplate0020FBC0 *t=tmpl; if(!t)return 0; if(t->next)t=(HealingTemplate0020FBC0*)t->next->getFinalOverride();return t; }
};
class GameLogic { public: char pad[0x3c]; unsigned frame; Object *findObjectByID(int); };
extern GameLogic *TheGameLogic;
class FXList { public: static void doFXObj(const FXList*,const Object*,const Object*); };
struct HealingData0020FBC0 { char pad[0x48]; const FXList *fx; };
struct HealingArmor001B0200 { float adjust(void*,Object*,int); };
struct HealingPrimary0020FBC0 { V(00);V(01);V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13); virtual void validate(); virtual void fx(DamageInfo*); };
class ActiveBody { public:
 virtual void attemptDamage(DamageInfo*); virtual void attemptHealing(DamageInfo*);
 V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);V(14);V(15);V(16);V(17);V(18);V(19);V(20);V(21);V(22);V(23);V(24);V(25);V(26);V(27);V(28);V(29);V(30);V(31); virtual void internalChangeHealth(float,DamageInfo*);
 char pad04[4]; float m_currentHealth,m_prevHealth;char pad10[0x10];int m_curDamageState;char pad24[0x6c];unsigned m_lastHealingTimestamp;char pad94[0x28];int fieldBC;char padC0[8];HealingArmor001B0200 armor;
 Object *getObject() const { return *(Object**)((char*)this-8); }
};
void ActiveBody::attemptHealing(DamageInfo *info) {
 HealingPrimary0020FBC0 *primary=(HealingPrimary0020FBC0*)((char*)this-16);
 primary->validate();
 if(!info)return;
 if(info->damageType!=7) { attemptDamage(info);return; }
 Object *obj=getObject();
 if(!obj->getTemplate()->field4CA && !((Thing*)obj)->isKindOf(KINDOF_HEALING_149) && !((Thing*)obj)->isKindOf(KINDOF_HEALING_22) && !((Thing*)obj)->isKindOf(KINDOF_HEALING_24) && (obj->m_privateStatus&1)) return;
 info->actual=0.0f;info->clipped=0.0f;
 float amount=armor.adjust((char*)info+4,getObject(),0);
 if(amount>0.0f) {
  int oldState=m_curDamageState;
  internalChangeHealth(amount,info);
  info->actual=amount;info->clipped=m_prevHealth-m_currentHealth;
  m_lastHealingTimestamp=TheGameLogic->frame;
  if(m_currentHealth>m_prevHealth) {
   for(HealingBehavior0020FBC0 **m=obj->m_behaviors;*m;++m) {
    HealingDamageFacet0020FBC0 *d=(*m)->facet.getDamage();
    if(d) d->onHealing(info);
   }
   HealingData0020FBC0 *md=*(HealingData0020FBC0**)((char*)this-12);
   if(!((Thing*)obj)->isKindOf(KINDOF_HEALING_7) && md && md->fx && !(obj->m_status&0x40)) FXList::doFXObj(md->fx,obj,0);
  }
  if(m_curDamageState!=oldState) {
   for(HealingBehavior0020FBC0 **m=obj->m_behaviors;*m;++m) {
    HealingDamageFacet0020FBC0 *d=(*m)->facet.getDamage();
    if(d) d->onState(info,oldState,m_curDamageState);
   }
   if(fieldBC) { Object *linked=TheGameLogic->findObjectByID(fieldBC);if(linked) { HealingBodyFacet0020FBC0 *b=linked->body; if(b) b->state(m_curDamageState); } }
  }
 }
 primary->fx(info);
}
