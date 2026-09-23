// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail RVA 0032D720. Typed reconstruction of its complete switch dispatcher.
// ScriptConditions identity: installed vtable 010E1F44 slot 9 -> ILT 0000D9E0.
// Address-qualified entry avoids the already misnamed ledger row at 003307E0.
// Landed callee symbols are declared exactly as their existing source defines them.
// Address-qualified inline call views preserve the dispatcher's observed ABI when
// a legacy declaration discards AL or spells parameter words differently. They
// bind only existing symbols; they do not introduce names, pins or body claims.
// The raw/member union is the existing ScriptActions_d_002f5ca0.cpp construct.
#include "PreRTS.h"
#include "GameLogic/Scripts.h"
// BFME call declarations reused from the landed sources cited below. The ZH
// ScriptConditions header lacks BFME-only arms and differs in two prototypes.
// This TU models no ScriptConditions fields or virtual layout through this class;
// the witnessed virtual calls have separate address-qualified views below.
class ScriptConditions {
protected:
    // 003240F0: ScriptConditionsCastleObjectTypes.cpp
    bool evaluateRva003240F0(Parameter*, Parameter*);
    // 00322E80: ScriptConditionsNamedBaseUnpackableForPlayer.cpp
    bool evaluateNamedBaseUnpackableForPlayer(Parameter*, Parameter*);
    // 00324670: ScriptConditionsTriggerAreas.cpp
    bool evaluateTeamInsideAreaPartially(class Parameter *,class Parameter *,class Parameter *);
    // 003247A0: ScriptConditionsTriggerAreas.cpp
    bool evaluateNamedInsideArea(class Parameter *,class Parameter *);
    // 003245A0: ScriptConditionsTeamState.cpp
    bool evaluateIsDestroyed(class Parameter *);
    // 00324600: ScriptConditionsTeamCompare.cpp
    bool evaluateTeamCountCompare(class Parameter *,class Parameter *,class Parameter *);
    // 00327560: ScriptConditionsNamedUnit.cpp
    bool evaluateNamedUnitRankLevel(class Parameter *,class Parameter *);
    // 00322300: ScriptConditions.cpp
    bool evaluateNamedUnitDestroyed(class Parameter *);
    // 00322390: ScriptConditions.cpp
    bool evaluateNamedUnitDying(class Parameter *);
    // 003223E0: ScriptConditions.cpp
    bool evaluateNamedUnitTotallyDead(class Parameter *);
    // 00322350: ScriptConditions.cpp
    bool evaluateNamedUnitExists(class Parameter *);
    // 0032A2E0: ScriptConditions_evaluateHasUnits_Thunk.cpp
    bool evaluateHasUnits(class Parameter *);
    // 0032AFD0: ScriptConditionsTeamState.cpp
    bool evaluateTeamStateIs(class Parameter *,class Parameter *);
    // 0032B0B0: ScriptConditionsTeamState.cpp
    bool evaluateTeamStateIsNot(class Parameter *,class Parameter *);
    // 00324AA0: ScriptConditions.cpp
    bool evaluateNamedOutsideArea(class Parameter *,class Parameter *);
    // 00324AC0: ScriptConditionsTriggerAreas.cpp
    bool evaluateTeamInsideAreaEntirely(class Parameter *,class Parameter *,class Parameter *);
    // 00324BD0: ScriptConditions.cpp
    bool evaluateTeamOutsideAreaEntirely(class Parameter *,class Parameter *,class Parameter *);
    // 00327660: ScriptConditionsNamedByType.cpp
    bool evaluateNamedAttackedByType(class Parameter *,class Parameter *);
    // 00324C30: ScriptConditionsTeamMembers.cpp
    bool evaluateTeamAttackedByPlayer(class Parameter *,class Parameter *);
    // 00322510: ScriptConditions.cpp
    bool evaluateNamedCreated(class Parameter *);
    // 00324D00: ScriptConditionsTeamState.cpp
    bool evaluateTeamCreated(class Parameter *);
    // 00322530: ScriptConditionsPlayerMask.cpp
    bool evaluatePlayerHasCredits(class Parameter *,class Parameter *,class Parameter *);
    // 00327D30: ScriptConditions.cpp; dispatcher case 52 is ENEMY_SIGHTED.
    bool evaluateEnemySighted(class Parameter *,class Parameter *,class Parameter *);
    // 003222B0: ScriptConditions.cpp
    bool evaluateBridgeRepaired(class Parameter *);
    // 00322260: ScriptConditions.cpp
    bool evaluateBridgeBroken(class Parameter *);
    // 00328470: ScriptConditionsTeamMembers.cpp
    bool evaluateRva00328470(class Parameter *,class Parameter *);
    // 003226E0: ScriptConditionsNamedContain.cpp
    unsigned char evaluateNamedContainEmpty(class Parameter *);
    // 00322780: ScriptConditionsPlayerMask.cpp
    bool evaluateNamedOwnedByPlayer(class Parameter *,class Parameter *);
    // 00324D40: ScriptConditionsTeamCompare.cpp
    bool evaluateTeamOwnedByPlayer(class Parameter *,class Parameter *);
    // 00328590: ScriptConditionsPlayerMask.cpp
    bool evaluatePlayerHasNOrFewerFactionBuildings(class Parameter *,class Parameter *);
    // 00328680: ScriptConditionsPlayerHasNOrFewerBases.cpp
    bool evaluatePlayerHasNOrFewerBases(class Parameter *,class Parameter *);
    // 0032B390: ScriptConditionsNamedUnit.cpp
    bool evaluateNamedReachedWaypointsEnd(class Parameter *,class Parameter *);
    // 0032B520: ScriptConditions_evaluateTeamReachedWaypointsEnd.cpp
    bool evaluateTeamReachedWaypointsEnd(class Parameter *,class Parameter *);
    // 0032B840: ScriptConditionsNamedEnteredArea.cpp
    bool evaluateNamedEnteredArea(class Parameter *,class Parameter *);
    // 00324DE0: ScriptConditionsTriggerAreas.cpp
    bool evaluateNamedExitedArea(class Parameter *,class Parameter *);
    // 00324E40: ScriptConditionsTriggerAreas.cpp
    bool evaluateTeamEnteredAreaEntirely(class Parameter *,class Parameter *,class Parameter *);
    // 00324ED0: ScriptConditionsTriggerAreas.cpp
    bool evaluateTeamEnteredAreaPartially(class Parameter *,class Parameter *,class Parameter *);
    // 00324F60: ScriptConditionsTriggerAreas.cpp
    bool evaluateTeamExitedAreaEntirely(class Parameter *,class Parameter *,class Parameter *);
    // 00324FF0: ScriptConditionsTriggerAreas.cpp
    bool evaluateTeamExitedAreaPartially(class Parameter *,class Parameter *,class Parameter *);
    // 00323090: BfmeConv895.cpp
    bool evaluateMultiplayerPlayerDefeat(void);
    // 00322920: ScriptConditions.cpp
    bool evaluateAudioHasCompleted(class Parameter *);
    // 003229B0: ScriptConditionsPowerAndUpgradeFromUnit.cpp
    bool evaluatePlayerSpecialPowerFromUnitTriggered(class Parameter *,class Parameter *,class Parameter *);
    // 00322A60: ScriptConditionsPowerAndUpgradeFromUnit.cpp
    bool evaluatePlayerSpecialPowerFromUnitMidway(class Parameter *,class Parameter *,class Parameter *);
    // 00322B10: ScriptConditionsPowerAndUpgradeFromUnit.cpp
    bool evaluatePlayerSpecialPowerFromUnitComplete(class Parameter *,class Parameter *,class Parameter *);
    // 00322D10: ScriptConditionsScienceAcquired.cpp
    bool evaluateScienceAcquired(class Parameter *,class Parameter *);
    // 00322DA0: ScriptConditionsSciencePurchasePoints.cpp
    bool evaluateSciencePurchasePoints(class Parameter *,class Parameter *);
    // 00322E10: ScriptConditionsPlayerHasPower.cpp
    bool evaluatePlayerHasPower(class Parameter *);
    // 00322BC0: ScriptConditionsPowerAndUpgradeFromUnit.cpp
    bool evaluateUpgradeFromUnitComplete(class Parameter *,class Parameter *,class Parameter *);
    // 003232D0: ScriptConditionsPlayerMask.cpp
    bool evaluatePlayerDestroyedNOrMoreBuildings(class Parameter *,class Parameter *,class Parameter *);
    // 00323340: ScriptConditions.cpp
    bool evaluateUnitHasEmptied(class Parameter *);
    // 003230C0: ScriptConditionsPlayerMask.cpp
    bool evaluatePlayerHasComparisonPercentPower(class Parameter *,class Parameter *,class Parameter *);
    // 003231E0: ScriptConditions.cpp
    bool evaluateRva003231E0(class Parameter *,class Parameter *,class Parameter *);
    // 0032BB90: ScriptConditionsTeamMembers.cpp
    bool evaluateTeamHasObjectStatus(class Parameter *,class Parameter *,bool);
    // 00329160: ScriptConditionsPlayerMask.cpp
    bool evaluateSkirmishPlayerIsFaction(class Parameter *,class Parameter *);
    // 0032D300: ScriptConditions_evaluateSkirmishSuppliesWithinDistancePerimeter_Thunk.cpp
    bool evaluateSkirmishSuppliesWithinDistancePerimeter(class Parameter *,class Parameter *,class Parameter *,class Parameter *);
    // 00325680: ScriptConditionsTriggerAreas.cpp
    bool evaluateSkirmishNamedAreaExists(class Parameter *,class Parameter *);
    // 0032C400: BfmeScriptCondAreaGate.cpp
    bool bfmeAreaGate(class Parameter *,class Parameter *,class Parameter *);
    // 003258E0: ScriptConditions_evaluateMusicHasCompleted_Bfme.cpp
    bool evaluateMusicHasCompleted(class Parameter *,class Parameter *);
    // 00323650: ScriptConditions.cpp
    bool evaluateRva00323650(class Condition *,class Parameter *,class Parameter *);
    // 003237F0: ScriptConditionsNamedUnit.cpp
    bool evaluateIsSiegeAttachedToWall(class Parameter *);
    // 003260E0: ScriptConditionsCamera.cpp
    bool evaluateCameraHitSpecificSplineWaypoint(class Parameter *);
    // 00326130: ScriptConditionsCamera.cpp
    bool evaluateCameraEnteredArea(class Parameter *);
    // 00325D00: ScriptConditions_evaluateCounterSeconds.cpp
    bool evaluateCounterSeconds(class Condition *);
    // 00323B70: ScriptConditionsCompare.cpp
    bool evaluateDistanceBetweenObjects(class Parameter *,class Parameter *,class Parameter *,class Parameter *);
    // 00325E50: ScriptConditionsTeamCompare.cpp
    bool evaluateTeamCachedFloatCompare(class Parameter *,class Parameter *,class Parameter *,class Parameter *);
    // 00323CD0: ScriptConditionsNamedContain.cpp
    bool evaluateNamedHasFreeContainerSlots(class Parameter *);
    // 00325FC0: ScriptConditionsNamedUnit.cpp
    bool evaluateRva00325FC0(class Parameter *,class Parameter *);
    // 00323D50: ScriptConditionsPlayerMask.cpp
    bool evaluatePlayerCompareLightPoints(class Parameter *,class Parameter *,class Parameter *);
    // 003262C0: ScriptConditionsHasCommandPointsToBuildTeam.cpp
    bool evaluateHasCommandPointsToBuildTeam(class Parameter *,class Parameter *);
    // 0032C460: ScriptConditionsCanBuildAtBase.cpp
    bool evaluateCanBuildAtBase(class Parameter *,class Parameter *);
    // 00323E50: ScriptConditionsCanBuildAtBase.cpp
    bool evaluateCanBuildObjectTypeAtBase(class Parameter *,class Parameter *,class Parameter *);
    // 003297F0: ScriptConditionsPlayerMask.cpp
    bool evaluatePlayerHasKilledKindOfUnits(class Parameter *,class Parameter *,class Parameter *);
    // 00326660: ScriptConditionsPlayerHasKilledTypeUnits.cpp
    bool evaluatePlayerHasKilledTypeUnits(class Parameter *,class Parameter *,class Parameter *);
    // 00329950: ScriptConditionsNamedByType.cpp
    bool evaluateNamedDestroyedByType(class Parameter *,class Parameter *);
    // 003267B0: ScriptConditionsPathfinding.cpp
    bool evaluateNamedCanPathToWaypoint(class Parameter *,class Parameter *);
    // 00326830: ScriptConditionsPathfinding.cpp
    bool evaluateTeamCanPathToWaypoint(class Parameter *,class Parameter *);
    // 003268D0: ScriptConditionsPathfinding.cpp
    bool evaluateTeamCanPathToNamed(class Parameter *,class Parameter *);
    // 00326960: ScriptConditionsTeamState.cpp
    bool evaluateTeamHasNamed(class Parameter *,class Parameter *);
    // 00324020: ScriptConditionsCompare.cpp
    bool evaluateUnitHealth(class Parameter *,class Parameter *,class Parameter *);
    // 003242F0: ScriptConditions.cpp
    bool evaluateIsBuildingEmpty(class Parameter *);
    // 00324390: ScriptConditionsCompare.cpp
    bool evaluateCompareNumPlayersInGame(class Parameter *,class Parameter *);
    // 0032CB00: ScriptConditionsEvaluateUnitHasToggledWeapon.cpp
    bool evaluateUnitHasToggledWeapon(class Parameter *,class Parameter *);
    // 00326DA0: ScriptConditionsRva00326DA0.cpp
    bool rva00326da0(class Parameter *,class Parameter *);
    // 0032CCC0: ScriptConditionsAnyUnitsUsingBloodthirsty.cpp
    bool evaluateAnyUnitsUsingBloodthirsty(class Parameter *);
    // 00326C00: ScriptConditionsRva00326C00.cpp
    bool rva00326c00(class Parameter *,class Parameter *);
};

struct BfmeBitRequest;
struct BfmeSrcVJZ;
struct BfmeT1089;
struct BfmeT1090;
struct BfmeThingDEE;
struct BfmeThingDEF;
struct BfmeThingDEG;
struct BfmeYVJZ;

// 00322100: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsScienceAcquired.cpp
extern char __stdcall bfmeGo1091C(int);
// 003221B0: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsScienceAcquired.cpp
extern char __stdcall bfmeGo1091B(int);
// 00327940: Code/GameEngine/Source/Common/BfmeConv1094.cpp
extern char __stdcall bfmeGo1094A(int,int);
// 003283C0: Code/GameEngine/Source/Common/BfmeConv1092.cpp
extern char __stdcall bfmeGo1092B(int,int);
// 00322630: Code/GameEngine/Source/Common/BfmeConv1092.cpp
extern char __stdcall bfmeGo1092A(int,int);
// 00322810: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsSciencePurchasePoints.cpp
extern char __stdcall bfmeGo1089C(struct BfmeT1089 *,int);
// 00322880: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerHasPower.cpp
extern char __stdcall bfmeGo1090B(int);
// 003228F0: Code/GameEngine/Source/Common/BfmeConv681.cpp
extern void __stdcall bfmeGoDEE(struct BfmeThingDEE *);
// 00322950: Code/GameEngine/Source/Common/BfmeConv682.cpp
extern void __stdcall bfmeGoDEF(struct BfmeThingDEF *);
// 00322980: Code/GameEngine/Source/Common/BfmeConv683.cpp
extern void __stdcall bfmeGoDEG(struct BfmeThingDEG *);
// 00322C70: Code/GameEngine/Source/Common/BfmeConv1087.cpp
extern char __stdcall bfmeGo1087B(int,int);
// 003273A0: Code/GameEngine/Source/GameLogic/ScriptEngine/Rva003273A0SpecialPowerAction.cpp
class Rva003273A0SpecialPowerAction { public: bool execute(class Parameter *,class Parameter *,class Parameter *); };
// 0032BB30: Code/GameEngine/Source/Common/BfmeScriptUnitBitTest.cpp
extern bool __stdcall bfmeScriptUnitBitTest(class AsciiString const &,struct BfmeBitRequest const *);
// 003238C0: Code/GameEngine/Source/Common/BfmeConv1093.cpp
extern char __stdcall bfmeGo1093A(int,int);
// 00323710: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsSciencePurchasePoints.cpp
extern char __stdcall bfmeGo1089B(int);
// 00323780: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerHasPower.cpp
extern char __stdcall bfmeGo1090A(int,struct BfmeT1090 *);
// 003256C0: Code/GameEngine/Source/Common/BfmeConv1396.cpp
extern char __stdcall bfmeGoVJZ(struct BfmeSrcVJZ *,struct BfmeYVJZ *);
// 00323D20: Code/GameEngine/Source/Common/BfmeConv922.cpp
extern char __stdcall bfmeGo922D(void *,void *,void *);
// 00322430: Code/GameEngine/Source/Common/BfmeConv1956.cpp
extern char __stdcall bfmeCheckERL(void *);
// 00323980: Code/GameEngine/Source/Common/BfmeConv939.cpp
extern int __cdecl bfmeGo939C(void);
// 00323FB0: Code/GameEngine/Source/Common/BfmeConv1081.cpp
extern char __stdcall bfmeGo1081B(int,int);
// 00324210: Code/GameEngine/Source/GameLogic/ScriptEngine/Rva00324210PlayerCondition.cpp
class Rva00324210PlayerCondition { public: bool evaluate(class Parameter *,class Parameter *,class Parameter *); };
// 00324340: Code/GameEngine/Source/Common/BfmeConv939.cpp
extern int __stdcall bfmeGo939D(char);
// 00324360: Code/GameEngine/Source/Common/BfmeConv922.cpp
extern char __cdecl bfmeGo922A(void);
// 0032C620: Code/GameEngine/Source/Common/BfmeScriptUnitTemplateBitEq.cpp
extern bool __stdcall bfmeScriptUnitTemplateBitEq(class AsciiString const &,struct BfmeBitRequest const *);

// The referenced ZH Parameter header has m_int at +0xC; BFME reads +8 here.
// Witness: RVA 0032F889 and 0032F8A1, MOV EDX,[EAX+8].
struct Rva0032D720ParameterView { unsigned int field00, field04; int field08; };

class Rva012F1600Interface { public:
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
    virtual bool slot29();
};
extern Rva012F1600Interface* Rva012F1600;
class Rva012F079CInterface { public:
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
    virtual bool slot13();
    virtual bool slot14();
};
extern Rva012F079CInterface* Rva012F079C;

class Rva0032D720Virtual {
public:
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
    virtual bool slot10(Parameter*, Parameter*, Parameter*, bool);
};

// Typed call-site views retain ECX, stack cleanup and AL observed in retail.
// Existing dump/thunk symbols carry addresses, not C++ signature claims.
// ILT 0001B45A -> body 00327790; existing Code/gen_asm/d_00322a60.asm.
extern void d_00327790(void);
// ILT 00012855 -> body 00327A00; existing Code/gen_small/thunks_008.cpp.
extern void j_00012855(void);
// ILT 0001CA0D -> body 00328020; existing Code/gen_small/thunks_013.cpp.
extern void j_0001ca0d(void);
// ILT 00005ACE -> body 0032CFC0; existing Code/gen_small/thunks_002.cpp.
extern void j_00005ace(void);
// ILT 0003E73E -> body 0032B730; existing Code/gen_asm/d_0032b730.asm.
extern void d_0032b730(void);
// ILT 00006852 -> body 003287E0; existing Code/gen_asm/d_00322a60.asm.
extern void d_003287e0(void);
// ILT 00042C49 -> body 00328A80; existing Code/gen_asm/d_00322a60.asm.
extern void d_00328a80(void);
// ILT 0001034D -> body 00329A80; existing Code/gen_asm/d_00322a60.asm.
extern void d_00329a80(void);
// ILT 0004318A -> body 00329C20; existing Code/gen_asm/d_00322a60.asm.
extern void d_00329c20(void);
// ILT 00033EBF -> body 0032B190; existing Code/gen_asm/d_00322a60.asm.
extern void d_0032b190(void);
// ILT 0004ACB9 -> body 00328CC0; existing Code/gen_small/thunks_036.cpp.
extern void j_0004acb9(void);
// ILT 0003FAFD -> body 0032A710; existing Code/gen_small/thunks_030.cpp.
extern void j_0003fafd(void);
// ILT 0001BC25 -> body 0032ABC0; existing Code/gen_small/thunks_013.cpp.
extern void j_0001bc25(void);
// ILT 00033BCC -> body 00327260; existing Code/gen_small/thunks_024.cpp.
extern void j_00033bcc(void);
// ILT 00004066 -> body 0032A550; existing Code/gen_small/dumps_000.cpp.
extern void d_0032a550(void);
// ILT 00026265 -> body 0032B8D0; existing Code/gen_small/thunks_018.cpp.
extern void j_00026265(void);
// ILT 00037097 -> body 0032BC80; existing Code/gen_small/thunks_026.cpp.
extern void j_00037097(void);
// ILT 000265AD -> body 00329230; existing Code/gen_small/thunks_018.cpp.
extern void j_000265ad(void);
// ILT 0003CF74 -> body 00323550; existing Code/gen_asm/d_00322a60.asm.
extern void d_00323550(void);
// ILT 0000B31B -> body 003252A0; existing Code/gen_small/thunks_004.cpp.
extern void j_0000b31b(void);
// ILT 00024CDA -> body 003254B0; existing Code/gen_small/thunks_017.cpp.
extern void j_00024cda(void);
// ILT 0000C586 -> body 0032C090; existing Code/gen_asm/d_0032b730.asm.
extern void d_0032c090(void);
// ILT 0000867A -> body 00325700; existing Code/gen_small/thunks_003.cpp.
extern void j_0000867a(void);
// ILT 00023F29 -> body 00329400; existing Code/gen_asm/d_00322a60.asm.
extern void d_00329400(void);
// ILT 000230FB -> body 00325BC0; existing Code/gen_small/thunks_016.cpp.
extern void j_000230fb(void);
// ILT 00035986 -> body 003239A0; existing Code/gen_small/thunks_025.cpp.
extern void j_00035986(void);
// ILT 0001BE37 -> body 00325970; existing Code/gen_small/thunks_013.cpp.
extern void j_0001be37(void);
// ILT 0004A660 -> body 003261D0; existing Code/gen_asm/d_00322a60.asm.
extern void d_003261d0(void);
// ILT 0002772D -> body 00326490; existing Code/gen_asm/d_00322a60.asm.
extern void d_00326490(void);
// ILT 00047AB4 -> body 003248E0; existing Code/gen_small/thunks_034.cpp.
extern void j_00047ab4(void);
// ILT 000287BD -> body 00326F40; existing Code/gen_small/thunks_019.cpp.
extern void j_000287bd(void);
// ILT 00047C1C -> body 00329E00; existing Code/gen_asm/d_00322a60.asm.
extern void d_00329e00(void);
// ILT 000228C2 -> body 00329FB0; existing Code/gen_asm/d_00322a60.asm.
extern void d_00329fb0(void);
// ILT 0004463E -> body 0032CDB0; existing Code/gen_small/thunks_032.cpp.
extern void j_0004463e(void);
// ILT 00006537 -> body 0032C680; existing Code/gen_asm/d_0032b730.asm.
extern void d_0032c680(void);
// ILT 0002B661 -> body 0032C7F0; existing Code/gen_asm/d_0032b730.asm.
extern void d_0032c7f0(void);
// ILT 0002769C -> body 0032C990; existing Code/gen_asm/d_0032b730.asm.
extern void d_0032c990(void);
// ILT 0002A2DE -> body 003269C0; existing Code/gen_small/thunks_020.cpp.
extern void j_0002a2de(void);

class Rva0032D720 : public ScriptConditions {
public:
    bool evaluate(Condition* c);
private:
    __forceinline bool rva00322100(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { char (__stdcall *raw)(int); Function member; } fn;
        fn.raw = bfmeGo1091C;
        return (this->*fn.member)(a0);
    }
    __forceinline bool rva003221B0(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { char (__stdcall *raw)(int); Function member; } fn;
        fn.raw = bfmeGo1091B;
        return (this->*fn.member)(a0);
    }

    __forceinline bool rva00327790(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00327790;
        return (this->*fn.member)(a0, a1);
    }
    __forceinline bool rva00327940(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(int,int); Function member; } fn;
        fn.raw = bfmeGo1094A;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00327A00(Condition* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_00012855;
        return (this->*fn.member)(a0, a1, a2);
    }

    __forceinline bool rva003283C0(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(int,int); Function member; } fn;
        fn.raw = bfmeGo1092B;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00322630(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(int,int); Function member; } fn;
        fn.raw = bfmeGo1092A;
        return (this->*fn.member)(a0, a1);
    }
    __forceinline bool rva00328020(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0001ca0d;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva0032CFC0(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_00005ace;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva003226E0(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        return (this->*reinterpret_cast<Function>(
            &Rva0032D720::evaluateNamedContainEmpty))(a0);
    }

    __forceinline bool rva00322810(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(struct BfmeT1089 *,int); Function member; } fn;
        fn.raw = bfmeGo1089C;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00322880(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { char (__stdcall *raw)(int); Function member; } fn;
        fn.raw = bfmeGo1090B;
        return (this->*fn.member)(a0);
    }

    __forceinline bool rva0032B730(Condition* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_0032b730;
        return (this->*fn.member)(a0, a1);
    }




    __forceinline bool rva003287E0(Parameter* a0, Parameter* a1, Parameter* a2, int a3, int a4)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*, int, int);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_003287e0;
        return (this->*fn.member)(a0, a1, a2, a3, a4);
    }
    __forceinline bool rva00328A80(Parameter* a0, Parameter* a1, Parameter* a2, int a3)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*, int);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00328a80;
        return (this->*fn.member)(a0, a1, a2, a3);
    }
    __forceinline bool rva00329A80(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00329a80;
        return (this->*fn.member)(a0, a1);
    }
    __forceinline bool rva00329C20(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00329c20;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva003228F0(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { void (__stdcall *raw)(struct BfmeThingDEE *); Function member; } fn;
        fn.raw = bfmeGoDEE;
        return (this->*fn.member)(a0);
    }

    __forceinline bool rva00322950(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { void (__stdcall *raw)(struct BfmeThingDEF *); Function member; } fn;
        fn.raw = bfmeGoDEF;
        return (this->*fn.member)(a0);
    }
    __forceinline bool rva00322980(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { void (__stdcall *raw)(struct BfmeThingDEG *); Function member; } fn;
        fn.raw = bfmeGoDEG;
        return (this->*fn.member)(a0);
    }
    __forceinline bool rva0032B190(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_0032b190;
        return (this->*fn.member)(a0, a1, a2);
    }

    __forceinline bool rva00322C70(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(int,int); Function member; } fn;
        fn.raw = bfmeGo1087B;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00328CC0(Condition* a0, Parameter* a1, Parameter* a2, Parameter* a3, Parameter* a4)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0004acb9;
        return (this->*fn.member)(a0, a1, a2, a3, a4);
    }

    __forceinline bool rva0032A710(Condition* a0, Parameter* a1, Parameter* a2, Parameter* a3, Parameter* a4, Parameter* a5, Parameter* a6)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*, Parameter*, Parameter*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0003fafd;
        return (this->*fn.member)(a0, a1, a2, a3, a4, a5, a6);
    }
    __forceinline bool rva0032ABC0(Condition* a0, Parameter* a1, Parameter* a2, Parameter* a3, Parameter* a4, Parameter* a5)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*, Parameter*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0001bc25;
        return (this->*fn.member)(a0, a1, a2, a3, a4, a5);
    }
    __forceinline bool rva00327260(Parameter* a0, Parameter* a1, Parameter* a2, Parameter* a3)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_00033bcc;
        return (this->*fn.member)(a0, a1, a2, a3);
    }
    __forceinline bool rva0032A550(Parameter* a0, Parameter* a1, Parameter* a2, Parameter* a3, Parameter* a4)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_0032a550;
        return (this->*fn.member)(a0, a1, a2, a3, a4);
    }

    __forceinline bool rva0032B8D0(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_00026265;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva0032BB30(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { bool (__stdcall *raw)(class AsciiString const &,struct BfmeBitRequest const *); Function member; } fn;
        fn.raw = bfmeScriptUnitBitTest;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva0032BC80(Condition* a0, Parameter* a1, Parameter* a2, Parameter* a3, Parameter* a4)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_00037097;
        return (this->*fn.member)(a0, a1, a2, a3, a4);
    }

    __forceinline bool rva00329230(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_000265ad;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva00323550(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00323550;
        return (this->*fn.member)(a0, a1);
    }
    __forceinline bool rva003252A0(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0000b31b;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva003254B0(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_00024cda;
        return (this->*fn.member)(a0, a1, a2);
    }

    __forceinline bool rva0032C090(Condition* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_0032c090;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva003238C0(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(int,int); Function member; } fn;
        fn.raw = bfmeGo1093A;
        return (this->*fn.member)(a0, a1);
    }
    __forceinline bool rva0032C400(Condition* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*, Parameter*);
        return (this->*reinterpret_cast<Function>(
            &Rva0032D720::bfmeAreaGate))(a0, a1, a2);
    }
    __forceinline bool rva00325700(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0000867a;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00323710(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { char (__stdcall *raw)(int); Function member; } fn;
        fn.raw = bfmeGo1089B;
        return (this->*fn.member)(a0);
    }
    __forceinline bool rva00323780(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(int,struct BfmeT1090 *); Function member; } fn;
        fn.raw = bfmeGo1090A;
        return (this->*fn.member)(a0, a1);
    }
    __forceinline bool rva003256C0(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(struct BfmeSrcVJZ *,struct BfmeYVJZ *); Function member; } fn;
        fn.raw = bfmeGoVJZ;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00329400(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00329400;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00325BC0(Condition* a0)
    {
        typedef bool (Rva0032D720::*Function)(Condition*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_000230fb;
        return (this->*fn.member)(a0);
    }

    __forceinline bool rva003239A0(Condition* a0)
    {
        typedef bool (Rva0032D720::*Function)(Condition*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_00035986;
        return (this->*fn.member)(a0);
    }
    __forceinline bool rva00325970(Condition* a0)
    {
        typedef bool (Rva0032D720::*Function)(Condition*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0001be37;
        return (this->*fn.member)(a0);
    }

    __forceinline bool rva00323D20(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { char (__stdcall *raw)(void *,void *,void *); Function member; } fn;
        fn.raw = bfmeGo922D;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva003261D0(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_003261d0;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00326490(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00326490;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva003248E0(Condition* a0, Parameter* a1, Parameter* a2, Parameter* a3)
    {
        typedef bool (Rva0032D720::*Function)(Condition*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_00047ab4;
        return (this->*fn.member)(a0, a1, a2, a3);
    }
    __forceinline bool rva00322430(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { char (__stdcall *raw)(void *); Function member; } fn;
        fn.raw = bfmeCheckERL;
        return (this->*fn.member)(a0);
    }
    __forceinline bool rva00323980()
    {
        typedef bool (Rva0032D720::*Function)();
        union { int (__cdecl *raw)(void); Function member; } fn;
        fn.raw = bfmeGo939C;
        return (this->*fn.member)();
    }

    __forceinline bool rva00323FB0(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { char (__stdcall *raw)(int,int); Function member; } fn;
        fn.raw = bfmeGo1081B;
        return (this->*fn.member)(a0, a1);
    }

    __forceinline bool rva00326F40(Parameter* a0, Parameter* a1, Parameter* a2, Parameter* a3)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_000287bd;
        return (this->*fn.member)(a0, a1, a2, a3);
    }

    __forceinline bool rva00329E00(Parameter* a0)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00329e00;
        return (this->*fn.member)(a0);
    }
    __forceinline bool rva00329FB0(Parameter* a0, int a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, int);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_00329fb0;
        return (this->*fn.member)(a0, a1);
    }
    __forceinline bool rva00324360()
    {
        typedef bool (Rva0032D720::*Function)();
        union { char (__cdecl *raw)(void); Function member; } fn;
        fn.raw = bfmeGo922A;
        return (this->*fn.member)();
    }

    __forceinline bool rva0032CDB0(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0004463e;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva0032C620(Parameter* a0, Parameter* a1)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*);
        union { bool (__stdcall *raw)(class AsciiString const &,struct BfmeBitRequest const *); Function member; } fn;
        fn.raw = bfmeScriptUnitTemplateBitEq;
        return (this->*fn.member)(a0, a1);
    }
    __forceinline bool rva0032C680(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_0032c680;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva0032C7F0(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_0032c7f0;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva0032C990(Parameter* a0, Parameter* a1, Parameter* a2)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = d_0032c990;
        return (this->*fn.member)(a0, a1, a2);
    }
    __forceinline bool rva003269C0(Parameter* a0, Parameter* a1, Parameter* a2, Parameter* a3)
    {
        typedef bool (Rva0032D720::*Function)(Parameter*, Parameter*, Parameter*, Parameter*);
        union { void (*raw)(void); Function member; } fn;
        fn.raw = j_0002a2de;
        return (this->*fn.member)(a0, a1, a2, a3);
    }

};

bool Rva0032D720::evaluate(Condition* c)
{
    switch (c->getConditionType()) {
    case 5:
        return rva00322100(c->getParameter(0));
    case 6:
        return rva003221B0(c->getParameter(0));
    case 7:
        return evaluateTeamInsideAreaPartially(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 13:
        return evaluateNamedInsideArea(c->getParameter(0), c->getParameter(1));
    case 8:
        return evaluateIsDestroyed(c->getParameter(0));
    case 170:
        return evaluateTeamCountCompare(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 172:
        return evaluateNamedUnitRankLevel(c->getParameter(0), c->getParameter(1));
    case 15:
        return evaluateNamedUnitDestroyed(c->getParameter(0));
    case 56:
        return evaluateNamedUnitDying(c->getParameter(0));
    case 57:
        return evaluateNamedUnitTotallyDead(c->getParameter(0));
    case 16:
        return evaluateNamedUnitExists(c->getParameter(0));
    case 10:
        return evaluateHasUnits(c->getParameter(0));
    case 9:
        return Rva012F1600->slot29();
    case 11:
        return evaluateTeamStateIs(c->getParameter(0), c->getParameter(1));
    case 12:
        return evaluateTeamStateIsNot(c->getParameter(0), c->getParameter(1));
    case 14:
        return evaluateNamedOutsideArea(c->getParameter(0), c->getParameter(1));
    case 17:
        return evaluateTeamInsideAreaEntirely(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 18:
        return evaluateTeamOutsideAreaEntirely(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 19:
        return evaluateNamedAttackedByType(c->getParameter(0), c->getParameter(1));
    case 20:
        return rva00327790(c->getParameter(0), c->getParameter(1));
    case 21:
        return rva00327940(c->getParameter(0), c->getParameter(1));
    case 22:
        return evaluateTeamAttackedByPlayer(c->getParameter(0), c->getParameter(1));
    case 23:
        return rva00327A00(c, c->getParameter(0), c->getParameter(1));
    case 24:
        return evaluateNamedCreated(c->getParameter(0));
    case 25:
        return evaluateTeamCreated(c->getParameter(0));
    case 26:
        return evaluatePlayerHasCredits(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 54:
        return evaluateBridgeRepaired(c->getParameter(0));
    case 55:
        return evaluateBridgeBroken(c->getParameter(0));
    case 27:
        return rva003283C0(c->getParameter(0), c->getParameter(1));
    case 28:
        return evaluateRva00328470(c->getParameter(0), c->getParameter(1));
    case 51:
        return rva00322630(c->getParameter(0), c->getParameter(1));
    case 52:
        if (c->getNumParameters() < 3) return false;
        return evaluateEnemySighted(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 133:
        return rva00328020(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 77:
        return rva0032CFC0(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 78:
        return rva003226E0(c->getParameter(0));
    case 30:
        return evaluateNamedOwnedByPlayer(c->getParameter(0), c->getParameter(1));
    case 31:
        return evaluateTeamOwnedByPlayer(c->getParameter(0), c->getParameter(1));
    case 32:
        return rva00322810(c->getParameter(1), c->getParameter(0));
    case 79:
        return evaluatePlayerHasNOrFewerFactionBuildings(c->getParameter(1), c->getParameter(0));
    case 131:
        return evaluatePlayerHasNOrFewerBases(c->getParameter(1), c->getParameter(0));
    case 33:
        return rva00322880(c->getParameter(0));
    case 47:
        return !rva00322880(c->getParameter(0));
    case 34:
        return evaluateNamedReachedWaypointsEnd(c->getParameter(0), c->getParameter(1));
    case 35:
        return evaluateTeamReachedWaypointsEnd(c->getParameter(0), c->getParameter(1));
    case 37:
        return rva0032B730(c, c->getParameter(0));
    case 38:
        return evaluateNamedEnteredArea(c->getParameter(0), c->getParameter(1));
    case 39:
        return evaluateNamedExitedArea(c->getParameter(0), c->getParameter(1));
    case 40:
        return evaluateTeamEnteredAreaEntirely(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 121:
        return evaluateNamedBaseUnpackableForPlayer(c->getParameter(0), c->getParameter(1));
    case 41:
        return evaluateTeamEnteredAreaPartially(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 42:
        return evaluateTeamExitedAreaEntirely(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 43:
        return evaluateTeamExitedAreaPartially(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 147:
        return evaluateRva003240F0(c->getParameter(0), c->getParameter(1));
    case 148:
        return rva003287E0(c->getParameter(0), c->getParameter(1), 0, 1, 0);
    case 149:
        return rva003287E0(c->getParameter(0), c->getParameter(1), 0, 1, 1);
    case 150:
        return rva003287E0(c->getParameter(0), c->getParameter(1), 0, 0, 0);
    case 151:
        return rva003287E0(c->getParameter(0), c->getParameter(1), 0, 0, 1);
    case 152:
        return rva003287E0(c->getParameter(0), 0, c->getParameter(1), 1, 0);
    case 153:
        return rva003287E0(c->getParameter(0), 0, c->getParameter(1), 1, 1);
    case 154:
        return rva003287E0(c->getParameter(0), 0, c->getParameter(1), 0, 0);
    case 155:
        return rva003287E0(c->getParameter(0), 0, c->getParameter(1), 0, 1);
    case 156:
        return rva00328A80(c->getParameter(0), c->getParameter(1), 0, 1);
    case 157:
        return rva00328A80(c->getParameter(0), c->getParameter(1), 0, 0);
    case 158:
        return rva00328A80(c->getParameter(0), 0, c->getParameter(1), 1);
    case 159:
        return rva00328A80(c->getParameter(0), 0, c->getParameter(1), 0);
    case 138:
        return rva00329A80(c->getParameter(0), c->getParameter(1));
    case 141:
        return rva00329C20(c->getParameter(0), c->getParameter(1));
    case 44:
        return Rva012F079C->slot13();
    case 45:
        return Rva012F079C->slot14();
    case 46:
        return evaluateMultiplayerPlayerDefeat();
    case 36:
        return rva003228F0(c->getParameter(0));
    case 48:
        return evaluateAudioHasCompleted(c->getParameter(0));
    case 49:
        return rva00322950(c->getParameter(0));
    case 50:
        return rva00322980(c->getParameter(0));
    case 53:
        return rva0032B190(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 61:
        return evaluatePlayerSpecialPowerFromUnitTriggered(c->getParameter(0), c->getParameter(1), 0);
    case 64:
        return evaluatePlayerSpecialPowerFromUnitTriggered(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 63:
        return evaluatePlayerSpecialPowerFromUnitMidway(c->getParameter(0), c->getParameter(1), 0);
    case 66:
        return evaluatePlayerSpecialPowerFromUnitMidway(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 62:
        return evaluatePlayerSpecialPowerFromUnitComplete(c->getParameter(0), c->getParameter(1), 0);
    case 65:
        return evaluatePlayerSpecialPowerFromUnitComplete(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 100:
        return rva00322C70(c->getParameter(0), c->getParameter(1));
    case 102:
        return evaluateScienceAcquired(c->getParameter(0), c->getParameter(1));
    case 101:
        return evaluateSciencePurchasePoints(c->getParameter(0), c->getParameter(1));
    case 173:
        return evaluatePlayerHasPower(c->getParameter(0));
    case 69:
        return evaluateUpgradeFromUnitComplete(c->getParameter(0), c->getParameter(1), 0);
    case 70:
        return evaluateUpgradeFromUnitComplete(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 58:
        return rva00328CC0(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
    case 71:
        return evaluatePlayerDestroyedNOrMoreBuildings(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 74:
        if (c->getNumParameters() < 5) return false;
        return rva0032A710(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), c->getParameter(4), 0);
    case 110:
        if (c->getNumParameters() < 6) return false;
        return rva0032A710(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), c->getParameter(4), c->getParameter(5));
    case 75:
        if (c->getNumParameters() < 5) return false;
        return rva0032ABC0(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), c->getParameter(4));
    case 160:
        return rva00327260(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
    case 161:
        return rva0032A550(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3), c->getParameter(4));
    case 76:
        return evaluateUnitHasEmptied(c->getParameter(0));
    case 83:
        return evaluatePlayerHasComparisonPercentPower(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 84:
        return evaluateRva003231E0(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 85:
        return rva0032B8D0(c->getParameter(0), c->getParameter(1));
    case 171:
        return reinterpret_cast<Rva003273A0SpecialPowerAction*>(this)->execute(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 80:
        return rva0032BB30(c->getParameter(0), c->getParameter(1));
    case 81:
        return evaluateTeamHasObjectStatus(c->getParameter(0), c->getParameter(1), 1);
    case 82:
        return evaluateTeamHasObjectStatus(c->getParameter(0), c->getParameter(1), 0);
    case 86:
        return rva0032BC80(c, c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
    case 87:
        return evaluateSkirmishPlayerIsFaction(c->getParameter(0), c->getParameter(1));
    case 88:
        return evaluateSkirmishSuppliesWithinDistancePerimeter(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
    case 89:
        return reinterpret_cast<Rva0032D720Virtual*>(this)->slot10(c->getParameter(0), c->getParameter(1), c->getParameter(2), 1);
    case 90:
        return reinterpret_cast<Rva0032D720Virtual*>(this)->slot10(c->getParameter(0), c->getParameter(1), c->getParameter(2), 0);
    case 91:
        return rva00329230(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 92:
        return rva00323550(c->getParameter(0), c->getParameter(1));
    case 93:
        return rva003252A0(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 94:
        return rva003254B0(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 95:
        return evaluateSkirmishNamedAreaExists(c->getParameter(0), c->getParameter(1));
    case 96:
        return rva0032C090(c, c->getParameter(0), c->getParameter(1));
    case 97:
        return rva003238C0(c->getParameter(0), c->getParameter(1));
    case 98:
        return rva0032C400(c, c->getParameter(0), c->getParameter(1));
    case 99:
        return rva00325700(c->getParameter(0), c->getParameter(1));
    case 103:
        return evaluateMusicHasCompleted(c->getParameter(0), c->getParameter(1));
    case 105:
        return evaluateRva00323650(c, c->getParameter(0), c->getParameter(1));
    case 106:
        return rva00323710(c->getParameter(0));
    case 107:
        return rva00323780(c->getParameter(0), c->getParameter(1));
    case 108:
        return rva003256C0(c->getParameter(0), c->getParameter(1));
    case 109:
        return evaluateIsSiegeAttachedToWall(c->getParameter(0));
    case 104:
        return rva00329400(c->getParameter(0), c->getParameter(1));
    case 120:
        return evaluateCameraHitSpecificSplineWaypoint(c->getParameter(0));
    case 132:
        return evaluateCameraEnteredArea(c->getParameter(0));
    case 111:
        return rva00325BC0(c);
    case 112:
        return evaluateCounterSeconds(c);
    case 113:
        return rva003239A0(c);
    case 114:
        return rva00325970(c);
    case 115:
        return evaluateDistanceBetweenObjects(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
    case 116:
        return evaluateTeamCachedFloatCompare(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
    case 117:
        return evaluateNamedHasFreeContainerSlots(c->getParameter(0));
    case 118:
        return evaluateRva00325FC0(c->getParameter(0), c->getParameter(1));
    case 119:
        return rva00323D20(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 123:
        return rva003261D0(c->getParameter(0), c->getParameter(1));
    case 124:
        return evaluatePlayerCompareLightPoints(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 125:
        return evaluateHasCommandPointsToBuildTeam(c->getParameter(0), c->getParameter(1));
    case 126:
        return rva00326490(c->getParameter(0), c->getParameter(1));
    case 127:
        return evaluateCanBuildAtBase(c->getParameter(0), c->getParameter(1));
    case 169:
        return evaluateCanBuildObjectTypeAtBase(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 128:
        return evaluatePlayerHasKilledKindOfUnits(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 129:
        return evaluatePlayerHasKilledTypeUnits(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 130:
        return evaluateNamedDestroyedByType(c->getParameter(0), c->getParameter(1));
    case 134:
        return rva003248E0(c, c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 135:
        return rva00322430(c->getParameter(0));
    case 142:
        return rva00323980();
    case 136:
        return evaluateNamedCanPathToWaypoint(c->getParameter(0), c->getParameter(1));
    case 137:
        return rva00323FB0(c->getParameter(0), c->getParameter(1));
    case 139:
        return evaluateTeamCanPathToWaypoint(c->getParameter(0), c->getParameter(1));
    case 140:
        return evaluateTeamCanPathToNamed(c->getParameter(0), c->getParameter(1));
    case 143:
        return evaluateTeamHasNamed(c->getParameter(0), c->getParameter(1));
    case 144:
        return evaluateUnitHealth(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 145:
        return reinterpret_cast<Rva00324210PlayerCondition*>(this)->evaluate(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 146:
        return rva00326F40(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
    case 162:
        return evaluateIsBuildingEmpty(c->getParameter(0));
    case 163:
        return rva00329E00(c->getParameter(0));
    case 164:
        return rva00329FB0(c->getParameter(0), 1);
    case 165:
        return rva00329FB0(c->getParameter(0), 0);
    case 166: {
        typedef bool (Rva0032D720::*Function)(bool);
        union { int (__stdcall *raw)(char); Function member; } fn;
        fn.raw = bfmeGo939D;
        return (this->*fn.member)(reinterpret_cast<Rva0032D720ParameterView*>(c->getParameter(0))->field08 != 0);
    }
    case 167:
        return rva00324360();
    case 168:
        return evaluateCompareNumPlayersInGame(c->getParameter(0), c->getParameter(1));
    case 174:
        return rva0032CDB0(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 175:
        return rva0032C620(c->getParameter(0), c->getParameter(1));
    case 176:
        return rva0032C680(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 177:
        return rva0032C7F0(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 178:
        return rva0032C990(c->getParameter(0), c->getParameter(1), c->getParameter(2));
    case 179:
        return rva003269C0(c->getParameter(0), c->getParameter(1), c->getParameter(2), c->getParameter(3));
    case 180:
        return evaluateUnitHasToggledWeapon(c->getParameter(0), c->getParameter(1));
    case 182:
        return rva00326da0(c->getParameter(0), c->getParameter(1));
    case 181:
        return evaluateAnyUnitsUsingBloodthirsty(c->getParameter(0));
    case 183:
        return rva00326c00(c->getParameter(0), c->getParameter(1));
    default:
        return false;
    }
}
