// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnBehaviorModuleData dtor. dual members @+0x20/+0x58.

class SpawnBehaviorModuleDataMemberA
{
public:
	~SpawnBehaviorModuleDataMemberA();
private:
	unsigned char m_pad[0x38];
};

class SpawnBehaviorModuleDataMemberB
{
public:
	~SpawnBehaviorModuleDataMemberB();
private:
	unsigned char m_pad[0x4];
};

class SpawnBehaviorModuleDataBase
{
public:
	virtual ~SpawnBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x1c];
};

class __declspec(novtable) SpawnBehaviorModuleData : public SpawnBehaviorModuleDataBase
{
public:
	virtual ~SpawnBehaviorModuleData();
private:
	SpawnBehaviorModuleDataMemberA m_a;
	SpawnBehaviorModuleDataMemberB m_b;
};

// ??1SpawnBehaviorModuleData@@UAE@XZ
SpawnBehaviorModuleData::~SpawnBehaviorModuleData()
{
}
