// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DevastateSpecialPowerModuleData ctor.
// Base size 0x210; four zero dwords at +0x210..+0x21c.

class DevastateSpecialPowerModuleDataBase
{
public:
	DevastateSpecialPowerModuleDataBase();
	virtual ~DevastateSpecialPowerModuleDataBase();

private:
	unsigned char m_pad[0x20c];
};

class DevastateSpecialPowerModuleData : public DevastateSpecialPowerModuleDataBase
{
public:
	DevastateSpecialPowerModuleData();
	virtual ~DevastateSpecialPowerModuleData();

private:
	unsigned int m_210;
	unsigned int m_214;
	unsigned int m_218;
	unsigned int m_21c;
};

// ??0DevastateSpecialPowerModuleData@@QAE@XZ
DevastateSpecialPowerModuleData::DevastateSpecialPowerModuleData()
{
	m_210 = 0;
	m_214 = 0;
	m_218 = 0;
	m_21c = 0;
}