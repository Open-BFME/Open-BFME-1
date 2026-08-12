// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: CreateCrateDieModuleData constructor lifted from retail.

#include <list>

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}

private:
	unsigned char m_data[4];
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_data[0x2c];
};

class DieModuleData : public Snapshot
{
public:
	DieModuleData() {}
	virtual ~DieModuleData();

private:
	InstantDeathDieMuxData m_dieMuxData;
};

class CreateCrateDieModuleData : public DieModuleData
{
public:
	CreateCrateDieModuleData();
	virtual ~CreateCrateDieModuleData();

private:
	std::list<AsciiString> m_crateNameList;
};

// ??0CreateCrateDieModuleData@@QAE@XZ
CreateCrateDieModuleData::CreateCrateDieModuleData()
	: DieModuleData(), m_crateNameList()
{
	m_crateNameList.clear();
}
