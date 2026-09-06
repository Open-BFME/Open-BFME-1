// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
// ~PhysicsBehavior, lifted from its MASM dump to C++.
//
// Sibling of PhysicsBehaviorCtorModuleFactoryBody.cpp: same UpdateModule chain
// (PB_DeepBase vptr at +0x00, PB_Iface1 at +0x0c, PB_Iface2 at +0x10) and the
// same 0x60-byte compact BFME layout. The only live member at teardown is the
// std::vector<Coord3D> m_overlapForces at +0x20 (start/finish/end_of_storage);
// its 12-byte element stride (imul 0x2AAAAAAB, *12) and the inline vs.
// operator-delete threshold at 0x80 bytes match retail exactly. Everything
// past the vector is scalar/POD and needs no destructor work, so the tail
// re-installs the UpdateModule vtable set and chains to the shared
// PB_DeepBase dtor (pinned ??1PB_DeepBase@@UAE@XZ @ 0x00047C53).

#include <vector>

class Thing;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	float x;
	float y;
	float z;
};

class ModuleData;

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public PB_DeepBase, public PB_Iface1
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public PB_Iface2
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PhysicsUpdate.h
class PhysicsBehavior : public UpdateModule
{
public:
	virtual ~PhysicsBehavior();

private:
	std::vector<Coord3D> m_overlapForces;			///< retail this+0x20
	unsigned char m_unreconstructed_2c[0x34];
};

// ??1PhysicsBehavior@@UAE@XZ
PhysicsBehavior::~PhysicsBehavior()
{
}
