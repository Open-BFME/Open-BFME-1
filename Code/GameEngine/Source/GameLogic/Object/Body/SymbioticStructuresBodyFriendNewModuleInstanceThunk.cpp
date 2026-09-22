// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SymbioticStructuresBody::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SymbioticStructuresBody
{
public:
	SymbioticStructuresBody(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xec];
};

// ?friend_newModuleInstance@SymbioticStructuresBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SymbioticStructuresBody::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SymbioticStructuresBody(thing, data);
}
