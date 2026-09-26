// ?apply@Rva00212980Owner@@QAEXMPAUDamageInfo@@@Z
// RVA 00212980, DelayedDeathBody secondary BodyModule interface slot +80.
// Negative offsets address the primary module data and object through the
// unchanged interface receiver; the qualified owner preserves that provenance.
// Both upgrade predicates are evaluated. A transition clears the incoming
// damage flag and zeroes the amount according to module flag68.
class UpgradeTemplate; class Module; struct DamageInfo { unsigned char before20[0x20]; unsigned char flag20; };
class Player { public: bool hasUpgradeComplete(const UpgradeTemplate*); };
class Object { public:
 Player *getControllingPlayer() const;
 bool hasUpgrade(const UpgradeTemplate*) const;
 Module *findModule(int) const;
};
class NameKeyGenerator { public: unsigned int nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
class LifetimeUpdate { public: void setLifetimeRange(unsigned int,unsigned int); };
class FXList { public: static void doFXObj(const FXList*,const Object*,const Object*); };
struct Rva00212980Data {
 unsigned char prefix[0x64]; unsigned int time64; bool flag68;
 unsigned char gap69[3]; const FXList *fx6c; bool flag70;
 unsigned char gap71[3]; const UpgradeTemplate *upgrade74;
};
struct Rva002147E0Owner { void apply(float,DamageInfo*); };
struct Rva00212980Owner {
 // Unused virtual slot signatures are placeholders, not ABI claims.
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual float health();
 unsigned char beforeD0[0xcc]; unsigned char started; unsigned char checked;
 Rva00212980Data *data() const {return *(Rva00212980Data**)((char*)this-12);}
 Object *object() const {return *(Object**)((char*)this-8);}
 void apply(float,DamageInfo*);
};
void Rva00212980Owner::apply(float amount,DamageInfo *info)
{
 Object *obj=object();
 const Rva00212980Data *module=data();
 Player *player=obj->getControllingPlayer();
 bool transitioned=false;
 if(!started) {
  if(!(checked && info && info->flag20==1)) {
   if(!module->flag70) goto finish;
   if(!(health()+amount<=0.0f)) goto finish;
  }
  if(module->upgrade74) {
   bool playerComplete=player && player->hasUpgradeComplete(module->upgrade74);
   bool objectComplete=obj->hasUpgrade(module->upgrade74);
   if(!playerComplete && !objectComplete) goto finish;
  }
  LifetimeUpdate *lifetime=(LifetimeUpdate*)object()->findModule(TheNameKeyGenerator->nameToKey("LifetimeUpdate"));
  if(lifetime) lifetime->setLifetimeRange(module->time64,module->time64);
  if(!started) FXList::doFXObj(module->fx6c,object(),0);
  info->flag20=0;
  started=1;
  transitioned=true;
 }
finish:
 if((checked || started) && (data()->flag68 || transitioned)) amount=0;
 if(started==1 && info && info->flag20==1) amount=-health();
 ((Rva002147E0Owner*)this)->apply(amount,info);
}
