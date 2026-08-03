// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift UpgradeDieModuleData dtor MASM to clean C++.
// Retail destroys the AsciiString member at this+0x34 under an SEH frame,
// then runs the inlined DieModuleData base dtor (base vtable store).

class AsciiString
{
public:
	~AsciiString();
};

class UpgradeDieModuleDataBase
{
public:
	virtual ~UpgradeDieModuleDataBase() {}

private:
	unsigned char m_pad[0x30];
};

class __declspec(novtable) UpgradeDieModuleData
	: public UpgradeDieModuleDataBase
{
public:
	virtual ~UpgradeDieModuleData();

private:
	AsciiString m_upgradeName;
};

// ??1UpgradeDieModuleData@@UAE@XZ
UpgradeDieModuleData::~UpgradeDieModuleData()
{
}
