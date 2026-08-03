// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FellBeastSwoopPowerModuleData ctor - base size 0x254, then two dwords.

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	// vptr (4) + 0x250 = 0x254 total base
	unsigned char m_base[0x250];
};

class FellBeastSwoopPowerModuleData : public SpecialPowerModuleData
{
public:
	FellBeastSwoopPowerModuleData();
	virtual ~FellBeastSwoopPowerModuleData();

private:
	unsigned int m_field254;
	unsigned int m_field258;
};

// ??0FellBeastSwoopPowerModuleData@@QAE@XZ
FellBeastSwoopPowerModuleData::FellBeastSwoopPowerModuleData()
	: SpecialPowerModuleData()
{
	m_field254 = 0;
	m_field258 = 0;
}
