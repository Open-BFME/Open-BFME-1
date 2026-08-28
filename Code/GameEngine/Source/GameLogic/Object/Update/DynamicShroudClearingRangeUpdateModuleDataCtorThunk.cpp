// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DynamicShroudClearingRangeUpdateModuleData constructor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();

private:
	unsigned int m_data[0x0c];
};

class __declspec(novtable) DynamicShroudClearingRangeUpdateModuleDataBase
{
public:
	virtual ~DynamicShroudClearingRangeUpdateModuleDataBase();

private:
	unsigned int m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicShroudClearingRangeUpdate.h
class DynamicShroudClearingRangeUpdateModuleData
	: public DynamicShroudClearingRangeUpdateModuleDataBase
{
public:
	DynamicShroudClearingRangeUpdateModuleData();
	virtual ~DynamicShroudClearingRangeUpdateModuleData();

private:
	unsigned int m_shrinkDelay;
	unsigned int m_shrinkTime;
	unsigned int m_growDelay;
	unsigned int m_growTime;
	float m_finalVision;
	unsigned int m_changeInterval;
	unsigned int m_growInterval;
	bool m_doSpySatFX;
	RadiusDecalTemplate m_gridDecalTemplate;
};

// ??0DynamicShroudClearingRangeUpdateModuleData@@QAE@XZ
DynamicShroudClearingRangeUpdateModuleData::DynamicShroudClearingRangeUpdateModuleData()
{
	m_shrinkDelay = 0;
	m_shrinkTime = 0;
	m_growDelay = 0;
	m_growTime = 0;
	m_finalVision = 0.0f;
	m_changeInterval = 0;
	m_growInterval = 0;
	m_doSpySatFX = false;
}
