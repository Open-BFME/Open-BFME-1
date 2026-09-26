// cl: /DNDEBUG /MD /GX- /O2 /Ob2
//
// +0x08 is named from retail's own INI field table at 0x00C8D4B0: it holds one
// key, SpawnPointBoneName, at that offset, and upstream's parse table for this
// class writes that key to m_spawnPointBoneNameData. One key, one member, so
// there is nothing to disambiguate.
//
// It stays an int. Upstream's member is an AsciiString, which is one pointer
// word here, and the constructor stores the null that AsciiString's own
// constructor would -- declaring the real type would add a constructor and a
// destructor call this body does not make.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h
class SpawnPointProductionExitUpdateModuleData
{
public:
	SpawnPointProductionExitUpdateModuleData();
	virtual ~SpawnPointProductionExitUpdateModuleData();

private:
	int m_tag;
	int m_spawnPointBoneNameData;
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

extern "C" void __cdecl SpawnPointProductionExitUpdateFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h
class SpawnPointProductionExitUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ??0SpawnPointProductionExitUpdateModuleData@@QAE@XZ
SpawnPointProductionExitUpdateModuleData::SpawnPointProductionExitUpdateModuleData()
{
	m_spawnPointBoneNameData = 0;
}

// ?friend_newModuleData@SpawnPointProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpawnPointProductionExitUpdate::friend_newModuleData(INI *ini)
{
	SpawnPointProductionExitUpdateModuleData *data = new SpawnPointProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &SpawnPointProductionExitUpdateFieldParse);
	return (ModuleData *)data;
}