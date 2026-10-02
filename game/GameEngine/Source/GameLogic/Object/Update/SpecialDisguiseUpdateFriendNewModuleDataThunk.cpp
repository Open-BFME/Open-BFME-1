// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialDisguiseUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpecialDisguiseUpdateModuleData
{
public:
	SpecialDisguiseUpdateModuleData();
	virtual ~SpecialDisguiseUpdateModuleData();

private:
	unsigned char m_pad[0x268];
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

// Retail's factory at SpecialDisguiseUpdate pushes 0x0044331A here (see
// ?friend_newModuleData@SpecialDisguiseUpdate@@SAPAVModuleData@@PAVINI@@@Z), and the only symbol the
// build defines at that address is the five-byte ILT thunk ?j_0004331a@@YAXXZ, which
// game/gen_small/gthunks_075.cpp implements as a `jmp` to the module-data
// class's static field-parse builder.  The old
// `extern "C" SpecialDisguiseUpdateFieldParse` was invented in this TU and nothing
// defines it; the thunk is retail's real spelling of this operand.
void j_0004331a();

class SpecialDisguiseUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SpecialDisguiseUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialDisguiseUpdate::friend_newModuleData(INI *ini)
{
	SpecialDisguiseUpdateModuleData *data = new SpecialDisguiseUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(j_0004331a));
	return (ModuleData *)data;
}
