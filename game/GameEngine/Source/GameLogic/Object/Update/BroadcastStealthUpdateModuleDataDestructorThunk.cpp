// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BroadcastStealthUpdateModuleData dtor. dual different members SEH.

class BroadcastStealthUpdateModuleDataMemberA
{
public:
	~BroadcastStealthUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class BroadcastStealthUpdateModuleDataMemberB
{
public:
	~BroadcastStealthUpdateModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class BroadcastStealthUpdateModuleDataBase
{
public:
	virtual ~BroadcastStealthUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x24];
};

class __declspec(novtable) BroadcastStealthUpdateModuleData : public BroadcastStealthUpdateModuleDataBase
{
public:
	virtual ~BroadcastStealthUpdateModuleData();
private:
	BroadcastStealthUpdateModuleDataMemberA m_a;
	BroadcastStealthUpdateModuleDataMemberB m_b;
};

// ??1BroadcastStealthUpdateModuleData@@UAE@XZ
BroadcastStealthUpdateModuleData::~BroadcastStealthUpdateModuleData()
{
}
