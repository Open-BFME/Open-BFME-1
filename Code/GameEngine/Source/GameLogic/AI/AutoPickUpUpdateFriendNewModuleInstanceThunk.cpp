// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class Module
{
public:
	virtual ~Module();
};

class AutoPickUpUpdate : public Module
{
public:
	AutoPickUpUpdate(Thing *, const ModuleData *);
	virtual ~AutoPickUpUpdate();

    static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_data[0x28];
};

// ?friend_newModuleInstance@AutoPickUpUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AutoPickUpUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
    return new AutoPickUpUpdate(thing, moduleData);
}
