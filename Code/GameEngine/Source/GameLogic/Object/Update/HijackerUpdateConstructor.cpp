// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0HijackerUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdate.cpp

// Retail's incremental-link thunk at 0x0003A382 forwards to this 95-byte
// constructor body at 0x00295B20.  The focused hierarchy follows the
// authoritative HijackerUpdate header: UpdateModule's three subobjects and
// fields at +0x14/+0x18/+0x1c, then the target ID, Coord3D, and three flags.
// Keeping the base constructor external preserves its proven retail pin;
// Coord3D is a real member so zero() remains the compiler's construction
// barrier between the flag stores and the final vtable stores.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	Coord3D() {}
	void zero() { m_x = 0.0f; m_y = 0.0f; m_z = 0.0f; }
private:
	float m_x;
	float m_y;
	float m_z;
};

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();
protected:
	void *m_f04;
	void *m_f08;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HijackerUpdate.h
class HijackerUpdate : public UpdateModule
{
public:
	HijackerUpdate(Thing *, const ModuleData *);

private:
	unsigned int m_targetID;
	Coord3D m_ejectPos;
	unsigned char m_update;
	unsigned char m_isInVehicle;
	unsigned char m_wasTargetAirborne;
};

// ??0HijackerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
HijackerUpdate::HijackerUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_targetID = 0;
	m_update = 0;
	m_isInVehicle = 0;
	m_wasTargetAirborne = 0;
	m_ejectPos.zero();
}
