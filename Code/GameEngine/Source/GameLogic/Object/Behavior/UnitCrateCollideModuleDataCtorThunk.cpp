// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: UnitCrateCollideModuleData constructor lifted from retail.

class CrateCollideModuleData
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData();

private:
	unsigned char m_data[0x50];
};

class AsciiString
{
public:
	AsciiString()
		: m_data(0)
	{
	}

	~AsciiString();
	void set(const char *text, int length);

private:
	char *m_data;
};

class UnitCrateCollideModuleData : public CrateCollideModuleData
{
public:
	UnitCrateCollideModuleData();
	virtual ~UnitCrateCollideModuleData();

private:
	unsigned int m_unitCount;
	AsciiString m_unitType;
};

// ??0UnitCrateCollideModuleData@@QAE@XZ
UnitCrateCollideModuleData::UnitCrateCollideModuleData()
	: CrateCollideModuleData(), m_unitType()
{
	m_unitCount = 0;
	m_unitType.set("", 0);
}
