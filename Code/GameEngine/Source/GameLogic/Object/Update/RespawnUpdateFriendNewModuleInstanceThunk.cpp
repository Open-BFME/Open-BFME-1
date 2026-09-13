// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RespawnUpdate::friend_newModuleInstance factory, retail 0x0011CC00,
// converted out of Code/gen_asm/d_0010e580.asm.
//
// One of thirty-one factories that are the same three lines and differ only in
// the size operator new is handed and the constructor called. zh_sweep matches
// any of them against any Zero Hour factory at 96-99%, so the code cannot name
// them; the ModuleFactory registration block can. It builds the AsciiString
// "RespawnUpdate" and pushes this factory's address as the argument beside
// it, the way addModule takes them.
//
// Retail allocates 0x44 bytes here, which is sizeof(RespawnUpdate), and calls
// the constructor through link thunk 0x0000FA38.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RespawnUpdate
{
public:
	RespawnUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x44];
};

// ?friend_newModuleInstance@RespawnUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RespawnUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new RespawnUpdate(thing, data);
}
