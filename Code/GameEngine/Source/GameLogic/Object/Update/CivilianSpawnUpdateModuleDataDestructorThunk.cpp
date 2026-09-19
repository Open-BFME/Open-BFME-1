// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CivilianSpawnUpdateModuleData dtor. dual members @+0xc/+0x14.

class CivilianSpawnUpdateModuleDataMemberA
{
public:
	~CivilianSpawnUpdateModuleDataMemberA();
private:
	unsigned char m_pad[0x8];
};

class CivilianSpawnUpdateModuleDataMemberB
{
public:
	~CivilianSpawnUpdateModuleDataMemberB();
private:
	unsigned char m_pad[0x4];
};

class CivilianSpawnUpdateModuleDataBase
{
public:
	virtual ~CivilianSpawnUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x8];
};

class __declspec(novtable) CivilianSpawnUpdateModuleData : public CivilianSpawnUpdateModuleDataBase
{
public:
	virtual ~CivilianSpawnUpdateModuleData();
private:
	CivilianSpawnUpdateModuleDataMemberA m_a;
	CivilianSpawnUpdateModuleDataMemberB m_b;
};

// ??1CivilianSpawnUpdateModuleData@@UAE@XZ
CivilianSpawnUpdateModuleData::~CivilianSpawnUpdateModuleData()
{
}
