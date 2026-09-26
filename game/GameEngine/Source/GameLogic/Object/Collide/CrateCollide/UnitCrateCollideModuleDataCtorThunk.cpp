// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: UnitCrateCollideModuleData lifecycle lifted from retail.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString()
		: m_data(0)
	{
	}

	~AsciiString() { releaseBuffer(); }
	void set(const char *text, int length);

private:
	void releaseBuffer();

	char *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

// The base string at +0x44 and the derived string at +0x58 are destroyed in
// reverse ownership order. Keeping the base's trailing bytes explicit also
// preserves the constructor's +0x54 derived-field boundary.
class __declspec(novtable) CrateCollideModuleData : public Snapshot
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData() {}

private:
	unsigned char m_head[0x40];
	AsciiString m_first;
	unsigned char m_tail[0x0c];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UnitCrateCollide.h
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

// Retail elides the derived and intermediate vptr stores during teardown; the
// final Snapshot vptr store remains observable in the inlined base destructor.
class __declspec(novtable) UnitCrateCollideModuleData;

// ??1UnitCrateCollideModuleData@@UAE@XZ
UnitCrateCollideModuleData::~UnitCrateCollideModuleData()
{
}
