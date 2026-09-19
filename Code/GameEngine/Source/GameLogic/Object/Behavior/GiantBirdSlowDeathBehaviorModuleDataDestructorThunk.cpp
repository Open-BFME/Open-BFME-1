// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GiantBirdSlowDeathBehaviorModuleData dtor. SEH GiantBirdSlowDeathBehaviorModuleDataMember @+0x1b4 then base.

class GiantBirdSlowDeathBehaviorModuleDataMember
{
public:
	~GiantBirdSlowDeathBehaviorModuleDataMember();
private:
	unsigned char m_pad[4];
};

class GiantBirdSlowDeathBehaviorModuleDataBase
{
public:
	virtual ~GiantBirdSlowDeathBehaviorModuleDataBase();
private:
	unsigned char m_pad[0x1b0];
};

class __declspec(novtable) GiantBirdSlowDeathBehaviorModuleData : public GiantBirdSlowDeathBehaviorModuleDataBase
{
public:
	virtual ~GiantBirdSlowDeathBehaviorModuleData();
private:
	GiantBirdSlowDeathBehaviorModuleDataMember m_member;
};

// ??1GiantBirdSlowDeathBehaviorModuleData@@UAE@XZ
GiantBirdSlowDeathBehaviorModuleData::~GiantBirdSlowDeathBehaviorModuleData()
{
}
