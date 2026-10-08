// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep

class Thing;
class ModuleData;
class Object;

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_f00[0x3c];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};
class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoDepositUpdate.h
class AutoDepositUpdateModuleData
{
public:
	unsigned char m_f00[8];
	unsigned int m_depositFrame;
};

class AutoDepositUpdate : public UpdateModule
{
public:
	AutoDepositUpdate(Thing *thing, const ModuleData *moduleData);
	const AutoDepositUpdateModuleData *getAutoDepositUpdateModuleData() const { return (const AutoDepositUpdateModuleData *)m_moduleData; }
private:
	unsigned int m_depositOnFrame;
	bool m_awardInitialCaptureBonus;
	bool m_initialized;
};

AutoDepositUpdate::AutoDepositUpdate(Thing *thing, const ModuleData *moduleData) : UpdateModule(thing, moduleData), m_awardInitialCaptureBonus(false), m_initialized(false)
{
	m_depositOnFrame = TheGameLogic->getFrame() + getAutoDepositUpdateModuleData()->m_depositFrame;
}
