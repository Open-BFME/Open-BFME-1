// cl: /DNDEBUG /MD /EHsc

// Open-BFME: CivilianSpawnCollideModuleData scalar-deleting destructor at
// retail 0x00217590 (30 bytes).  The matched module-data constructor at
// 0x00217360, complete destructor at 0x002175C0, and the named
// CivilianSpawnCollide module-data factory establish this class identity.

class CivilianSpawnCollideModuleData
{
public:
	__declspec(noinline) virtual ~CivilianSpawnCollideModuleData();
};

CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData()
{
}

void Force_CivilianSpawnCollideModuleData_Deleting_Destructor(
	CivilianSpawnCollideModuleData *value)
{
	delete value;
}
