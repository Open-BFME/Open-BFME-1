// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HijackerUpdate.h
class HijackerUpdateModuleData
{
public:
	HijackerUpdateModuleData();
	virtual ~HijackerUpdateModuleData();

private:
	int m_unused;
	int m_attachToBone;
	int m_parachuteName;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HijackerUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HijackerUpdate.h
class HijackerUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

HijackerUpdateModuleData::HijackerUpdateModuleData()
	: m_attachToBone(0)
	, m_parachuteName(0)
{
}

// ?friend_newModuleData@HijackerUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HijackerUpdate::friend_newModuleData(INI *ini)
{
	HijackerUpdateModuleData *data = new HijackerUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &HijackerUpdateFieldParse);
	return (ModuleData *)data;
}
