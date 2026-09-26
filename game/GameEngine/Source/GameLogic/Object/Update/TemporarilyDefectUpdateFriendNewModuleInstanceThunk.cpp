// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TemporarilyDefectUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class TemporarilyDefectUpdate
{
public:
	TemporarilyDefectUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x30];
};

// ?friend_newModuleInstance@TemporarilyDefectUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TemporarilyDefectUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new TemporarilyDefectUpdate(thing, data);
}
