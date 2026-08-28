// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DTankDraw::friend_newModuleInstance factory, retail 0x006BF580,
// converted out of a machine byte dump and repointed off 0x0011F690.
//
// The draw-module registration block pairs the AsciiString "W3DTankDraw" with
// this address, and the sizes agree with it: retail allocates 0x2F8 here, which
// sits with its siblings -- 0x27C for W3DQuadrupedDraw, 0x288 for
// W3DHordeModelDraw, 0x3EC for W3DTruckDraw -- and in the same run of addresses,
// 0x006BF040 through 0x006BFCF0. The row this name sat on, 0x0011F690, allocates
// 0xEC and lives among the small behaviour modules, so it is some other class's
// factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTankDraw.h
class W3DTankDraw
{
public:
	W3DTankDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2F8];
};

// ?friend_newModuleInstance@W3DTankDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTankDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DTankDraw(thing, data);
}
