// TeamTemplateInfo::TeamTemplateInfo at RVA 0x000EFEB0 (2992 bytes).
// Identity: native TeamPrototype constructor 0x000F3E40 calls this body.
// BFME adds teamEventsList at +0x70 and has 32 generic script hooks.
// See targets/game/reverse/identity_evidence/000EFEB0-team-template-constructor.md.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "ascii_string.h"
#include "basetype.h"
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline void StringBase<char>::clear() { releaseBuffer(); }
enum NameKeyType { NAMEKEY_INVALID=0 };
enum AttitudeType { AI_NORMAL=0 };
enum VeterancyLevel { LEVEL_REGULAR=0 };
class StaticNameKey {
public: NameKeyType key() const; operator NameKeyType() const { return key(); }
};
class NameKeyGenerator {
public: AsciiString keyToName(NameKeyType); NameKeyType nameToKey(const char*);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Dict {
public:
 int getInt(NameKeyType,bool *exists=0) const;
 float getReal(NameKeyType,bool *exists=0) const;
 bool getBool(NameKeyType,bool *exists=0) const;
 AsciiString getAsciiString(NameKeyType,bool *exists=0) const;
};
class Waypoint {
public:
 AsciiString getName() const;
 const Coord3D *getLocation() const { return &m_location; }
 Waypoint *getNext() const { return m_pNext; }
 unsigned char m_00[0xc]; Coord3D m_location; int m_18; Waypoint *m_pNext;
};
class TerrainLogic {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(00) SLOT(04) SLOT(08) SLOT(0c) SLOT(10) SLOT(14) SLOT(18) SLOT(1c)
 SLOT(20) SLOT(24) SLOT(28) SLOT(2c) SLOT(30) SLOT(34) SLOT(38) SLOT(3c)
 SLOT(40) SLOT(44) SLOT(48) SLOT(4c) SLOT(50) SLOT(54) SLOT(58) SLOT(5c)
 SLOT(60) SLOT(64) SLOT(68) SLOT(6c) SLOT(70) SLOT(74)
#undef SLOT
 virtual Waypoint *getFirstWaypoint();
};
extern TerrainLogic *TheTerrainLogic;
class Xfer;
// Four independently decoded BFME Snapshot slots: deleting dtor / load / name / xfer.
// Canonical snapshot.h orders its name/load slots oppositely; keep this ABI view local.
class Rva000EFEB0Snapshot {
public:
 Rva000EFEB0Snapshot() {} virtual ~Rva000EFEB0Snapshot() {}
 virtual void loadPostProcess()=0;
 virtual const char *snapshotNameAt000F0D60() const=0;
 virtual void xfer(Xfer*)=0;
};
struct TCreateUnitsInfo {
 int minUnits,maxUnits; AsciiString unitThingName;
};
enum {MAX_GENERIC_SCRIPTS=32};
class TeamTemplateInfo : public Rva000EFEB0Snapshot {
public:
 TeamTemplateInfo(Dict*);
 TCreateUnitsInfo m_unitsInfo[7];
 int m_numUnitsInfo;
 Coord3D m_homeLocation;
 bool m_hasHomeLocation;
 AsciiString m_scriptOnCreate,m_teamEventsList,m_scriptOnIdle;
 int m_initialIdleFrames;
 AsciiString m_scriptOnEnemySighted,m_scriptOnAllClear,m_scriptOnUnitDestroyed,m_scriptOnDestroyed;
 float m_destroyedThreshold;
 bool m_isAIRecruitable,m_isBaseDefense,m_isPerimeterDefense,m_automaticallyReinforce;
 bool m_transportsReturn,m_avoidThreats,m_attackCommonTarget;
 int m_maxInstances,m_productionPriority,m_productionPrioritySuccessIncrease,m_productionPriorityFailureDecrease;
 AttitudeType m_initialTeamAttitude;
 AsciiString m_transportUnitType,m_startReinforceWaypoint;
 bool m_teamStartsFull,m_transportsExit;
 VeterancyLevel m_veterancy;
 AsciiString m_productionCondition;
 bool m_executeActions;
 AsciiString m_teamGenericScripts[MAX_GENERIC_SCRIPTS];
 virtual const char *snapshotNameAt000F0D60()const;
 virtual void xfer(Xfer*);
 virtual void loadPostProcess();
};

typedef char TeamTemplateInfoSize[sizeof(TeamTemplateInfo)==0x144 ? 1 : -1];
extern const StaticNameKey TheKey_teamAggressiveness;
extern const StaticNameKey TheKey_teamAllClearScript;
extern const StaticNameKey TheKey_teamAttackCommonTarget;
extern const StaticNameKey TheKey_teamAutoReinforce;
extern const StaticNameKey TheKey_teamAvoidThreats;
extern const StaticNameKey TheKey_teamDestroyedThreshold;
extern const StaticNameKey TheKey_teamEnemySightedScript;
extern const StaticNameKey TheKey_teamEventsList;
extern const StaticNameKey TheKey_teamExecutesActionsOnCreate;
extern const StaticNameKey TheKey_teamGenericScriptHook;
extern const StaticNameKey TheKey_teamHome;
extern const StaticNameKey TheKey_teamInitialIdleSeconds;
extern const StaticNameKey TheKey_teamIsAIRecruitable;
extern const StaticNameKey TheKey_teamIsBaseDefense;
extern const StaticNameKey TheKey_teamIsPerimeterDefense;
extern const StaticNameKey TheKey_teamMaxInstances;
extern const StaticNameKey TheKey_teamOnCreateScript;
extern const StaticNameKey TheKey_teamOnDestroyedScript;
extern const StaticNameKey TheKey_teamOnIdleScript;
extern const StaticNameKey TheKey_teamOnUnitDestroyedScript;
extern const StaticNameKey TheKey_teamProductionCondition;
extern const StaticNameKey TheKey_teamProductionPriority;
extern const StaticNameKey TheKey_teamProductionPriorityFailureDecrease;
extern const StaticNameKey TheKey_teamProductionPrioritySuccessIncrease;
extern const StaticNameKey TheKey_teamReinforcementOrigin;
extern const StaticNameKey TheKey_teamStartsFull;
extern const StaticNameKey TheKey_teamTransport;
extern const StaticNameKey TheKey_teamTransportsExit;
extern const StaticNameKey TheKey_teamTransportsReturn;
extern const StaticNameKey TheKey_teamUnitMaxCount1;
extern const StaticNameKey TheKey_teamUnitMaxCount2;
extern const StaticNameKey TheKey_teamUnitMaxCount3;
extern const StaticNameKey TheKey_teamUnitMaxCount4;
extern const StaticNameKey TheKey_teamUnitMaxCount5;
extern const StaticNameKey TheKey_teamUnitMaxCount6;
extern const StaticNameKey TheKey_teamUnitMaxCount7;
extern const StaticNameKey TheKey_teamUnitMinCount1;
extern const StaticNameKey TheKey_teamUnitMinCount2;
extern const StaticNameKey TheKey_teamUnitMinCount3;
extern const StaticNameKey TheKey_teamUnitMinCount4;
extern const StaticNameKey TheKey_teamUnitMinCount5;
extern const StaticNameKey TheKey_teamUnitMinCount6;
extern const StaticNameKey TheKey_teamUnitMinCount7;
extern const StaticNameKey TheKey_teamUnitType1;
extern const StaticNameKey TheKey_teamUnitType2;
extern const StaticNameKey TheKey_teamUnitType3;
extern const StaticNameKey TheKey_teamUnitType4;
extern const StaticNameKey TheKey_teamUnitType5;
extern const StaticNameKey TheKey_teamUnitType6;
extern const StaticNameKey TheKey_teamUnitType7;
extern const StaticNameKey TheKey_teamVeterancy;
TeamTemplateInfo::TeamTemplateInfo(Dict *d) :
	m_numUnitsInfo(0)
{
	Bool exists;
	Int min, max;
	AsciiString templateName;
	min = d->getInt(TheKey_teamUnitMinCount1, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount1, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType1, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount2, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount2, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType2, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount3, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount3, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType3, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount4, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount4, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType4, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount5, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount5, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType5, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount6, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount6, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType6, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	min = d->getInt(TheKey_teamUnitMinCount7, &exists);
	max = d->getInt(TheKey_teamUnitMaxCount7, &exists);
	templateName = d->getAsciiString(TheKey_teamUnitType7, &exists);
	if (max>0 && exists) {
		m_unitsInfo[m_numUnitsInfo].minUnits = min;
		m_unitsInfo[m_numUnitsInfo].maxUnits = max;
		m_unitsInfo[m_numUnitsInfo].unitThingName = templateName;
		m_numUnitsInfo++;
	}

	AsciiString waypoint = d->getAsciiString(TheKey_teamHome, &exists);
	m_homeLocation.x = m_homeLocation.y = 0;
	m_homeLocation.z = 0;
	m_hasHomeLocation = false;
	if (exists) {
		for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
			if (way->getName().compare(waypoint) == 0) {
				m_homeLocation = *way->getLocation();
				m_hasHomeLocation = true;
			}
		}
	}

	m_scriptOnCreate = d->getAsciiString(TheKey_teamOnCreateScript, &exists);
	m_teamEventsList = d->getAsciiString(TheKey_teamEventsList, &exists);
	m_isAIRecruitable	= d->getBool(TheKey_teamIsAIRecruitable, &exists);
	if (!exists) {
		m_isAIRecruitable = false;
	}
	m_isBaseDefense	= d->getBool(TheKey_teamIsBaseDefense, &exists);
	m_isPerimeterDefense	= d->getBool(TheKey_teamIsPerimeterDefense, &exists);
	m_automaticallyReinforce = d->getBool(TheKey_teamAutoReinforce, &exists);

	Int interact	= d->getInt(TheKey_teamAggressiveness, &exists);
	m_initialTeamAttitude = AI_NORMAL;
	if (exists) {
		m_initialTeamAttitude = (AttitudeType) interact;
	}

	m_transportsReturn	= d->getBool(TheKey_teamTransportsReturn, &exists);
	m_avoidThreats = d->getBool(TheKey_teamAvoidThreats, &exists);

	m_attackCommonTarget = d->getBool(TheKey_teamAttackCommonTarget, &exists);

	m_maxInstances = d->getInt(TheKey_teamMaxInstances, &exists);

	m_scriptOnIdle = d->getAsciiString(TheKey_teamOnIdleScript, &exists);
	m_initialIdleFrames = 5 * d->getInt(TheKey_teamInitialIdleSeconds, &exists);
	m_scriptOnEnemySighted = d->getAsciiString(TheKey_teamEnemySightedScript, &exists);
	m_scriptOnAllClear = d->getAsciiString(TheKey_teamAllClearScript, &exists);
	m_scriptOnDestroyed = d->getAsciiString(TheKey_teamOnDestroyedScript, &exists);
	m_destroyedThreshold = d->getReal(TheKey_teamDestroyedThreshold, &exists);
	m_scriptOnUnitDestroyed = d->getAsciiString(TheKey_teamOnUnitDestroyedScript, &exists);

	m_productionPriority = d->getInt(TheKey_teamProductionPriority, &exists);
	m_productionPrioritySuccessIncrease = d->getInt(TheKey_teamProductionPrioritySuccessIncrease, &exists);
	m_productionPriorityFailureDecrease = d->getInt(TheKey_teamProductionPriorityFailureDecrease, &exists);

	// Production scripts stuff
	m_productionCondition = d->getAsciiString(TheKey_teamProductionCondition, &exists);
	m_executeActions = d->getBool(TheKey_teamExecutesActionsOnCreate, &exists);

	
	// Which scripts to attempt during run?
	for (int i = 0; i < MAX_GENERIC_SCRIPTS; ++i) {
		AsciiString keyName;
		keyName.format("%s%d", TheNameKeyGenerator->keyToName(TheKey_teamGenericScriptHook).str(), i);			
		m_teamGenericScripts[i] = d->getAsciiString(TheNameKeyGenerator->nameToKey(keyName.str()), &exists);
		if (!exists) {
			m_teamGenericScripts[i].clear();
		}
	}


	// reinforcement team info.
	m_transportUnitType = d->getAsciiString(TheKey_teamTransport, &exists);
	m_transportsExit = d->getBool(TheKey_teamTransportsExit, &exists);
	m_teamStartsFull = d->getBool(TheKey_teamStartsFull, &exists);
	m_startReinforceWaypoint = d->getAsciiString(TheKey_teamReinforcementOrigin, &exists);
	m_veterancy = (VeterancyLevel)d->getInt(TheKey_teamVeterancy, &exists);
}

