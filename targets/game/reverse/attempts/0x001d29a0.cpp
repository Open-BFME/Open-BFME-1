// ??0Object@@QAE@PBVThingTemplate@@ABV?$BitFlags@$0CN@@@PAVTeam@@@Z
// partial score=0.7906264719736222 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /vd1 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Complete native bank for RVA 0x001D29A0 / 4246 bytes; 889 masked differences.
// See identity_evidence/001D29A0-object-constructor-abi.md for ABI and bounded verdict.
#include "string_base.h"
template<> inline StringBase<char>::~StringBase(){releaseBuffer();}
template<> inline bool StringBase<char>::isEmpty()const{return !m_data || !m_data->length;}
template<> inline bool StringBase<char>::isNotEmpty()const{return m_data && m_data->length;}
#include "ascii_string.h"
#include <list>
#include <vector>
#include <bitset>
class ThingTemplate;class Team;class Object;class ModuleData;
template<int N> class BitFlags {public:std::bitset<N> m_bits;};
class Overridable {public:const Overridable*getFinalOverride()const;void*m_vtable;Overridable*m_nextOverride;};
class Snapshot {public:virtual ~Snapshot(){};virtual void snapshot(){};};
class GeometryInfo:public Snapshot {public:GeometryInfo(const GeometryInfo&);~GeometryInfo();char m_04[0x58];};
struct ModuleNugget {AsciiString m_name,m_tag;const ModuleData*m_data;int m_0c,m_10;};
class ModuleInfo {public:std::vector<ModuleNugget>m_modules;int getCount()const{return m_modules.size();}AsciiString getNthName(int)const;const ModuleData*getNthData(int i)const{return i>=0&&(unsigned)i<(unsigned)getCount()?m_modules[i].m_data:0;}};
class ThingTemplate:public Overridable {public:char m_08[0x20-8];AsciiString m_name;char m_24[0x60-0x24];GeometryInfo m_geometryInfo;char m_bc[12];BitFlags<224>m_kindOf;char m_e4[0x294-0xe4];ModuleInfo m_behaviorModuleInfo;char m_2a0[0x3a4-0x2a0];float m_3a4,m_3a8;int m_3ac;char m_3b0[0x424-0x3b0];unsigned m_occlusionDelay;float friend_calcVisionRange()const{return m_3a4;}float friend_calcShroudClearingRange()const{return m_3a8;}bool canPossiblyHaveAnyWeapon()const;bool isKindOf(int n)const{return m_kindOf.m_bits[n];}};
class Thing {public:Thing(const ThingTemplate*);virtual ~Thing();const ThingTemplate*m_template;char m_08[0x58];const ThingTemplate*getTemplate()const{const ThingTemplate*t=m_template;if(!t)return 0;if(t->m_nextOverride)t=(const ThingTemplate*)t->m_nextOverride->getFinalOverride();return t;}};
class Rva001D29A0Virtual {public:virtual void v0(){};virtual void v1(){};virtual void v2(){};virtual void v3(){};virtual void v4(){};};
class Rva001D29A0IfaceA {public:virtual void a0(){};};
class Rva001D29A0IfaceB {public:virtual void b0(){};};
class Rva001D29A0IfaceC {public:virtual void c0(){};};
class Rva001D29A0IfaceV:public Rva001D29A0IfaceA,public virtual Rva001D29A0Virtual {};
class Gen_001EACF0 {public:Gen_001EACF0();virtual ~Gen_001EACF0();char m_04[0x34];};
struct TriggerInfo {void*m_trigger;bool m_4,m_5,m_6,m_7;TriggerInfo():m_trigger(0),m_4(false),m_5(false),m_6(false),m_7(false){}};
struct Pair310{unsigned a,b;};
class BehaviorModule;class AIUpdateSetAttitudeShim;class ExperienceTracker;class SpecialAbilityUpdate;
enum SpecialPowerType {SPECIAL_2B=43};
struct Rva001D29A0Pair {int a,b;Rva001D29A0Pair():a(-1),b(-1){}};
class Object:public Thing,public Snapshot,public Rva001D29A0IfaceV,public Rva001D29A0IfaceB,public Rva001D29A0IfaceC {
public:Object(const ThingTemplate*,const BitFlags<86>&,Team*,unsigned);virtual ~Object();virtual void snapshot(){};virtual void a0(){};virtual void b0(){};virtual void c0(){};virtual void v0(){};
BehaviorModule*findModule(int key)const;virtual void setTeam(Team*);void setID(unsigned);void rva001CA2E0();SpecialAbilityUpdate*findSpecialAbilityUpdate(SpecialPowerType)const;
unsigned m_id,m_producerID,m_builderID;void*m_drawable;AsciiString m_name;Object*m_next,*m_prev;BitFlags<86>m_status;Rva001D29A0Pair m_9c,m_a4;GeometryInfo m_geometryInfo;GeometryInfo*m_108;void*m_10c;BitFlags<320>m_110;char m_138[0x30];int m_168;char m_16c[0x18];bool m_184,m_185,m_186;void*m_group;int m_18c,m_190;float m_visionRange,m_198,m_19c;int m_1a0;BitFlags<32>m_disabledMask;unsigned m_disabledTillFrame[11];BehaviorModule*m_1d4,*m_1d8,*m_1dc,*m_1e0,*m_defectionHelper,*m_1e8,*m_1ec;BehaviorModule**m_behaviors;bool m_1f4,m_1f5;BehaviorModule*m_1f8;void*m_contain,*m_body;AIUpdateSetAttitudeShim*m_ai;BehaviorModule*m_physics;void*m_20c;ExperienceTracker*m_experienceTracker;void*m_214,*m_218,*m_21c;float m_220;BitFlags<192>m_224;Team*m_team;AsciiString m_originalTeamName;unsigned m_indicatorColor;AsciiString m_248;unsigned m_24c,m_250,m_254,m_258;struct DLINK_TeamMemberList{Object*m_prev,*m_next;DLINK_TeamMemberList():m_prev(0),m_next(0){}~DLINK_TeamMemberList(){}}m_dlink_TeamMemberList;Gen_001EACF0 m_weaponSet;unsigned m_29c,m_2a0;int m_2a4;unsigned m_2a8,m_2ac,m_2b0,m_2b4,m_2b8,m_2bc;BitFlags<128>m_2c0;unsigned m_soleHealingBenefactorID,m_soleHealingBenefactorExpirationFrame;TriggerInfo m_triggerInfo[5];unsigned m_enteredOrExitedFrame;int m_304,m_308,m_30c;std::list<Pair310>m_310;int m_layer,m_318;unsigned m_31c,m_320,m_324,m_328,m_32c,m_330,m_334,m_338,m_33c;bool m_isSelectable,m_341,m_342;unsigned char m_scriptStatus,m_privateStatus;bool m_345;unsigned char m_numTriggerAreasActive;bool m_347,m_isReceivingDifficultyBonus;unsigned m_34c;std::vector<void*>m_350,m_35c;bool m_368,m_369,m_36a;unsigned m_36c;int m_370;std::vector<void*>m_374;unsigned m_380;bool m_384;unsigned m_388,m_38c,m_390[2],m_398;bool m_39c;unsigned m_3a0,m_3a4;bool m_3a8;int m_3ac;std::vector<void*>m_3b0;
};
enum ObjectID{INVALID_ID=0};class GameLogic {public:ObjectID allocateObjectID();void removeObjectFromLookupTable(Object*);void addObjectToLookupTable(Object*);void registerObject(Object*);char m_00[0x3c];unsigned m_frame;};extern GameLogic*TheGameLogic;
void Object::setID(unsigned id){if(m_id!=id){if(m_id)TheGameLogic->removeObjectFromLookupTable(this);m_id=id;if(m_id)TheGameLogic->addObjectToLookupTable(this);}}
enum NameKeyType{NAMEKEY_INVALID=0};class ModuleData:public Snapshot{public:NameKeyType m_moduleTagNameKey;unsigned m_08;void setModuleTagNameKey(NameKeyType k){m_moduleTagNameKey=k;}};
class Module {public:virtual ~Module();virtual void p1();virtual void p2();virtual void p3();virtual int getModuleNameKey()const;virtual void onObjectCreated();const ModuleData*m_data;};
class BehaviorModuleInterface {public:virtual void*getBody();virtual void*unused1();virtual void*getContain();virtual void*p3();virtual void*p4();virtual void*p5();virtual void*p6();virtual void*p7();virtual void*p8();virtual void*p9();virtual void*p10();virtual void*p11();virtual void*p12();virtual void*p13();virtual void*p14();virtual void*p15();virtual void*p16();virtual void*p17();virtual AIUpdateSetAttitudeShim*getAIUpdateInterface();};
class ObjectModule:public Module{public:Object*m_object;};
class BehaviorModule:public ObjectModule,public BehaviorModuleInterface{};
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER=0x3fffffff,UPDATE_SLEEP_NONE=1};class UpdateModuleInterface{public:virtual UpdateSleepTime update();};

class UpdateModule:public BehaviorModule,public UpdateModuleInterface{public:unsigned m_nextCallFrameAndPhase;int m_indexInLogic,m_pad;protected:void setWakeFrame(Object*,UpdateSleepTime);};
class ObjectHelper:public UpdateModule {public:ObjectHelper(Thing*,const ModuleData*);virtual ~ObjectHelper();};
struct SMCPair {unsigned a,b;};
class ObjectSMCHelper:public ObjectHelper{public:__forceinline ObjectSMCHelper(Thing*t,const ModuleData*d):ObjectHelper(t,d){}virtual ~ObjectSMCHelper();virtual UpdateSleepTime update();std::list<SMCPair>m_smcList;};
class ObjectRecoveryHelper:public ObjectHelper{public:__forceinline ObjectRecoveryHelper(Thing*t,const ModuleData*d):ObjectHelper(t,d){setWakeFrame(m_object,UPDATE_SLEEP_FOREVER);}virtual ~ObjectRecoveryHelper();virtual UpdateSleepTime update();};
class ObjectRepulsorHelper:public ObjectHelper{public:ObjectRepulsorHelper(Thing*t,const ModuleData*d):ObjectHelper(t,d){}virtual ~ObjectRepulsorHelper();virtual UpdateSleepTime update();};
class ObjectDefectionHelper:public ObjectHelper{public:ObjectDefectionHelper(Thing*t,const ModuleData*d):ObjectHelper(t,d){m_24=0;m_28=0;m_20=0;m_2c=false;}virtual ~ObjectDefectionHelper();virtual UpdateSleepTime update();unsigned m_20,m_24;float m_28;bool m_2c;};
class ObjectGuardingHelper:public ObjectHelper{public:ObjectGuardingHelper(Thing*,const ModuleData*);unsigned m_20;std::list<void*>m_24;};
class ObjectWeaponStatusHelper:public ObjectHelper{public:__forceinline ObjectWeaponStatusHelper(Thing*t,const ModuleData*d):ObjectHelper(t,d){setWakeFrame(m_object,UPDATE_SLEEP_NONE);}virtual ~ObjectWeaponStatusHelper();virtual UpdateSleepTime update();};
class FiringTracker:public UpdateModule {public:FiringTracker(Thing*,const ModuleData*);char m_20[0x3c];};
class ObjectSMCHelperModuleData:public ModuleData{};class ObjectRecoveryHelperModuleData:public ModuleData{};class ObjectRepulsorHelperModuleData:public ModuleData{};class ObjectDefectionHelperModuleData:public ModuleData{};class ObjectGuardingHelperModuleData:public ModuleData{};class ObjectWeaponStatusHelperModuleData:public ModuleData{};class FiringTrackerModuleData:public ModuleData{};
class NameKeyGenerator{public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator*TheNameKeyGenerator;
class TeamPrototype {public:char m_00[0x1d4];int m_initialTeamAttitude;AsciiString getAttackPriorityName()const;};class Team{public:void*m_00;TeamPrototype*m_prototype;const TeamPrototype*getPrototype(){return m_prototype;}};class Player{public:char m_00[0x230];Team*m_defaultTeam;};class PlayerList{public:char m_00[0x14];Player*m_neutralPlayer;};extern PlayerList*ThePlayerList;
class AIData{public:char m_00[0x64];bool m_enableRepulsors;};class AI{public:char m_00[0x14];AIData*m_data;};extern AI*TheAI;
enum ModuleType {MODULETYPE_BEHAVIOR=0};class ModuleFactory{public:Module*newModule(Thing*,const AsciiString&,const ModuleData*,ModuleType);};extern ModuleFactory*TheModuleFactory;
class AttackPriorityInfo {public:AsciiString getName()const;};
enum AttitudeType {ATTITUDE_UNUSED};class AIUpdateSetAttitudeShim{public:void setAttitude(AttitudeType);char m_00[0x70];const AttackPriorityInfo*m_attackInfo;};
class ScriptEngine{public:const AttackPriorityInfo*getAttackInfo(const AsciiString&);};extern ScriptEngine*TheScriptEngine;
class ExperienceTracker{public:ExperienceTracker(Object*);char m_00[0x30];};
class SpecialAbilityUpdate{public:char m_00[0xe4];bool m_e4;};
class Radar{public:void addObject(Object*);};extern Radar*TheRadar;
class Rva00594FD0 {public:void add(Object*);};class RvaGlobal12F4B98 {public:char m_00[0x2b8];Rva00594FD0 m_2b8;};extern RvaGlobal12F4B98*RvaGlobal_12F4B98;
inline BehaviorModule*Object::findModule(int key)const{BehaviorModule*m=0;for(BehaviorModule**b=m_behaviors;*b;++b)if((*b)->getModuleNameKey()==key){m=*b;break;}return m;}
Object::Object(const ThingTemplate*tt,const BitFlags<86>&status,Team*team,unsigned id):Thing(tt),m_id(0),m_producerID(0),m_builderID(0),m_drawable(0),m_next(0),m_prev(0),m_status(status),m_geometryInfo(tt->m_geometryInfo),m_108(&m_geometryInfo),m_10c((void*)tt->m_bc),m_168(0),m_184(false),m_185(false),m_186(false),m_group(0),m_18c(0),m_19c(0),m_1d4(0),m_1d8(0),m_1dc(0),m_1e0(0),m_defectionHelper(0),m_1e8(0),m_1ec(0),m_behaviors(0),m_1f4(false),m_1f5(false),m_contain(0),m_body(0),m_ai(0),m_physics(0),m_20c(0),m_experienceTracker(0),m_214(0),m_218(0),m_21c(0),m_220(-1.0f),m_team(0),m_indicatorColor(0),m_24c(0),m_250(0),m_254(0),m_258(0),m_29c(0),m_2a0(0),m_2a8(0),m_2ac(0),m_2b0(0),m_2b4(0),m_2b8(0),m_2bc(0),m_soleHealingBenefactorID(0),m_soleHealingBenefactorExpirationFrame(0),m_enteredOrExitedFrame(0),m_304(0),m_308(0),m_30c(0),m_layer(1),m_318(1),m_31c(0),m_320(0),m_324(0),m_328(0),m_32c(0),m_334(0),m_338(0),m_33c(0),m_341(false),m_342(false),m_scriptStatus(0),m_privateStatus(0),m_345(false),m_numTriggerAreasActive(0),m_347(false),m_isReceivingDifficultyBonus(false),m_34c(0),m_368(false),m_369(false),m_36a(false),m_36c(0),m_370(-1),m_380(0),m_384(false),m_388(0),m_38c(0),m_398(0),m_39c(false),m_3a0(0),m_3a4(0),m_3a8(false),m_3ac(-1)
{
    for(int i=0;i<11;++i)m_disabledTillFrame[i]=0;
    m_2a4=-1;((std::bitset<64>*)m_390)->reset();
    if(!TheGameLogic||!tt)return;
    if(tt->m_nextOverride)tt=(const ThingTemplate*)tt->m_nextOverride->getFinalOverride();
    const float vision=tt->friend_calcVisionRange();m_visionRange=vision;m_198=tt->friend_calcShroudClearingRange();if(m_198==-1.0f)m_198=vision;m_1a0=tt->m_3ac;
    AsciiString modName;
    if(id==0)setID(TheGameLogic->allocateObjectID());else setID(id);
    int totalModules=tt->m_behaviorModuleInfo.getCount()+7;
    m_behaviors=new BehaviorModule*[totalModules+1];
    for(int i=0;i<=totalModules;++i)m_behaviors[i]=0;
    BehaviorModule**curB=m_behaviors;
    const ModuleInfo&mi=tt->m_behaviorModuleInfo;
    setTeam(team?team:ThePlayerList->m_neutralPlayer->m_defaultTeam);
    static const NameKeyType smcKey=TheNameKeyGenerator->nameToKey("ModuleTag_SMCHelper");
    static ObjectSMCHelperModuleData smcData;smcData.setModuleTagNameKey(smcKey);
    m_1dc=new ObjectSMCHelper(this,&smcData);*curB++=m_1dc;
    static const NameKeyType recoveryKey=TheNameKeyGenerator->nameToKey("ModuleTag_RecoveryHelper");
    static ObjectRecoveryHelperModuleData recoveryData;recoveryData.setModuleTagNameKey(recoveryKey);
    m_1d8=new ObjectRecoveryHelper(this,&recoveryData);*curB++=m_1d8;
    if(TheAI&&TheAI->m_data->m_enableRepulsors&&getTemplate()->isKindOf(45)){
        static const NameKeyType repulsorKey=TheNameKeyGenerator->nameToKey("ModuleTag_RepulsorHelper");
        static ObjectRepulsorHelperModuleData repulsorData;repulsorData.setModuleTagNameKey(repulsorKey);
        m_1d4=new ObjectRepulsorHelper(this,&repulsorData);*curB++=m_1d4;
    }
    if(!tt->isKindOf(6)&&!tt->isKindOf(96)&&!tt->isKindOf(135)){
        static const NameKeyType defectionKey=TheNameKeyGenerator->nameToKey("ModuleTag_DefectionHelper");
        static ObjectDefectionHelperModuleData defectionData;defectionData.setModuleTagNameKey(defectionKey);
        m_defectionHelper=new ObjectDefectionHelper(this,&defectionData);*curB++=m_defectionHelper;
    }
    static const NameKeyType guardingKey=TheNameKeyGenerator->nameToKey("ModuleTag_GuardingHelper");
    static ObjectGuardingHelperModuleData guardingData;guardingData.setModuleTagNameKey(guardingKey);
    m_1e8=new ObjectGuardingHelper(this,&guardingData);*curB++=m_1e8;
    if(tt->canPossiblyHaveAnyWeapon()){
        static const NameKeyType wsKey=TheNameKeyGenerator->nameToKey("ModuleTag_WeaponStatusHelper");
        static ObjectWeaponStatusHelperModuleData wsData;wsData.setModuleTagNameKey(wsKey);
        m_1e0=new ObjectWeaponStatusHelper(this,&wsData);*curB++=m_1e0;
        static const NameKeyType firingKey=TheNameKeyGenerator->nameToKey("ModuleTag_FiringTrackerHelper");
        static FiringTrackerModuleData firingData;firingData.setModuleTagNameKey(firingKey);
        m_1ec=new FiringTracker(this,&firingData);*curB++=m_1ec;
    }
    for(int modIdx=0;modIdx<mi.getCount();++modIdx){
        modName=mi.getNthName(modIdx);if(modName.isEmpty())continue;
        BehaviorModule*newMod=(BehaviorModule*)TheModuleFactory->newModule(this,modName,mi.getNthData(modIdx),MODULETYPE_BEHAVIOR);*curB++=newMod;
        void*body=newMod->getBody();if(body)m_body=body;
        void*contain=newMod->getContain();if(contain)m_contain=contain;
        AIUpdateSetAttitudeShim*ai=newMod->getAIUpdateInterface();if(ai)m_ai=ai;
        static NameKeyType physicsKey=TheNameKeyGenerator->nameToKey("PhysicsBehavior");if(newMod->getModuleNameKey()==physicsKey)m_physics=newMod;
    }
    *curB=0;
    static NameKeyType squishKey=TheNameKeyGenerator->nameToKey("SquishCollide");
    if(findModule(squishKey))m_1f4=true;
    static NameKeyType emotionKey=TheNameKeyGenerator->nameToKey("EmotionTrackerUpdate");
    m_1f8=findModule(emotionKey);
    SpecialAbilityUpdate*ability=findSpecialAbilityUpdate(SPECIAL_2B);if(ability&&ability->m_e4)m_1f5=true;
    AIUpdateSetAttitudeShim*ai=m_ai;
    if(ai){
        ai->setAttitude((AttitudeType)m_team->getPrototype()->m_initialTeamAttitude);
        if(m_team&&m_team->getPrototype()&&m_team->getPrototype()->getAttackPriorityName().isNotEmpty()){
            AsciiString name=m_team->getPrototype()->getAttackPriorityName();
            const AttackPriorityInfo*info=TheScriptEngine->getAttackInfo(name);
            if(info&&info->getName().isNotEmpty())ai->m_attackInfo=info;
        }
    }
    m_experienceTracker=new ExperienceTracker(this);
    m_248=tt->m_name;
    for(BehaviorModule**b=m_behaviors;*b;++b)(*b)->onObjectCreated();
    m_isSelectable=tt->isKindOf(1);m_341=true;
    TheRadar->addObject(this);TheGameLogic->registerObject(this);
    if(RvaGlobal_12F4B98)RvaGlobal_12F4B98->m_2b8.add(this);
    m_330=TheGameLogic->m_frame+tt->m_occlusionDelay;
    rva001CA2E0();
}
