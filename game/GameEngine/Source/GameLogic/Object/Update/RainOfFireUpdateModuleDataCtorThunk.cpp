// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RainOfFireUpdateModuleData leaf ctor.

class RainOfFireUpdateModuleData
{
public:
	RainOfFireUpdateModuleData();
	virtual ~RainOfFireUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_startRainTime;
	unsigned int m_darknessFadeTime;
	float m_rainEmitterHeight;
	float m_darknessLevel;
	unsigned int m_jitterRadius;
	float m_dpsMin;
	float m_dpsMax;
	unsigned int m_dpsRampupTime;
	unsigned int m_28;
	unsigned int m_2c;
};

// ??0RainOfFireUpdateModuleData@@QAE@XZ
RainOfFireUpdateModuleData::RainOfFireUpdateModuleData()
{
	m_startRainTime = 0x96;
	m_darknessFadeTime = 0x78;
	m_rainEmitterHeight = 100.0f;
	m_darknessLevel = 0.25f;
	m_jitterRadius = 0;
	m_dpsMin = 1.0f;
	m_dpsMax = 1.0f;
	m_dpsRampupTime = 0;
	m_28 = 0;
	m_2c = 0;
}
