// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the ModuleData destructor.
//
// The object has a primary eight-byte base, a secondary polymorphic base at
// +0x08, and an AsciiString at +0x70.  The derived vtable is suppressed by
// novtable; the primary base's inline destructor restores the base vtable.

class CommandSetUpgradeModuleDataPrimaryBase
{
public:
	virtual ~CommandSetUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_04;
};

class CommandSetUpgradeModuleDataBase
{
public:
	virtual ~CommandSetUpgradeModuleDataBase();

private:
	unsigned char m_data[0x64];
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

class __declspec(novtable) CommandSetUpgradeModuleDataIntermediateBase
	: public CommandSetUpgradeModuleDataPrimaryBase
{
public:
	virtual ~CommandSetUpgradeModuleDataIntermediateBase() {}

private:
	CommandSetUpgradeModuleDataBase m_base;
};

class __declspec(novtable) CommandSetUpgradeModuleData
	: public CommandSetUpgradeModuleDataIntermediateBase
{
public:
	virtual ~CommandSetUpgradeModuleData();

private:
	BFMERetailAsciiString m_member;
};

// ??1CommandSetUpgradeModuleData@@UAE@XZ
CommandSetUpgradeModuleData::~CommandSetUpgradeModuleData()
{
}
