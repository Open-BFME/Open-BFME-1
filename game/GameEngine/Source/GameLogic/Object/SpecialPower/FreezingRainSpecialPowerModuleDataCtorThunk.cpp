// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FreezingRainSpecialPowerModuleData ctor (same base as Darkness).

class FreezingRainSpecialPowerModuleDataBase
{
public:
	FreezingRainSpecialPowerModuleDataBase();
	virtual ~FreezingRainSpecialPowerModuleDataBase();

private:
	unsigned char m_pad[0x20c];
};

class FreezingRainSpecialPowerModuleData : public FreezingRainSpecialPowerModuleDataBase
{
public:
	FreezingRainSpecialPowerModuleData();
	virtual ~FreezingRainSpecialPowerModuleData();

private:
	float m_210;
	unsigned int m_214;
};

// ??0FreezingRainSpecialPowerModuleData@@QAE@XZ
FreezingRainSpecialPowerModuleData::FreezingRainSpecialPowerModuleData()
{
	m_210 = 10.0f;
	m_214 = 0;
}
