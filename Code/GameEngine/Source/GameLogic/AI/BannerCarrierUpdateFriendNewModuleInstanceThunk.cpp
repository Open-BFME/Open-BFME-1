// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class Module
{
public:
	virtual ~Module();
};

class BannerCarrierUpdate : public Module
{
public:
	BannerCarrierUpdate(Thing *, const ModuleData *);
	virtual ~BannerCarrierUpdate();

    static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_data[0x1c];
};

// ?friend_newModuleInstance@BannerCarrierUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BannerCarrierUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
    return new BannerCarrierUpdate(thing, moduleData);
}
