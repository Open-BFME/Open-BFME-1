// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RainOfFireUpdateModuleData leaf ctor.

class RainOfFireUpdateModuleData
{
public:
	RainOfFireUpdateModuleData();
	virtual ~RainOfFireUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned int m_0c;
	float m_10;
	float m_14;
	unsigned int m_18;
	float m_1c;
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
};

// ??0RainOfFireUpdateModuleData@@QAE@XZ
RainOfFireUpdateModuleData::RainOfFireUpdateModuleData()
{
	m_08 = 0x96;
	m_0c = 0x78;
	m_10 = 100.0f;
	m_14 = 0.25f;
	m_18 = 0;
	m_1c = 1.0f;
	m_20 = 1.0f;
	m_24 = 0;
	m_28 = 0;
	m_2c = 0;
}
