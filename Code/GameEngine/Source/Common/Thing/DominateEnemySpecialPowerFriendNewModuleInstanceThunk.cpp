// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DominateEnemySpecialPower::friend_newModuleInstance factory, retail 0x00122140,
// converted out of Code/gen_asm/d_0010e580.asm.
//
// One of thirty-one factories that are the same three lines and differ only in
// the size operator new is handed and the constructor called. zh_sweep matches
// any of them against any Zero Hour factory at 96-99%, so the code cannot name
// them; the ModuleFactory registration block can. It builds the AsciiString
// "DominateEnemySpecialPower" and pushes this factory's address as the argument beside
// it, the way addModule takes them.
//
// Retail allocates 0xE8 bytes here, which is sizeof(DominateEnemySpecialPower), and calls
// the constructor through link thunk 0x00003D3C.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DominateEnemySpecialPower
{
public:
	DominateEnemySpecialPower(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xE8];
};

// ?friend_newModuleInstance@DominateEnemySpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DominateEnemySpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new DominateEnemySpecialPower(thing, data);
}
