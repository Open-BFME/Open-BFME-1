// cl: /DNDEBUG /MD /EHsc

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString()
	{
		m_data = 0;
	}

	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void clear(void)
	{
		releaseBuffer();
	}

private:
	void releaseBuffer(void);

	char *m_data;
};

class ZeroWord
{
public:
	ZeroWord()
	{
		m_value = 0;
	}

	void clear(void)
	{
		m_value = 0;
	}

private:
	volatile unsigned int m_value;
};

class ModuleDataBase_DefectorSpecialPowerModuleData
{
public:
	ModuleDataBase_DefectorSpecialPowerModuleData();
	virtual ~ModuleDataBase_DefectorSpecialPowerModuleData();

private:
	unsigned char m_pad[0x20c];
};

class WeaponChangeSpecialPowerModuleModuleData
	: public ModuleDataBase_DefectorSpecialPowerModuleData
{
public:
	WeaponChangeSpecialPowerModuleModuleData();

private:
	ZeroWord m_flagsUsedForToggle;
	unsigned int m_toggleOnSleepFrames;
	unsigned int m_toggleOffSleepFrames;
	BFMERetailAsciiString m_toggleOnAttributeModifier;
	BFMERetailAsciiString m_toggleOffAttributeModifier;
};

// ??0WeaponChangeSpecialPowerModuleModuleData@@QAE@XZ
WeaponChangeSpecialPowerModuleModuleData::WeaponChangeSpecialPowerModuleModuleData()
	: ModuleDataBase_DefectorSpecialPowerModuleData(), m_flagsUsedForToggle(), m_toggleOnSleepFrames(0), m_toggleOffSleepFrames(0)
{
	m_flagsUsedForToggle.clear();
	m_toggleOnAttributeModifier.clear();
	m_toggleOffAttributeModifier.clear();
}
