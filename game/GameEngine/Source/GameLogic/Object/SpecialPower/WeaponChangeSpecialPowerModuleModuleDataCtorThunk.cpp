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
	ZeroWord m_210;
	unsigned int m_214;
	unsigned int m_218;
	BFMERetailAsciiString m_21c;
	BFMERetailAsciiString m_220;
};

// ??0WeaponChangeSpecialPowerModuleModuleData@@QAE@XZ
WeaponChangeSpecialPowerModuleModuleData::WeaponChangeSpecialPowerModuleModuleData()
	: ModuleDataBase_DefectorSpecialPowerModuleData(), m_210(), m_214(0), m_218(0)
{
	m_210.clear();
	m_21c.clear();
	m_220.clear();
}
