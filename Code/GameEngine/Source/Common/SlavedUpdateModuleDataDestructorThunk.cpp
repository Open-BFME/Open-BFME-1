// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift ModuleData dtor MASM dump to clean C++.
// Retail @0x00126980: SEH dtor destroying two adjacent 4-byte string members
// at this+0x4C then this+0x48 (reverse declaration order), then an inlined
// base vftable store. SlavedUpdateModuleData's m_weldingSysName /
// m_weldingFXBone sit at exactly those offsets after 8 base bytes and the
// 16 int/real fields from the GeneralsMD SlavedUpdate.h layout.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char *m_str;
public:
	~AsciiString();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleData
{
public:
	virtual ~UpdateModuleData() {}
	unsigned int m_04;
};

class __declspec(novtable) SlavedUpdateModuleData : public UpdateModuleData
{
public:
	virtual ~SlavedUpdateModuleData();

private:
	int m_guardMaxRange;
	int m_guardWanderRange;
	int m_attackRange;
	int m_attackWanderRange;
	int m_scoutRange;
	int m_scoutWanderRange;
	int m_distToTargetToGrantRangeBonus;
	int m_repairRange;
	float m_repairMinAltitude;
	float m_repairMaxAltitude;
	float m_repairRatePerSecond;
	int m_repairWhenHealthBelowPercentage;
	int m_minReadyFrames;
	int m_maxReadyFrames;
	int m_minWeldFrames;
	int m_maxWeldFrames;
	AsciiString m_weldingSysName;
	AsciiString m_weldingFXBone;
	unsigned char m_stayOnSameLayerAsMaster;
};

// ??1SlavedUpdateModuleData@@UAE@XZ
SlavedUpdateModuleData::~SlavedUpdateModuleData()
{
}
