// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LargeGroupAudioUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class LargeGroupAudioUpdate
{
public:
	LargeGroupAudioUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x68];
};

// ?friend_newModuleInstance@LargeGroupAudioUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LargeGroupAudioUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new LargeGroupAudioUpdate(thing, data);
}
