// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PassiveAreaEffectBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PassiveAreaEffectBehavior
{
public:
	PassiveAreaEffectBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@PassiveAreaEffectBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PassiveAreaEffectBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new PassiveAreaEffectBehavior(thing, data);
}
