// cl: /DNDEBUG /MD /EHsc

// FireWeaponWhenDamagedBehavior::friend_newModuleData, retail 0x0012A170,
// 54 bytes.
//
// The factory allocates 0x9C bytes, constructs a
// FireWeaponWhenDamagedBehaviorModuleData (0x0012A100, reached through ILT
// 0x00012233) and hands INI::initFromINIMultiProc the ILT 0x0002969A of
// FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse (0x00123180). See
// identity_evidence/0012a170-fireweaponwhendamaged-friend-newmoduledata.md.

class MultiIniFieldParse;
class ModuleData;

void *__cdecl operator new(unsigned int size);

// Retail builds the data without an EH frame, so the constructor is reached
// through this address-named view of its thunk rather than a new-expression.
class Rva0012A170ModuleData
{
public:
	Rva0012A170ModuleData *construct();

private:
	char m_data[0x9c];
};

class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(
		void *object,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

class FireWeaponWhenDamagedBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FireWeaponWhenDamagedBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponWhenDamagedBehavior::friend_newModuleData(INI *ini)
{
	void *memory = operator new(sizeof(Rva0012A170ModuleData));
	Rva0012A170ModuleData *data;
	if (memory != 0)
	{
		data = static_cast<Rva0012A170ModuleData *>(memory)->construct();
	}
	else
	{
		data = 0;
	}

	if (ini != 0)
		ini->initFromINIMultiProc(data, FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
