// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FreeLifeBody::friend_newModuleInstance factory, retail 0x0011F940,
// converted out of Code/gen_asm/d_0010e580.asm.
//
// One of thirty-one factories that are the same three lines and differ only in
// the size operator new is handed and the constructor called. zh_sweep matches
// any of them against any Zero Hour factory at 96-99%, so the code cannot name
// them; the ModuleFactory registration block can. It builds the AsciiString
// "FreeLifeBody" and pushes this factory's address as the argument beside
// it, the way addModule takes them.
//
// Retail allocates 0xF4 bytes here, which is sizeof(FreeLifeBody), and calls
// the constructor through link thunk 0x00013296.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FreeLifeBody
{
public:
	FreeLifeBody(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xF4];
};

// ?friend_newModuleInstance@FreeLifeBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FreeLifeBody::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new FreeLifeBody(thing, data);
}
