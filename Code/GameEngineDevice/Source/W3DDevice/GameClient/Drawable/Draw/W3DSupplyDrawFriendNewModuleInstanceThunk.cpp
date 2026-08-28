// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DSupplyDraw::friend_newModuleInstance factory, retail 0x006BF360,
// converted out of a machine byte dump and repointed off 0x0011E2D0.
//
// The registration block pairs the AsciiString "W3DSupplyDraw" with this address, and
// the allocation sizes settle it: this body hands operator new 0x284, while
// 0x0011E2D0 -- where the name had been sitting alongside two other modules'
// -- hands it 0x18 and calls a different constructor. Retail cannot have folded
// bodies that differ in both, since those are the bytes identical-code folding
// compares. 0x0011E2D0 is what the same block registers as LockWeaponCreate.
//
// The constructor is reached through link thunk 0x00042E9C, which lands on
// 0x0077DB70.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DSupplyDraw.h
class W3DSupplyDraw
{
public:
	W3DSupplyDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x284];
};

// ?friend_newModuleInstance@W3DSupplyDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DSupplyDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DSupplyDraw(thing, data);
}
