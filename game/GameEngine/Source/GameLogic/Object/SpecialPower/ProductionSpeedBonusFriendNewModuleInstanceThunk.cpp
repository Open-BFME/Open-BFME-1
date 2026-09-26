// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ProductionSpeedBonus::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ProductionSpeedBonus
{
public:
	ProductionSpeedBonus(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2c];
};

// ?friend_newModuleInstance@ProductionSpeedBonus@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ProductionSpeedBonus::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new ProductionSpeedBonus(thing, data);
}
