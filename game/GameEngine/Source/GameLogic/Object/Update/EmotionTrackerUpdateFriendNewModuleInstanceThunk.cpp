// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EmotionTrackerUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class EmotionTrackerUpdate
{
public:
	EmotionTrackerUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xb8];
};

// ?friend_newModuleInstance@EmotionTrackerUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *EmotionTrackerUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new EmotionTrackerUpdate(thing, data);
}
