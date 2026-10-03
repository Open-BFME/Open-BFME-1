// cl: /DNDEBUG /MD /EHsc

// The +0x0C spawn-policy member's constructor is reached through retail's ILT
// thunk at 0x0003747A (the ledger's ?j_0003747a@@YAXXZ, the ICF-folded handle
// body), not through a body of its own, so the constructor here is inline and
// forwards to that thunk. The local view class therefore carries a name of its
// own: `CivilianSpawnUpdateModuleDataMemberA` is pinned to 0x0003747A and an
// in-class body under that name would claim the address retail's `?j_` thunk
// already holds. Layout is unchanged; the destructor TU keeps its own view.
extern void j_0003747a();

// BFME member layouts cross-checked against the exact destructor at
// game/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnUpdateModuleDataDestructorThunk.cpp.
class CivilianSpawnUpdateSpawnPolicy
{
public:
	CivilianSpawnUpdateSpawnPolicy() { ((void (__fastcall *)(CivilianSpawnUpdateSpawnPolicy *))j_0003747a)(this); }
	~CivilianSpawnUpdateSpawnPolicy();

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
	CivilianSpawnUpdateSpawnPolicy m_spawnPolicy;
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
