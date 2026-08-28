// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DLaserDraw::friend_newModuleInstance factory, retail 0x006BF150,
// converted out of a machine byte dump.
//
// Same three lines as every other module factory, so the code cannot name it.
// The draw-module registration block does: it builds the AsciiString "W3DLaserDraw"
// and pushes this factory's address as the argument beside it.
//
// Retail allocates 0x5C bytes, which is sizeof(W3DLaserDraw), and calls the
// constructor through link thunk 0x0000E61A.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DLaserDraw.h
class W3DLaserDraw
{
public:
	W3DLaserDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x5C];
};

// ?friend_newModuleInstance@W3DLaserDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DLaserDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DLaserDraw(thing, data);
}
