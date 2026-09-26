// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EnragedBehaviorModuleData dtor. PropagandaTower SEH pattern.

class EnragedBehaviorModuleDataMember
{
public:
	~EnragedBehaviorModuleDataMember();
};

class EnragedBehaviorModuleDataBase
{
public:
	virtual ~EnragedBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) EnragedBehaviorModuleData : public EnragedBehaviorModuleDataBase
{
public:
	virtual ~EnragedBehaviorModuleData();
private:
	EnragedBehaviorModuleDataMember m_member;
};

// ??1EnragedBehaviorModuleData@@UAE@XZ
EnragedBehaviorModuleData::~EnragedBehaviorModuleData()
{
}
