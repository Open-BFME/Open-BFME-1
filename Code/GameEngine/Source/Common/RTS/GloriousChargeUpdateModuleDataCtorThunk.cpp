// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GloriousChargeUpdateModuleData - SpecialPower base + 3 zero dwords.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_base[0x250];
};

class GloriousChargeUpdateModuleData : public SpecialPowerModuleData
{
public:
	GloriousChargeUpdateModuleData();
	virtual ~GloriousChargeUpdateModuleData();

private:
	unsigned int m_field254;
	unsigned int m_field258;
	unsigned int m_field25c;
};

// ??0GloriousChargeUpdateModuleData@@QAE@XZ
GloriousChargeUpdateModuleData::GloriousChargeUpdateModuleData()
	: SpecialPowerModuleData()
{
	m_field254 = 0;
	m_field258 = 0;
	m_field25c = 0;
}
