// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BattlePlanUpdateModuleData dtor. 14x same member.

class BattlePlanUpdateModuleDataMemberA
{
public:
	~BattlePlanUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class BattlePlanUpdateModuleDataBase
{
public:
	virtual ~BattlePlanUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x18];
};

class __declspec(novtable) BattlePlanUpdateModuleData : public BattlePlanUpdateModuleDataBase
{
public:
	virtual ~BattlePlanUpdateModuleData();
private:
	BattlePlanUpdateModuleDataMemberA m_a;
	BattlePlanUpdateModuleDataMemberA m_b;
	BattlePlanUpdateModuleDataMemberA m_c;
	BattlePlanUpdateModuleDataMemberA m_d;
	BattlePlanUpdateModuleDataMemberA m_e;
	BattlePlanUpdateModuleDataMemberA m_f;
	BattlePlanUpdateModuleDataMemberA m_g;
	BattlePlanUpdateModuleDataMemberA m_h;
	BattlePlanUpdateModuleDataMemberA m_i;
	BattlePlanUpdateModuleDataMemberA m_j;
	BattlePlanUpdateModuleDataMemberA m_k;
	BattlePlanUpdateModuleDataMemberA m_l;
	BattlePlanUpdateModuleDataMemberA m_m;
	unsigned char m_gap13[0x4c];
	BattlePlanUpdateModuleDataMemberA m_n;
};

// ??1BattlePlanUpdateModuleData@@UAE@XZ
BattlePlanUpdateModuleData::~BattlePlanUpdateModuleData()
{
}
