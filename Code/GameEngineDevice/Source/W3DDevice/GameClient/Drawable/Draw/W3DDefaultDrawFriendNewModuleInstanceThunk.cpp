// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DDefaultDraw::friend_newModuleInstance factory, retail 0x006BEFC0,
// converted out of a machine byte dump and repointed off 0x0011E2D0.
//
// The registration block pairs the AsciiString "W3DDefaultDraw" with this address. The
// allocation size settles it against the row the name sat on: this body hands
// operator new 0x14 where 0x0011E2D0 hands it 0x18, and retail cannot
// have folded two bodies that differ in the size they allocate.
//
// The constructor is reached through link thunk 0x00009FED, landing on
// 0x007513C0.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DDefaultDraw.h
class W3DDefaultDraw
{
public:
	W3DDefaultDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x14];
};

// ?friend_newModuleInstance@W3DDefaultDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DDefaultDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DDefaultDraw(thing, data);
}
