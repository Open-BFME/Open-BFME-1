// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DTruckDraw::friend_newModuleInstance factory, retail 0x006BF470,
// converted out of a machine byte dump.
//
// Same three lines as every other module factory, so the code cannot name it.
// The draw-module registration block does: it builds the AsciiString "W3DTruckDraw"
// and pushes this factory's address as the argument beside it.
//
// Retail allocates 0x3EC bytes, which is sizeof(W3DTruckDraw), and calls the
// constructor through link thunk 0x00036AED.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTruckDraw.h
class W3DTruckDraw
{
public:
	W3DTruckDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x3EC];
};

// ?friend_newModuleInstance@W3DTruckDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTruckDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DTruckDraw(thing, data);
}
