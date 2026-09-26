// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HijackerUpdate.h
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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl HijackerUpdateFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HijackerUpdate.h
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
		ini->initFromINIMultiProc(data, &HijackerUpdateFieldParse);
	return (ModuleData *)data;
}
