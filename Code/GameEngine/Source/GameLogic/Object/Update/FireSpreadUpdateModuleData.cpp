// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// Open-BFME5: FireSpreadUpdateModuleData default ctor.
// Zero order: +0xc, +0x10, +0x8, +0x14.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireSpreadUpdate.h
class FireSpreadUpdateModuleData
{
public:
	FireSpreadUpdateModuleData();
	virtual ~FireSpreadUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_oclEmbers;
	unsigned int m_minSpreadTryDelayData;
	unsigned int m_maxSpreadTryDelayData;
	unsigned int m_spreadTryRange;
};

// ??0FireSpreadUpdateModuleData@@QAE@XZ
FireSpreadUpdateModuleData::FireSpreadUpdateModuleData()
{
	m_minSpreadTryDelayData = 0;
	m_maxSpreadTryDelayData = 0;
	m_oclEmbers = 0;
	m_spreadTryRange = 0;
}