// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ToggleMountedSpecialAbilityUpdateModuleData ctor.

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_base[0x250];
};

class ToggleMountedSpecialAbilityUpdateModuleData : public SpecialPowerModuleData
{
public:
	ToggleMountedSpecialAbilityUpdateModuleData();
	virtual ~ToggleMountedSpecialAbilityUpdateModuleData();

private:
	unsigned int m_field254;
	unsigned char m_byte258;
	unsigned char m_byte259;
};

// ??0ToggleMountedSpecialAbilityUpdateModuleData@@QAE@XZ
ToggleMountedSpecialAbilityUpdateModuleData::ToggleMountedSpecialAbilityUpdateModuleData()
	: SpecialPowerModuleData()
{
	m_field254 = 0;
	m_byte258 = 0;
	m_byte259 = 0;
}
