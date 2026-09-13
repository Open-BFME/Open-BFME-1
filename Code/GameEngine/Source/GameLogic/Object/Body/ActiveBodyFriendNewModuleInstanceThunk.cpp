// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ActiveBody::friend_newModuleInstance factory, retail 0x0011F3A0,
// converted out of Code/gen_asm/d_0010e580.asm.
//
// One of thirty-one factories that are the same three lines and differ only in
// the size operator new is handed and the constructor called. zh_sweep matches
// any of them against any Zero Hour factory at 96-99%, so the code cannot name
// them; the ModuleFactory registration block can. It builds the AsciiString
// "ActiveBody" and pushes this factory's address as the argument beside
// it, the way addModule takes them.
//
// Retail allocates 0xE0 bytes here, which is sizeof(ActiveBody), and calls
// the constructor through link thunk 0x00025509.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBody
{
public:
	ActiveBody(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xE0];
};

// ?friend_newModuleInstance@ActiveBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ActiveBody::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new ActiveBody(thing, data);
}
