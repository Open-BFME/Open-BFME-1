// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SlavedUpdate::friend_newModuleData
//
// The members are named from retail's own INI field table, which gives each
// SlavedUpdate key a binary-proven offset; upstream's parse table says which
// member that key writes. Every offset here is derived from the declaration
// sequence, not from the old m_NN names, and the two agree across all nineteen.
// Upstream declares the same nineteen in the same order and the widths match --
// four bytes each except StayOnSameLayerAsMaster, which is the one byte at the
// end. Only identifiers changed; no field moved.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h
class SlavedUpdateModuleData
{
public:
	SlavedUpdateModuleData()
	{
		// Store order mirrors retail factory body.
		m_weldingSysName = 0;
		m_weldingFXBone = 0;
		m_guardMaxRange = 0;
		m_guardWanderRange = 0;
		m_attackRange = 0;
		m_attackWanderRange = 0;
		m_scoutRange = 0;
		m_scoutWanderRange = 0;
		m_distToTargetToGrantRangeBonus = 0;
		m_repairRatePerSecond = 0;
		m_repairWhenHealthBelowPercentage = 0;
		m_repairMinAltitude = 0;
		m_repairMaxAltitude = 0;
		m_minWeldFrames = 0;
		m_maxWeldFrames = 0;
		m_minReadyFrames = 0;
		m_maxReadyFrames = 0;
		m_stayOnSameLayerAsMaster = 0;
	}
	virtual ~SlavedUpdateModuleData();
private:
	unsigned int m_04;
	unsigned int m_guardMaxRange;
	unsigned int m_guardWanderRange;
	unsigned int m_attackRange;
	unsigned int m_attackWanderRange;
	unsigned int m_scoutRange;
	unsigned int m_scoutWanderRange;
	unsigned int m_distToTargetToGrantRangeBonus;
	unsigned int m_repairRange;
	unsigned int m_repairMinAltitude;
	unsigned int m_repairMaxAltitude;
	unsigned int m_repairRatePerSecond;
	unsigned int m_repairWhenHealthBelowPercentage;
	unsigned int m_minReadyFrames;
	unsigned int m_maxReadyFrames;
	unsigned int m_minWeldFrames;
	unsigned int m_maxWeldFrames;
	unsigned int m_weldingSysName;
	unsigned int m_weldingFXBone;
	unsigned char m_stayOnSameLayerAsMaster;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SlavedUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h
class SlavedUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SlavedUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlavedUpdate::friend_newModuleData(INI *ini)
{
	SlavedUpdateModuleData *data = new SlavedUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &SlavedUpdateFieldParse);
	return (ModuleData *)data;
}
