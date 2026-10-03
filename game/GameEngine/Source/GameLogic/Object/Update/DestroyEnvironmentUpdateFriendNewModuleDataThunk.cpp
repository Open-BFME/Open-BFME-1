// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DestroyEnvironmentUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DestroyEnvironmentUpdateModuleData
{
public:
	DestroyEnvironmentUpdateModuleData();
	virtual ~DestroyEnvironmentUpdateModuleData();

private:
	unsigned char m_pad[0xc];
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

void j_00014b87();

class DestroyEnvironmentUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DestroyEnvironmentUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DestroyEnvironmentUpdate::friend_newModuleData(INI *ini)
{
	DestroyEnvironmentUpdateModuleData *data = new DestroyEnvironmentUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(j_00014b87));
	return (ModuleData *)data;
}

// Retail's factory at DestroyEnvironmentUpdate pushes 0x00414B87 here (see
// ?friend_newModuleData@DestroyEnvironmentUpdate@@SAPAVModuleData@@PAVINI@@@Z), and the only
// symbol the build defines at that address is the five-byte ILT thunk
// ?j_00014b87@@YAXXZ (game/gen_small/gthunks_022.cpp), a `jmp` to 0x0028CD50, the
// module-data class's static field-parse builder.  The old
// `extern "C" DestroyEnvironmentUpdateFieldParse` was invented in this TU and nothing
// defines it; the thunk is retail's real spelling of this operand.
