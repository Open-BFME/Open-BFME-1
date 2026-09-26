// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: UpgradeModuleModuleData scalar-deleting destructor at retail RVA
// 0x001295C0 (30 bytes).  The exact named constructor at 0x00128D20 and the
// matched complete destructor at 0x00128FA0 establish this ModuleData class;
// UpgradeModuleModuleDataDestructorThunk.cpp owns its ActiveBody base and
// layout-string cleanup.

class UpgradeModuleModuleData
{
public:
	__declspec(noinline) virtual ~UpgradeModuleModuleData();
};

UpgradeModuleModuleData::~UpgradeModuleModuleData()
{
}

void Force_UpgradeModuleModuleData_Deleting_Destructor(
	UpgradeModuleModuleData *value)
{
	delete value;
}
