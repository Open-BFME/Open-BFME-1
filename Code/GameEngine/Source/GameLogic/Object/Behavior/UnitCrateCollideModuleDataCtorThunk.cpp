// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: UnitCrateCollideModuleData constructor lifted from retail.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CrateCollide.h
class CrateCollideModuleData
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData();

private:
	unsigned char m_data[0x50];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UnitCrateCollide.h
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
