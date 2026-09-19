// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Open-BFME5: SlaughterHordeContain constructor with its retail MI layout.

class Thing;
class ModuleData;

extern "C" char SlaughterHordeContain_vtbl0;
extern "C" char SlaughterHordeContain_vtbl0C;
extern "C" char SlaughterHordeContain_vtbl10;
extern "C" char SlaughterHordeContain_vtbl20;
extern "C" char SlaughterHordeContain_vtbl24;
extern "C" char SlaughterHordeContain_vtbl28;
extern "C" char SlaughterHordeContain_vtbl2C;
extern "C" char SlaughterHordeContain_vtbl30;
extern "C" char SlaughterHordeContain_vtbl34;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class SlaughterHordeContainIface1 { public: virtual void slot(); };
class SlaughterHordeContainIface2
{
public:
	virtual void slot();
private:
	unsigned char m_pad[0x0c];
};
class SlaughterHordeContainIface3 { public: virtual void slot(); };
class SlaughterHordeContainIface4 { public: virtual void slot(); };
class SlaughterHordeContainIface5 { public: virtual void slot(); };
class SlaughterHordeContainIface6 { public: virtual void slot(); };
class SlaughterHordeContainIface7 { public: virtual void slot(); };
class SlaughterHordeContainIface8 { public: virtual void slot(); };

class SlaughterHordeContainBase : public BehaviorModule,
	public SlaughterHordeContainIface1,
	public SlaughterHordeContainIface2,
	public SlaughterHordeContainIface3,
	public SlaughterHordeContainIface4,
	public SlaughterHordeContainIface5,
	public SlaughterHordeContainIface6,
	public SlaughterHordeContainIface7,
	public SlaughterHordeContainIface8
{
public:
	SlaughterHordeContainBase(Thing *, const ModuleData *);

private:
	unsigned char m_data[0x984];
};

class __declspec(novtable) SlaughterHordeContain : public SlaughterHordeContainBase
{
public:
	SlaughterHordeContain(Thing *, const ModuleData *);

private:
	volatile unsigned int m_f9BC;
	volatile unsigned int m_f9C0;
};

// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z
SlaughterHordeContain::SlaughterHordeContain(Thing *thing, const ModuleData *moduleData)
	: SlaughterHordeContainBase(thing, moduleData)
{
	m_f9BC = 0;
	*(void *volatile *)this = &SlaughterHordeContain_vtbl0;
	*(void *volatile *)((char *)this + 0x0c) = &SlaughterHordeContain_vtbl0C;
	*(void *volatile *)((char *)this + 0x10) = &SlaughterHordeContain_vtbl10;
	*(void *volatile *)((char *)this + 0x20) = &SlaughterHordeContain_vtbl20;
	*(void *volatile *)((char *)this + 0x24) = &SlaughterHordeContain_vtbl24;
	*(void *volatile *)((char *)this + 0x28) = &SlaughterHordeContain_vtbl28;
	*(void *volatile *)((char *)this + 0x2c) = &SlaughterHordeContain_vtbl2C;
	*(void *volatile *)((char *)this + 0x30) = &SlaughterHordeContain_vtbl30;
	*(void *volatile *)((char *)this + 0x34) = &SlaughterHordeContain_vtbl34;
	m_f9C0 = 0;
}
