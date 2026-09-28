// cl: /DNDEBUG /MD /GX
// Retail 0x00278C30 (231 bytes), 0x00278F20 (241 bytes), 0x00278D50 (370 bytes).
// Slot30 is reached by the matched TransportAIUpdate attack-object override
// through ILT 0x00039F7C; retain the established address-derived base identity.
// Slot 34 is named by the matched TransportAIUpdate force-attack override,
// which tail-calls this address through ILT 0x0003DCF3. Its address-derived
// ledger identity is retained because the base descriptive name is disputed.
// The static selector must remain in this TU: MSVC passes target in EAX,
// flag in EBX and owner on the stack. Both complete bodies are byte-checked.
// Object +0x1FC is m_contain and owner +0x30 is m_stateMachine (name_oracle).
// Other raw offsets are witnessed by these bodies; no semantic names inferred.
// getFinalOverride uses the native recursive inline and nullable accessor.
// The 28-byte constructor is nonthrowing: retail ctor 0x000D1930 only writes
// its vtable and scalar fields. This preserves retail's lack of an EH frame.
template<class T> T &at(void *p, unsigned n) { return *(T*)((char*)p+n); }
class Object;
enum KindOfType {};
#include "../../../command_source_type.h"
class Thing { public: bool isKindOf(KindOfType) const; };
class Overridable { public: const Overridable *getFinalOverride() const { if(at<Overridable*>((void*)this,4)) return at<Overridable*>((void*)this,4)->getFinalOverride(); return this; } };
inline const Overridable *finalTemplate(Object *o) { const Overridable *p=at<Overridable*>(o,4); if(!p) return 0; return p->getFinalOverride(); }
class GameLogic { public: Object *findObjectByID(int); };
extern GameLogic *TheBfmeGameLogic;
class BFMEWeaponSetFlags {};
class BFMEWeaponSetOwner { public: const BFMEWeaponSetFlags &getWeaponSetFlags() const; };
class BfmeSubEQT;
class BfmeItemMD { public: char pad[4]; BfmeSubEQT *templateAt04; char pad08[0x20-8]; int countAt20; char pad24[0x34-0x24]; int limitAt34; };
class BfmeHolderMD { public: BfmeItemMD *bfmeFindMD(int); };
class BfmeHostXZ { public: void bfmeFinishXZ(void*); };
class BfmeContainOwner;
class Rva0018BDD0 { public: void collect(BfmeContainOwner*,bool); };
class Rva00181EE0Inner;
class Rva00181EE0Owner { public: void setFrom(Rva00181EE0Inner*); };
class Rva000D1930 { public: Rva000D1930() throw(); virtual ~Rva000D1930() throw(); char payload[24]; };
class AttackTargetInterface00278C30;
class AttackTargetModule00278C30 { public:
virtual void unused0();
virtual void unused1();
virtual void unused2();
virtual void unused3();
virtual void unused4();
virtual void unused5();
virtual void unused6();
virtual void unused7();
virtual void unused8();
virtual void unused9();
virtual void unused10();
virtual void unused11();
virtual void unused12();
virtual void unused13();
virtual void unused14();
virtual void unused15();
virtual void unused16();
virtual void unused17();
virtual void unused18();
virtual void unused19();
virtual void unused20();
virtual void unused21();
virtual void unused22();
virtual void unused23();
virtual void unused24();
virtual void unused25();
virtual AttackTargetInterface00278C30 *getInterface();
};
class AttackTargetInterface00278C30 { public:
virtual void unused0();
virtual void unused1();
virtual void unused2();
virtual void unused3();
virtual void unused4();
virtual void unused5();
virtual void unused6();
virtual void unused7();
virtual void unused8();
virtual void unused9();
virtual void unused10();
virtual void unused11();
virtual void unused12();
virtual void unused13();
virtual void unused14();
virtual void unused15();
virtual void unused16();
virtual void unused17();
virtual Object *select(int,int,int);
};
class AttackMachine00278F20 { public:
virtual void unused0();
virtual void unused1();
virtual void unused2();
virtual void unused3();
virtual void unused4();
virtual void clear();
virtual void unused6();
virtual void unused7();
virtual void setState(int);
virtual void unused9();
virtual void unused10();
virtual void unused11();
virtual void unused12();
virtual void unused13();
virtual void setTarget(Object*);
};

static Object *selectAttackTarget00278C30(Object *target,Object *owner,bool *flag)
{
 if (!(at<unsigned char>(owner,0x94)&0x20)) {
  Object *parent=at<Object*>(target,0x214);
  if (!parent || !((Thing*)parent)->isKindOf((KindOfType)108)) {
   parent=TheBfmeGameLogic->findObjectByID(at<int>(target,0x78));
   if(parent && ((Thing*)parent)->isKindOf((KindOfType)108)) target=parent;
  } else target=parent;
 } else if(at<unsigned>((void*)finalTemplate(target),0xd4)&0x1000) {
  AttackTargetModule00278C30 *module=at<AttackTargetModule00278C30*>(target,0x1fc);
  if(module) {
   AttackTargetInterface00278C30 *iface=module->getInterface();
   if(iface) { target=iface->select(0,0,0); if(!target) return 0; }
  }
 }
 *flag=(at<unsigned>((void*)finalTemplate(target),0xd4)&0x1000)!=0;
 if((at<unsigned>((void*)finalTemplate(owner),0xd4)&0x400000) || (at<unsigned char>(owner,0x94)&0x20)) *flag=false;
 return target;
}
class Rva00278F20 { public: void slot34(Object*,int,CommandSourceType); char pad[0x30]; AttackMachine00278F20 *m_stateMachine; char pad34[0x48-0x34]; CommandSourceType m_sourceAt48; };
void Rva00278F20::slot34(Object *target,int shots,CommandSourceType source)
{
 if(!target) return;
 Object *owner=at<Object*>(this,8);
 if(at<unsigned>((void*)&((BFMEWeaponSetOwner*)owner)->getWeaponSetFlags(),0)&0x100) return;
 at<AttackMachine00278F20*>(this,0x30)->clear();
 bool flag=false;
 Object *helperOwner=at<Object*>(this,8);
 target=selectAttackTarget00278C30(target,helperOwner,&flag);
 if(!target) return;
 if(flag) {
  Rva000D1930 *list=new Rva000D1930;
  ((Rva0018BDD0*)list)->collect((BfmeContainOwner*)target,true);
  ((Rva00181EE0Owner*)at<AttackMachine00278F20*>(this,0x30))->setFrom((Rva00181EE0Inner*)list);
  m_sourceAt48=source;
  m_stateMachine->setState(23);
  delete list;
 } else {
  at<AttackMachine00278F20*>(this,0x30)->setTarget(target);
  m_sourceAt48=source;
  m_stateMachine->setState(11);
 }
 BfmeItemMD *weapon=((BfmeHolderMD*)at<Object*>(this,8))->bfmeFindMD(0);
 if(weapon) { weapon->limitAt34=shots; weapon->countAt20=0; }
 if(source==0 || source==1) ((BfmeHostXZ*)this)->bfmeFinishXZ(target);
}

enum WeaponChoiceCriteria {};
class Object { public: bool chooseBestWeaponForTarget(const Object*,WeaponChoiceCriteria,CommandSourceType); };
class BfmeSubEQT { public: char bfmeAEQT(); };
class Rva00278D50 {
public:
 void slot30(Object*,int,CommandSourceType);
 char pad[0x30]; AttackMachine00278F20 *m_stateMachine;
 char pad34[0x48-0x34]; CommandSourceType m_sourceAt48;
};
void Rva00278D50::slot30(Object *victim,int shots,CommandSourceType source)
{
 Object *object=at<Object*>(this,8);
 if(at<unsigned>((void*)&((BFMEWeaponSetOwner*)object)->getWeaponSetFlags(),0)&0x100) return;
 if(!victim || (at<unsigned char>(object,0x344)&8)) return;
 object->chooseBestWeaponForTarget(victim,(WeaponChoiceCriteria)0,source);
 BfmeItemMD *weapon=((BfmeHolderMD*)object)->bfmeFindMD(0);
 at<int>(object,0x3a4)=0;
 if(source==0 && (at<unsigned char>(victim,0x94)&0x20) && weapon && !weapon->templateAt04->bfmeAEQT())
  at<int>(object,0x3a4)=at<int>(victim,0x74);
 void *ai=at<void*>(object,0x204);
 if(ai && at<int>(ai,0x34)) return;
 m_stateMachine->clear();
 bool flag=false;
 victim=selectAttackTarget00278C30(victim,object,&flag);
 if(!victim) return;
 if(flag) {
  Rva000D1930 *list=new Rva000D1930;
  ((Rva0018BDD0*)list)->collect((BfmeContainOwner*)victim,true);
  ((Rva00181EE0Owner*)m_stateMachine)->setFrom((Rva00181EE0Inner*)list);
  m_sourceAt48=source;
  m_stateMachine->setState(23);
  delete list;
 } else {
  m_stateMachine->setTarget(victim);
  m_sourceAt48=source;
  m_stateMachine->setState(10);
 }
 if(weapon) {
  weapon->limitAt34=shots; weapon->countAt20=0;
  if(weapon->templateAt04->bfmeAEQT() && (source==0||source==1)) at<int>(this,0x1a4)=at<int>(victim,0x74);
 }
 if(source==0 || source==1) ((BfmeHostXZ*)this)->bfmeFinishXZ(victim);
}
