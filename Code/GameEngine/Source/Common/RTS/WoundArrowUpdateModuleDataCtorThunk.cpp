// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WoundArrowUpdateModuleData - base + float 100.0f + zero dword.

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_base[0x250];
};

class WoundArrowUpdateModuleData : public SpecialPowerModuleData
{
public:
	WoundArrowUpdateModuleData();
	virtual ~WoundArrowUpdateModuleData();

private:
	float m_field254;
	unsigned int m_field258;
};

// ??0WoundArrowUpdateModuleData@@QAE@XZ
WoundArrowUpdateModuleData::WoundArrowUpdateModuleData()
	: SpecialPowerModuleData()
{
	m_field254 = 100.0f;
	m_field258 = 0;
}
