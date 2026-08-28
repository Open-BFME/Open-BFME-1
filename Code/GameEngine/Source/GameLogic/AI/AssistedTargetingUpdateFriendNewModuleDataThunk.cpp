// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// Open-BFME5: AssistedTargetingUpdate::friend_newModuleData

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssistedTargetingUpdate.h
class AssistedTargetingUpdateModuleData
{
public:
	AssistedTargetingUpdateModuleData();
	virtual ~AssistedTargetingUpdateModuleData();
private:
	unsigned int m_pad;
	unsigned int m_one;
	unsigned int m_weaponSlot;
	unsigned int m_laserFromAssistedName;
	unsigned int m_laserToTargetName;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AssistedTargetingUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssistedTargetingUpdate.h
class AssistedTargetingUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

AssistedTargetingUpdateModuleData::AssistedTargetingUpdateModuleData()
{
	m_one = 1;
	m_weaponSlot = 0;
	m_laserFromAssistedName = 0;
	m_laserToTargetName = 0;
}

// ?friend_newModuleData@AssistedTargetingUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AssistedTargetingUpdate::friend_newModuleData(INI *ini)
{
	AssistedTargetingUpdateModuleData *data = new AssistedTargetingUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &AssistedTargetingUpdateFieldParse);
	return (ModuleData *)data;
}
