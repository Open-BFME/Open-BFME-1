// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HorseHordeContain module ctor.
// Out-of-line base MI, then eleven most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34/+0xD4/+0xE4.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
virtual void behaviorModuleAnchor();

private:
unsigned char m_data[8];
};

class HorseHordeContainIface1
{
public:
virtual void horseHordeIface1Anchor();
};

class HorseHordeContainIface2
{
public:
virtual void horseHordeIface2Anchor();

private:
unsigned char m_pad[0xC];
};

class HorseHordeContainIface3
{
public:
virtual void horseHordeIface3Anchor();
};

class HorseHordeContainIface4
{
public:
virtual void horseHordeIface4Anchor();
};

class HorseHordeContainIface5
{
public:
virtual void horseHordeIface5Anchor();
};

class HorseHordeContainIface6
{
public:
virtual void horseHordeIface6Anchor();
};

class HorseHordeContainIface7
{
public:
virtual void horseHordeIface7Anchor();
};

class HorseHordeContainIface8
{
public:
virtual void horseHordeIface8Anchor();

private:
// span from after +0x34 vtbl to +0xD4
unsigned char m_pad[0x9C];
};

class HorseHordeContainIface9
{
public:
virtual void horseHordeIface9Anchor();

private:
unsigned char m_pad[0xC];
};

class HorseHordeContainIface10
{
public:
virtual void horseHordeIface10Anchor();
};

class HorseHordeContainBase : public BehaviorModule,
public HorseHordeContainIface1,
public HorseHordeContainIface2,
public HorseHordeContainIface3,
public HorseHordeContainIface4,
public HorseHordeContainIface5,
public HorseHordeContainIface6,
public HorseHordeContainIface7,
public HorseHordeContainIface8,
public HorseHordeContainIface9,
public HorseHordeContainIface10
{
public:
HorseHordeContainBase(Thing *thing, const ModuleData *moduleData);
};

class HorseHordeContain : public HorseHordeContainBase
{
public:
HorseHordeContain(Thing *thing, const ModuleData *moduleData);
};

// ??0HorseHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z
HorseHordeContain::HorseHordeContain(Thing *thing, const ModuleData *moduleData)
: HorseHordeContainBase(thing, moduleData)
{
}
