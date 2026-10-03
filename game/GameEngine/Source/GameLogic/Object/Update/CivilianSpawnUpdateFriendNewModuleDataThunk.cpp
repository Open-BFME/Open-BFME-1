// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CivilianSpawnUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CivilianSpawnUpdateModuleData
{
public:
	CivilianSpawnUpdateModuleData();
	virtual ~CivilianSpawnUpdateModuleData();

private:
	unsigned char m_pad[0x1c];
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

void j_0000b825();

class CivilianSpawnUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CivilianSpawnUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CivilianSpawnUpdate::friend_newModuleData(INI *ini)
{
	CivilianSpawnUpdateModuleData *data = new CivilianSpawnUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(j_0000b825));
	return (ModuleData *)data;
}

// Retail's factory at CivilianSpawnUpdate pushes 0x0040B825 here (see
// ?friend_newModuleData@CivilianSpawnUpdate@@SAPAVModuleData@@PAVINI@@@Z), and the only
// symbol the build defines at that address is the five-byte ILT thunk
// ?j_0000b825@@YAXXZ (game/gen_small/gthunks_011.cpp), a `jmp` to 0x0028A2D0, the
// module-data class's static field-parse builder.  The old
// `extern "C" CivilianSpawnUpdateFieldParse` was invented in this TU and nothing
// defines it; the thunk is retail's real spelling of this operand.
