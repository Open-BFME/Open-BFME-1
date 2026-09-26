// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GrabPassengerSpecialPowerModuleData ctor.
// Base ctor pin 0x15c44 (shared SpecialPowerModuleData body / thunk).

class GrabPassengerSpecialPowerModuleDataBase
{
public:
	GrabPassengerSpecialPowerModuleDataBase();
	virtual ~GrabPassengerSpecialPowerModuleDataBase();

private:
	unsigned char m_base[0x20c];
};

class GrabPassengerSpecialPowerModuleData : public GrabPassengerSpecialPowerModuleDataBase
{
public:
	GrabPassengerSpecialPowerModuleData();
	virtual ~GrabPassengerSpecialPowerModuleData();

private:
	unsigned int m_field210;
	unsigned char m_byte214;
};

// ??0GrabPassengerSpecialPowerModuleData@@QAE@XZ
GrabPassengerSpecialPowerModuleData::GrabPassengerSpecialPowerModuleData()
	: GrabPassengerSpecialPowerModuleDataBase()
{
	m_field210 = 0;
	m_byte214 = 1;
}
