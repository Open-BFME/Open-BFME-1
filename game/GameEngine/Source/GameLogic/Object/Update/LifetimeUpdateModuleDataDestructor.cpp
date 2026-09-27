// cl: /O2 /Ob1

// Retail keeps only the store of Snapshot's table (0x01073744): the derived
// and intermediate stores die against the inlined ~Snapshot.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class ModuleData : public Snapshot
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned char m_storage[0x0C];
};

class LifetimeUpdateModuleData : public ModuleData
{
public:
	virtual ~LifetimeUpdateModuleData();

private:
	unsigned int m_minLifetime;
	unsigned int m_maxLifetime;
	bool m_waitForWakeup;
	bool m_scoreKill;
	unsigned int m_deadLifetime;
};

LifetimeUpdateModuleData::~LifetimeUpdateModuleData()
{
}

// The destructor's own vtable store is dead, so only this object keeps the
// vftable, and with it the scalar deleting destructor, in this TU.
void forceLifetimeUpdateModuleDataDeletingDestructor()
{
	LifetimeUpdateModuleData value;
}
