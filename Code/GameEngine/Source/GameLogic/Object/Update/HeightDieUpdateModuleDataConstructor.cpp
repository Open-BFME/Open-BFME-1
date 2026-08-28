// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HeightDieUpdateModuleData default ctor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HeightDieUpdate.h
class HeightDieUpdateModuleData
{
public:
	HeightDieUpdateModuleData();
	virtual ~HeightDieUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned char m_0c;
	unsigned char m_0d;
	unsigned char m_pad0e;
	unsigned char m_pad0f;
	float m_10;
	unsigned char m_14;
	unsigned char m_pad15;
	unsigned char m_pad16;
	unsigned char m_pad17;
	unsigned int m_18;
};

// ??0HeightDieUpdateModuleData@@QAE@XZ
HeightDieUpdateModuleData::HeightDieUpdateModuleData()
{
	m_08 = 0;
	m_0c = 0;
	m_0d = 0;
	m_10 = -1.0f;
	m_14 = 0;
	m_18 = 0;
}