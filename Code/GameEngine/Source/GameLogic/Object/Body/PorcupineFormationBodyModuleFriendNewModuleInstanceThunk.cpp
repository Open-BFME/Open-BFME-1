// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PorcupineFormationBodyModule::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PorcupineFormationBodyModule
{
public:
	PorcupineFormationBodyModule(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xe0];
};

// ?friend_newModuleInstance@PorcupineFormationBodyModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PorcupineFormationBodyModule::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new PorcupineFormationBodyModule(thing, data);
}
