// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ToggleHiddenSpecialAbilityUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ToggleHiddenSpecialAbilityUpdateModuleData
{
public:
	ToggleHiddenSpecialAbilityUpdateModuleData();
	virtual ~ToggleHiddenSpecialAbilityUpdateModuleData();

private:
	unsigned char m_pad[0x250];
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

// Retail's factory at ToggleHiddenSpecialAbilityUpdate pushes 0x0040955C here
// (see ?friend_newModuleData@ToggleHiddenSpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z),
// and the only symbol the build defines at that address is the five-byte ILT
// thunk ?j_0000955c@@YAXXZ, which game/gen_small/gthunks_009.cpp implements as
// a `jmp` to the module-data class's static field-parse builder; the thunk is
// retail's real spelling of this operand.
void __cdecl j_0000955c(); // ?j_0000955c@@YAXXZ, ILT 0x0040955C

class ToggleHiddenSpecialAbilityUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ToggleHiddenSpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ToggleHiddenSpecialAbilityUpdate::friend_newModuleData(INI *ini)
{
	ToggleHiddenSpecialAbilityUpdateModuleData *data = new ToggleHiddenSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(j_0000955c));
	return (ModuleData *)data;
}
