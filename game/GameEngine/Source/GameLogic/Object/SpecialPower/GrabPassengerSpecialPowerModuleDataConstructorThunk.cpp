// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GrabPassengerSpecialPowerModuleData ctor.
// Base ctor pin 0x15c44 is an ILT thunk to 0x00268120, the body the ledger
// carries as ??0RiderChangeContainModuleData@@QAE@XZ: the SpecialPower
// module-data constructors are ICF-shared, so the base is spelled with the
// ledger's owning name and this TU's base class is only a layout view of it.

class RiderChangeContainModuleData
{
public:
	RiderChangeContainModuleData();
	virtual ~RiderChangeContainModuleData();

private:
	unsigned char m_base[0x20c];
};

class GrabPassengerSpecialPowerModuleData : public RiderChangeContainModuleData
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
	: RiderChangeContainModuleData()
{
	m_field210 = 0;
	m_byte214 = 1;
}
