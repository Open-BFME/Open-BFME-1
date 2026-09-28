// ActiveBody constructor RVA00211A50 / 601B; factory ILT00025509 and derived constructors prove identity.
// BFME primary layout: health18/1C/20; DamageInfo40..9B; vectorC0; armor flagsD0.
// EH states unwind BodyModule then the three-pointer vector. Capacity is a constructed
// allocator-proxy subobject, as in native STLport; it controls the state-zero store.
// Retain the native armor null branch even though both arms reduce to a store: it
// determines the final temporary register. DamageInfo subconstructors are inline.
// cl: /DNDEBUG /MD /EHsc
class Thing;class ModuleData;
class ObjectModule { public: ObjectModule(Thing*,const ModuleData*);virtual ~ObjectModule();const ModuleData *m_data;Thing *m_object; };
class BehaviorModuleInterface { public: virtual void facet(); };
class BodyModuleInterface { public: BodyModuleInterface():field14(1.0f){} virtual void body()=0;float field14; };
class __declspec(novtable) BodyModule:public ObjectModule,public BehaviorModuleInterface,public BodyModuleInterface { public:BodyModule(Thing*t,const ModuleData*d):ObjectModule(t,d){} ~BodyModule(); };
struct CtorTriple00211A50 { float x,y,z;void zero(){x=0.0f;y=0.0f;z=0.0f;} };
class DamageInfoInput { public:
 virtual void xfer();unsigned field04;unsigned short field08;int field0C,field10,field14;float field18;bool field1C,field1D;unsigned field20,field24,field28;CtorTriple00211A50 field2C;float field38,field3C,field40,field44;
 __forceinline DamageInfoInput(){field04=0;field08=0;field0C=22;field10=15;field14=0;field18=0;field1C=false;field1D=true;field20=0;field24=0;field28=0;field2C.zero();field38=0;field3C=0;field40=0;field44=1.0f;}
};
class DamageInfoOutput { public:virtual void xfer();float actual,clipped;bool noEffect;__forceinline DamageInfoOutput():actual(0),clipped(0),noEffect(false){} };
class DamageInfo { public:__forceinline DamageInfo(){} virtual void xfer();DamageInfoInput in;DamageInfoOutput out; };
struct CtorCapacity00211A50 { CtorCapacity00211A50():value(0){} void *value; };
class CtorVector0020F660 { public:CtorVector0020F660():begin(0),end(0),capacity(){}~CtorVector0020F660();CtorVector0020F660& operator=(const CtorVector0020F660&);void *begin,*end;CtorCapacity00211A50 capacity; };
struct ActiveData00211A50 { char prefix[8];float maxHealth,initialHealth,maxDamaged,maxReallyDamaged;char gap18[0x10];bool defaults;char gap29[0x27];CtorVector0020F660 vector; };
struct GlobalData {char prefix[0x19c];float m_unitDamagedThresh,m_unitReallyDamagedThresh;};extern GlobalData *TheGlobalData;
template<int N> class BitFlags { public: BitFlags():bits(0){}unsigned bits; };
class ArmorTemplate;class DamageFX;
class Armor { public:Armor(const ArmorTemplate *t=0):m_template(t){} const ArmorTemplate *m_template; };
class ArmorTemplateSet { public: BitFlags<11> flags;const ArmorTemplate *armor;const DamageFX *fx; };
class Overridable { public:virtual ~Overridable();const Overridable *getFinalOverride()const {if(next)return next->getFinalOverride();return this;}Overridable *next; };
class ThingTemplate:public Overridable {public:const ArmorTemplateSet *findArmorTemplateSet(const BitFlags<11>&)const;};
template<class T>class OVERRIDE {public:const T *value;operator const T*()const {if(!value)return 0;return (T*)value->getFinalOverride();}};
class Thing {public:virtual ~Thing();OVERRIDE<ThingTemplate> tmpl;const ThingTemplate *getTemplate()const{return tmpl;}};
class ActiveBody:public BodyModule {public:
 ActiveBody(Thing*,const ModuleData*);virtual ~ActiveBody();virtual void facet();virtual void body();
 float m_currentHealth,m_prevHealth,m_maxHealth,field24,field28,m_initialHealth;
 int m_curDamageState,field34,m_nextDamageFXTime,m_lastDamageFXDone;
 DamageInfo m_lastDamageInfo;unsigned m_lastDamageTimestamp,m_lastHealingTimestamp;bool m_frontCrushed,m_backCrushed,m_lastDamageCleared,m_indestructible;void *m_particleSystems;float fieldAC[4];bool fieldBC[4];CtorVector0020F660 vector;unsigned fieldCC;BitFlags<11> m_curArmorSetFlags;const ArmorTemplateSet *m_curArmorSet;Armor m_curArmor;const DamageFX *m_curDamageFX;
 void setCorrectDamageState(bool);
};
ActiveBody::ActiveBody(Thing *thing,const ModuleData *data):BodyModule(thing,data),m_curDamageState(0),field34(0),m_nextDamageFXTime(0),m_lastDamageFXDone(15),m_lastDamageTimestamp(-1),m_lastHealingTimestamp(-1),m_frontCrushed(false),m_backCrushed(false),m_lastDamageCleared(false),m_indestructible(false),m_particleSystems(0),fieldCC(0),m_curArmorSet(0),m_curArmor(0),m_curDamageFX(0) {
 const ActiveData00211A50 *md=(const ActiveData00211A50*)m_data;
 m_prevHealth=md->initialHealth;m_maxHealth=md->maxHealth;
 vector=md->vector;
 float reciprocal=1.0f/m_maxHealth;
 field24=reciprocal*md->maxDamaged;field28=reciprocal*md->maxReallyDamaged;
 m_initialHealth=m_currentHealth=(md->initialHealth!=-1.0f ? md->initialHealth:md->maxHealth);
 if(md->defaults) {if(field24==0.0f)field24=TheGlobalData->m_unitDamagedThresh;if(field28==0.0f)field28=TheGlobalData->m_unitReallyDamagedThresh;}
 for(int i=0;i<4;++i) {fieldAC[i]=0.0f;fieldBC[i]=false;}
 const ArmorTemplateSet *set=m_object->getTemplate()->findArmorTemplateSet(m_curArmorSetFlags);
 if(set && set!=m_curArmorSet) {if(set->armor){m_curArmor=Armor(set->armor);}else{m_curArmor.m_template=0;}m_curDamageFX=set->fx;m_curArmorSet=set;}
 setCorrectDamageState(false);
}
