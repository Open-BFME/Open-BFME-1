// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GrantUpgradeCreate::friend_newModuleInstance factory, retail 0x0011E4E0,
// converted out of Code/gen_asm/d_0010e580.asm.
//
// One of thirty-one factories that are the same three lines and differ only in
// the size operator new is handed and the constructor called. zh_sweep matches
// any of them against any Zero Hour factory at 96-99%, so the code cannot name
// them; the ModuleFactory registration block can. It builds the AsciiString
// "GrantUpgradeCreate" and pushes this factory's address as the argument beside
// it, the way addModule takes them.
//
// Retail allocates 0x18 bytes here, which is sizeof(GrantUpgradeCreate), and calls
// the constructor through link thunk 0x0001D3AE.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeCreate.h
class GrantUpgradeCreate
{
public:
	GrantUpgradeCreate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x18];
};

// ?friend_newModuleInstance@GrantUpgradeCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GrantUpgradeCreate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new GrantUpgradeCreate(thing, data);
}
