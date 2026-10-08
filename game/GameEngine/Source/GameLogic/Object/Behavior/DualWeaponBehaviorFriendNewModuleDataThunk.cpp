// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DualWeaponBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DualWeaponBehaviorModuleData
{
public:
	DualWeaponBehaviorModuleData();
	virtual ~DualWeaponBehaviorModuleData();

private:
	unsigned char m_pad[0x14];
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

extern "C" void __cdecl __identifier("DualWeaponBehaviorFieldParse")();

class DualWeaponBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DualWeaponBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DualWeaponBehavior::friend_newModuleData(INI *ini)
{
	DualWeaponBehaviorModuleData *data = new DualWeaponBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(__identifier("DualWeaponBehaviorFieldParse")));
	return (ModuleData *)data;
}

// Retail's factory at DualWeaponBehavior pushes 0x00425B4E here (see
// ?friend_newModuleData@DualWeaponBehavior@@SAPAVModuleData@@PAVINI@@@Z), and the only
// symbol the build defines at that address is the five-byte ILT thunk
// ?j_00025b4e@@YAXXZ (game/gen_small/gthunks_041.cpp), a `jmp` to 0x001F7E40, the
// module-data class's static field-parse builder.  The old
// `extern "C" DualWeaponBehaviorFieldParse` was invented in this TU and nothing
// defines it; the thunk is retail's real spelling of this operand.
