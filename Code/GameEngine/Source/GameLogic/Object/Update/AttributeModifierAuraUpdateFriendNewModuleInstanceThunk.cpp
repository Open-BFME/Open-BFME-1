// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AttributeModifierAuraUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AttributeModifierAuraUpdate
{
public:
	AttributeModifierAuraUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@AttributeModifierAuraUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AttributeModifierAuraUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new AttributeModifierAuraUpdate(thing, data);
}
