// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BeaconClientUpdate::friend_newModuleInstance factory, retail 0x00121B70,
// converted out of a machine byte dump and repointed off 0x0011E2D0.
//
// The registration block pairs the AsciiString "BeaconClientUpdate" with this address, and
// the allocation sizes settle it: this body hands operator new 0x14, while
// 0x0011E2D0 -- where the name had been sitting alongside two other modules'
// -- hands it 0x18 and calls a different constructor. Retail cannot have folded
// bodies that differ in both, since those are the bytes identical-code folding
// compares. 0x0011E2D0 is what the same block registers as LockWeaponCreate.
//
// The constructor is reached through link thunk 0x00046B1E, which lands on
// 0x006030C0.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Module/BeaconClientUpdate.h
class BeaconClientUpdate
{
public:
	BeaconClientUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x14];
};

// ?friend_newModuleInstance@BeaconClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BeaconClientUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new BeaconClientUpdate(thing, data);
}
