// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ClearanceTestingSlowDeathBehaviorModuleData dtor. SEH ClearanceTestingSlowDeathBehaviorModuleDataMember @+0x1a8 then base.

class ClearanceTestingSlowDeathBehaviorModuleDataMember
{
public:
	~ClearanceTestingSlowDeathBehaviorModuleDataMember();
private:
	unsigned char m_pad[4];
};

class SlowDeathBehaviorModuleData
{
public:
	virtual ~SlowDeathBehaviorModuleData();
private:
	unsigned char m_pad[0x1a4];
};

class __declspec(novtable) ClearanceTestingSlowDeathBehaviorModuleData : public SlowDeathBehaviorModuleData
{
public:
	virtual ~ClearanceTestingSlowDeathBehaviorModuleData();
private:
	ClearanceTestingSlowDeathBehaviorModuleDataMember m_member;
};

// ??1ClearanceTestingSlowDeathBehaviorModuleData@@UAE@XZ
ClearanceTestingSlowDeathBehaviorModuleData::~ClearanceTestingSlowDeathBehaviorModuleData()
{
}
