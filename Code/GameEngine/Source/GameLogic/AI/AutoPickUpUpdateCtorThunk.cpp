// cl: /DNDEBUG /MD /EHsc
// AutoPickUpUpdate constructor, retail RVA 0x00281AB0 (175 bytes).
//
// The retail body calls the shared ObjectModule constructor through ILT
// 0x000170E4, inlines UpdateModule's three scalar initialisers, installs the
// AutoPickUpUpdate interface, and then installs the four most-derived vtables.
// The sole named caller is friend_newModuleInstance at 0x00119AB0.

class ModuleData;

class Thing;

// The retail AutoPickUp module-data field table at 0x00CBB9D0 names the
// scalar at +0x08 "ScanDelayTime".  The module-data constructor independently
// writes its first post-base scalar at that offset; retain the table RVA and
// offset in the local name until the complete class header is recovered.
struct AutoPickUpUpdateModuleData
{
	unsigned char m_moduleDataBase00[8];
	unsigned int m_scanDelayTimeField_00CBB9D0_08;
};

extern int GetGameLogicRandomValue(int, int, const char *, int);

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Thing *m_object;
};

class PB_Iface1
{
public:
	virtual void slot();
};

class PB_Iface2
{
public:
	virtual void slot();
};

class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class AutoPickUpUpdateIface
{
public:
	virtual void slot();
};

class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateIface
{
public:
	AutoPickUpUpdate(Thing *, const ModuleData *);

private:
	int m_updateDelay;
	bool m_alwaysHeal;
	bool m_neverHeal;
};

// ??0AutoPickUpUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
AutoPickUpUpdate::AutoPickUpUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_updateDelay(0),
	  m_alwaysHeal(false),
	  m_neverHeal(false)
{
	const AutoPickUpUpdateModuleData *data =
		reinterpret_cast<const AutoPickUpUpdateModuleData *>(m_moduleData);
	m_updateDelay += GetGameLogicRandomValue(
		0, data->m_scanDelayTimeField_00CBB9D0_08,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AutoPickUpUpdate.cpp",
		0x86);
}

typedef char AutoPickUpObjectSizeCheck[sizeof(AutoPickUpUpdate) == 0x2c ? 1 : -1];
typedef char AutoPickUpModuleBaseSizeCheck[sizeof(PB_DeepBase) == 0x0c ? 1 : -1];
