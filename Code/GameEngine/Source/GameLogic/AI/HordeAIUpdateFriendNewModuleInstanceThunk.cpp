// cl: /DNDEBUG /MD /EHsc

class Module;
class Thing;
class ModuleData;

class HordeAIUpdate
{
public:
    HordeAIUpdate(Thing *, const ModuleData *);
    static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
    unsigned char storage[0x344];
};

// ?friend_newModuleInstance@HordeAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
    return reinterpret_cast<Module *>(new HordeAIUpdate(thing, moduleData));
}
