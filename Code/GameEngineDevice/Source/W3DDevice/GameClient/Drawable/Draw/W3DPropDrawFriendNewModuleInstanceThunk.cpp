// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DPropDraw::friend_newModuleInstance factory, retail 0x006BF8B0,
// converted out of a machine byte dump.
//
// Same three lines as every other module factory, so the code cannot name it.
// The draw-module registration block does: it builds the AsciiString "W3DPropDraw"
// and pushes this factory's address as the argument beside it.
//
// Retail allocates 0x10 bytes, which is sizeof(W3DPropDraw), and calls the
// constructor through link thunk 0x00039770.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DPropDraw.h
class W3DPropDraw
{
public:
	W3DPropDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x10];
};

// ?friend_newModuleInstance@W3DPropDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DPropDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DPropDraw(thing, data);
}
