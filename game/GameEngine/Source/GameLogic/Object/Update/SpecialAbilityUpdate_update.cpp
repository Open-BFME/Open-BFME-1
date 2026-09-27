// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002AA9D0, 1007 bytes: SpecialAbilityUpdate update interface at +0x10.
// Identity: ZH update phase machine plus BFME target tracking/abort additions.
// The address-qualified interface keeps the witnessed incoming secondary-base
// receiver separate from the full-object layout used by the virtual calls.
// Include the existing byte-verified readiness helper: MSVC must see that it
// preserves ECX across calls before startFacing and the sleep tail call.
// Its legacy integer return is consumed as AL, exactly as retail requires.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
struct Coord3D { float x,y,z; };
class Object; class SpecialAbilityUpdate;
enum CommandSourceType { DummyCommand002AA9D0 }; enum SpecialPowerType { DummyPower002AA9D0 };
class AICommandInterface {public:void aiIdle(CommandSourceType);};
class AI002AA9D0 {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
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
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual unsigned char isIdle();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual void slot111();
virtual void slot112();
virtual void slot113();
virtual void slot114();
virtual void slot115();
virtual void slot116();
virtual void slot117();
virtual void slot118();
virtual void slot119();
virtual void slot120();
virtual void slot121();
virtual void slot122();
virtual void slot123();
virtual void slot124();
virtual void slot125();
virtual void slot126();
virtual void slot127();
virtual int getLastCommandSource();
};
class Object {public:
 void notifyModelConditionChanged();
 char pad000[0x38]; Coord3D position; char pad044[0xcc]; _STL::bitset<320> conditions;
 char pad138[0xcc]; AI002AA9D0* ai; char pad208[0x34]; void* team;
 char pad240[0x104]; unsigned flags344;
 __forceinline void setCondition(int n){if(!conditions.test(n)){conditions._Unchecked_set(n);notifyModelConditionChanged();}}
};
class GameLogic {public:Object* findObjectByID(int);char pad000[0x3c];unsigned frame;};extern GameLogic* TheGameLogic;
class SpecialPowerTemplate {public:SpecialPowerType getSpecialPowerType()const;};
class SpecialAbilityUpdateModuleData {public:
 char pad000[0x1d8]; SpecialPowerTemplate* m_specialPowerTemplate;
 char pad1dc[0x6a]; unsigned char m_alwaysValidateSpecialObjects;char pad247[3];unsigned char field24a;char field24b;unsigned char field24c;
};
struct BfmeThingFEC {int bfmeGoFEC();char pad000[4];SpecialAbilityUpdateModuleData* data;char pad008[0x24];int field02c;char pad030[0xac];unsigned char active;};
inline int BfmeThingFEC::bfmeGoFEC(){if(!active){if(!data->m_alwaysValidateSpecialObjects){if(field02c==0)return 0x3fffffff;}}return 1;}
struct BfmeA999 {char bfmeGo999A();};
#include "Rva002A59F0BfmeReady.cpp"
class BfmeThing5F30 {public:unsigned char bfmeReady5F30()const;};
class BfmeThingXR {public:unsigned char bfmeReadyXR()const;};
class Rva002A7DB0 {public:bool check()const;};
class SpecialAbilityUpdate {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void onExit(bool,bool);
virtual unsigned char approachTarget();
virtual void startPreparation();
virtual unsigned char continuePreparation();
virtual void triggerAbilityEffect();
virtual void slot40();
virtual void finishAbility();
virtual unsigned char handlePackingProcessing();
virtual void startPacking(bool);
virtual void startUnpacking();
 void validateSpecialObjects();void endPreparation();void rva002A7E90();unsigned char isWithinStartAbilityRange();void startFacing();
 SpecialAbilityUpdateModuleData* data;Object* object;char pad00c[0x20];unsigned field02c;int packingState;
 char pad034[0x74];unsigned prepFrames;int targetID;Coord3D targetPos;char pad0bc[0x20];unsigned char active;
 char pad0dd[5];unsigned char withinRange;char pad0e3;unsigned char field0e4;unsigned char field0e5;

};
class SpecialAbilityUpdateUpdateInterface002AA9D0 {public:int update();
 SpecialAbilityUpdateModuleData* getData()const{return *(SpecialAbilityUpdateModuleData**)((char*)this-0xc);}
 Object* getObject()const{return *(Object**)((char*)this-8);}
 char pad000[0x1c];unsigned field02c;int packingState;char pad024[0x74];unsigned prepFrames;int targetID;Coord3D targetPos;char pad0ac[0x20];unsigned char active;char pad0cd[5];unsigned char withinRange;char pad0d3;unsigned char field0e4;unsigned char field0e5;
};
int SpecialAbilityUpdateUpdateInterface002AA9D0::update(){
 SpecialAbilityUpdate* base=(SpecialAbilityUpdate*)((char*)this-0x10);
 const SpecialAbilityUpdateModuleData* d=getData();
 base->validateSpecialObjects();
 if(getObject()->flags344&1){base->onExit(true,true);return ((BfmeThingFEC*)base)->bfmeGoFEC();}
 if(field02c && field02c<TheGameLogic->frame)base->slot40();
 if(!active)return ((BfmeThingFEC*)base)->bfmeGoFEC();
 AI002AA9D0* ai=getObject()->ai;
 if(!ai){base->onExit(false,true);return ((BfmeThingFEC*)base)->bfmeGoFEC();}
 if(targetID){Object* target=TheGameLogic->findObjectByID(targetID);if(target)targetPos=target->position;}
 if(ai->getLastCommandSource()!=2){base->onExit(false,true);return ((BfmeThingFEC*)base)->bfmeGoFEC();}
 bool shouldAbort=false;
 if(d->field24a&&!field0e4){field0e4=true;getObject()->setCondition(124);}
 if(d->m_specialPowerTemplate->getSpecialPowerType()==43){
 Object* target=TheGameLogic->findObjectByID(targetID);
 if(target&&(target->flags344&1)&&ai->isIdle())shouldAbort=true;
 if(ai->isIdle()&&field0e5)shouldAbort=true;
 }
 if(base->handlePackingProcessing()&&!shouldAbort)return ((BfmeThingFEC*)base)->bfmeGoFEC();
 if(targetID){Object* target=TheGameLogic->findObjectByID(targetID);
 if(target){if(target->flags344&1)shouldAbort=true;
 else switch(d->m_specialPowerTemplate->getSpecialPowerType()) {case 26:case 29:if(target->team==getObject()->team)shouldAbort=true;break;}}
 }
 if(shouldAbort&&!d->field24c){((AICommandInterface*)((char*)ai+0x20))->aiIdle((CommandSourceType)2);base->onExit(false,true);return ((BfmeThingFEC*)base)->bfmeGoFEC();}
 if(prepFrames){
 --prepFrames;
 if(!prepFrames){base->triggerAbilityEffect();
 if(((Rva002A7DB0*)base)->check())base->rva002A7E90();
 else{base->endPreparation();if(((BfmeThing5F30*)base)->bfmeReady5F30())base->startPacking(true);else base->finishAbility();}
 }else if(!base->continuePreparation()){
 base->endPreparation();if(((BfmeThing5F30*)base)->bfmeReady5F30())base->startPacking(false);else base->finishAbility();
 }
 }else if(base->isWithinStartAbilityRange()){
 withinRange=true;
 if(!((BfmeA999*)base)->bfmeGo999A()&&(unsigned char)((Gen_002A59F0*)base)->bfmeReady()){base->startFacing();return ((BfmeThingFEC*)base)->bfmeGoFEC();}
 if(((BfmeA999*)base)->bfmeGo999A()&&(unsigned char)((Gen_002A59F0*)base)->bfmeReady())return ((BfmeThingFEC*)base)->bfmeGoFEC();
 if(((BfmeThingXR*)base)->bfmeReadyXR()){base->startUnpacking();return ((BfmeThingFEC*)base)->bfmeGoFEC();}
 if(packingState==4){base->startPreparation();if(!prepFrames){base->triggerAbilityEffect();base->endPreparation();if(((BfmeThing5F30*)base)->bfmeReady5F30())base->startPacking(true);else base->finishAbility();}}
 }else if(ai->isIdle())base->approachTarget();
 return ((BfmeThingFEC*)base)->bfmeGoFEC();
}
