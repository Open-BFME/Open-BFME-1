// cl: /DNDEBUG /MD /EHsc

// BFME member layouts cross-checked against the exact destructor at
// Code/GameEngine/Source/Common/CivilianSpawnUpdateModuleDataDestructorThunk.cpp.
class CivilianSpawnUpdateModuleDataMemberA
{
public:
	CivilianSpawnUpdateModuleDataMemberA();
	~CivilianSpawnUpdateModuleDataMemberA();

	unsigned int m_value0;
	unsigned int m_value1;
};

class CivilianSpawnUpdateModuleDataMemberB
{
public:
	CivilianSpawnUpdateModuleDataMemberB() : m_value( 0 ) {}
	~CivilianSpawnUpdateModuleDataMemberB();

private:
	unsigned int m_value;
};

class CivilianSpawnUpdateModuleDataBase
{
public:
	virtual ~CivilianSpawnUpdateModuleDataBase() {}

protected:
	unsigned int m_reserved04;
	unsigned int m_maxSpawnCount;
};

class CivilianSpawnUpdateModuleData : public CivilianSpawnUpdateModuleDataBase
{
public:
	CivilianSpawnUpdateModuleData();
	virtual ~CivilianSpawnUpdateModuleData();

private:
	CivilianSpawnUpdateModuleDataMemberA m_spawnPolicy;
	CivilianSpawnUpdateModuleDataMemberB m_policyState;
	unsigned int m_field18;
	unsigned int m_field1C;
};

// ??0CivilianSpawnUpdateModuleData@@QAE@XZ
CivilianSpawnUpdateModuleData::CivilianSpawnUpdateModuleData()
{
	m_field18 = 0;
	m_field1C = 0;
	m_maxSpawnCount = 5;
	m_spawnPolicy.m_value1 = 300;
}
