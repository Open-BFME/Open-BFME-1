// cl: /DNDEBUG /MD /EHsc

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
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
};

// ??0FireSpreadUpdateModuleData@@QAE@XZ
FireSpreadUpdateModuleData::FireSpreadUpdateModuleData()
{
	m_0c = 0;
	m_10 = 0;
	m_08 = 0;
	m_14 = 0;
}