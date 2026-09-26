// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CivilianSpawnCollide::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CivilianSpawnCollide
{
public:
	CivilianSpawnCollide(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x14];
};

// ?friend_newModuleInstance@CivilianSpawnCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CivilianSpawnCollide::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new CivilianSpawnCollide(thing, data);
}
