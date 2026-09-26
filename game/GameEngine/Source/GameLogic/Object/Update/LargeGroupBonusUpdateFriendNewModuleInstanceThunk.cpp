// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LargeGroupBonusUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class LargeGroupBonusUpdate
{
public:
	LargeGroupBonusUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2c];
};

// ?friend_newModuleInstance@LargeGroupBonusUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LargeGroupBonusUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new LargeGroupBonusUpdate(thing, data);
}
