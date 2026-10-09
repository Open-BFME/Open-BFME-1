// cl: /DNDEBUG /MD /EHsc

// ReplenishUnitsBehavior::friend_newModuleData, retail 0x00117420, 110 bytes.
//
// The factory allocates 0x90 bytes, constructs a
// ReplenishUnitsBehaviorModuleData (0x00204ED0, through ILT 0x0003025B) and
// hands INI::initFromINIMultiProc the ILT 0x0002B1F7 of
// ReplenishUnitsBehaviorModuleData::buildFieldParse (0x00204F30). It sits next to
// the matched ReplenishUnitsBehavior::friend_newModuleInstance at 0x001173A0.
// See identity_evidence/00117420-replenishunits-friend-newmoduledata.md.

class INI;
class ModuleData;
class MultiIniFieldParse;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

class ReplenishUnitsBehaviorModuleData
{
public:
	ReplenishUnitsBehaviorModuleData();
	virtual ~ReplenishUnitsBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &p);

private:
	unsigned char m_unmodelled[0x90 - 4];
};

class ReplenishUnitsBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ReplenishUnitsBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ReplenishUnitsBehavior::friend_newModuleData(INI *ini)
{
	ReplenishUnitsBehaviorModuleData *data = new ReplenishUnitsBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ReplenishUnitsBehaviorModuleData::buildFieldParse);
	return (ModuleData *)data;
}
