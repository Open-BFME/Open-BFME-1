// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GrantStealthBehaviorModuleData dtor.
// Members @+0x0c (Buffer thunk), @+0x20 (other), @+0x2c (Buffer body).

class GrantStealthBehaviorModuleDataMemberA
{
public:
	~GrantStealthBehaviorModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class GrantStealthBehaviorModuleDataMemberB
{
public:
	~GrantStealthBehaviorModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class GrantStealthBehaviorModuleDataMemberC
{
public:
	~GrantStealthBehaviorModuleDataMemberC();
private:
	unsigned char m_pad[4];
};

class GrantStealthBehaviorModuleDataBase
{
public:
	virtual ~GrantStealthBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x8];
};

class __declspec(novtable) GrantStealthBehaviorModuleData
	: public GrantStealthBehaviorModuleDataBase
{
public:
	virtual ~GrantStealthBehaviorModuleData();
private:
	GrantStealthBehaviorModuleDataMemberA m_a;
	unsigned char m_gap1[0x10];
	GrantStealthBehaviorModuleDataMemberB m_b;
	unsigned char m_gap2[0x8];
	GrantStealthBehaviorModuleDataMemberC m_c;
};

// ??1GrantStealthBehaviorModuleData@@UAE@XZ
GrantStealthBehaviorModuleData::~GrantStealthBehaviorModuleData()
{
}
