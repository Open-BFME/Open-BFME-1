// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AttributeModifierUpgrade::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AttributeModifierUpgrade
{
public:
	AttributeModifierUpgrade(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x1c];
};

// ?friend_newModuleInstance@AttributeModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AttributeModifierUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new AttributeModifierUpgrade(thing, data);
}
