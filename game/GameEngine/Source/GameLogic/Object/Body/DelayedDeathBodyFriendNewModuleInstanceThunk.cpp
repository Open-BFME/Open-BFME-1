// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DelayedDeathBody::friend_newModuleInstance factory, retail
// 0x0011F830, converted out of game/gen_asm/d_0010e580.asm.
//
// zh_sweep matched the body 99% against nine different Zero Hour
// friend_newModuleInstance factories at once, because they are all the same
// three lines and differ only in the class size and the constructor they call.
// The name comes from the registration instead: ModuleFactory's init block at
// 0x0012FF59 builds the AsciiString "DelayedDeathBody" and immediately pushes
// this factory's link thunk 0x0004A0CA as the argument next to it, the way
// addModule takes them. FreeLifeBody is registered the same way twenty bytes
// further on, which is how the block reads.
//
// So the size operator new is handed, 0xE4, is sizeof(DelayedDeathBody), and
// the constructor behind link thunk 0x0002C818 -- body 0x00212810, still a byte
// dump -- is DelayedDeathBody's.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DelayedDeathBody
{
public:
	DelayedDeathBody(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xE4];
};

// ?friend_newModuleInstance@DelayedDeathBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DelayedDeathBody::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new DelayedDeathBody(thing, data);
}
