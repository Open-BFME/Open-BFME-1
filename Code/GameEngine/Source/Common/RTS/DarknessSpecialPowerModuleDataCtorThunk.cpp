// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DarknessSpecialPowerModuleData ctor.
// Base size 0x210; float 10.0f at +0x210; zero at +0x214.

class DarknessSpecialPowerModuleDataBase
{
public:
	DarknessSpecialPowerModuleDataBase();
	virtual ~DarknessSpecialPowerModuleDataBase();

private:
	unsigned char m_pad[0x20c];
};

class DarknessSpecialPowerModuleData : public DarknessSpecialPowerModuleDataBase
{
public:
	DarknessSpecialPowerModuleData();
	virtual ~DarknessSpecialPowerModuleData();

private:
	float m_210;
	unsigned int m_214;
};

// ??0DarknessSpecialPowerModuleData@@QAE@XZ
DarknessSpecialPowerModuleData::DarknessSpecialPowerModuleData()
{
	m_210 = 10.0f;
	m_214 = 0;
}
