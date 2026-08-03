// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift ToppleUpdateModuleData dtor MASM to clean C++.
// Retail destroys UpgradeList at this+0x10 under an SEH frame, then runs the
// inlined UpdateModuleData base dtor (base vtable store).

class UpgradeList
{
public:
	~UpgradeList();
};

class ToppleUpdateModuleDataBase
{
public:
	virtual ~ToppleUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) ToppleUpdateModuleData
	: public ToppleUpdateModuleDataBase
{
public:
	virtual ~ToppleUpdateModuleData();

private:
	UpgradeList m_upgradeList;
};

// ??1ToppleUpdateModuleData@@UAE@XZ
ToppleUpdateModuleData::~ToppleUpdateModuleData()
{
}
