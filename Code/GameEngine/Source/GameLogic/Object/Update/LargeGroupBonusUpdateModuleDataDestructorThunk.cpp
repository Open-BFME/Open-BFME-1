// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LargeGroupBonusUpdateModuleData dtor (ICF GrantStealth).
// Members @+0x0c, @+0x20, @+0x2c.

class LargeGroupBonusUpdateModuleDataMemberA
{
public:
	~LargeGroupBonusUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class LargeGroupBonusUpdateModuleDataMemberB
{
public:
	~LargeGroupBonusUpdateModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class LargeGroupBonusUpdateModuleDataMemberC
{
public:
	~LargeGroupBonusUpdateModuleDataMemberC();
private:
	unsigned char m_pad[4];
};

class LargeGroupBonusUpdateModuleDataBase
{
public:
	virtual ~LargeGroupBonusUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x8];
};

class __declspec(novtable) LargeGroupBonusUpdateModuleData
	: public LargeGroupBonusUpdateModuleDataBase
{
public:
	virtual ~LargeGroupBonusUpdateModuleData();
private:
	LargeGroupBonusUpdateModuleDataMemberA m_a;
	unsigned char m_gap1[0x10];
	LargeGroupBonusUpdateModuleDataMemberB m_b;
	unsigned char m_gap2[0x8];
	LargeGroupBonusUpdateModuleDataMemberC m_c;
};

// ??1LargeGroupBonusUpdateModuleData@@UAE@XZ
LargeGroupBonusUpdateModuleData::~LargeGroupBonusUpdateModuleData()
{
}
