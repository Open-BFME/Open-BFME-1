// cl: /O2 /Ob1

// Retail keeps only the store of Snapshot's table (0x01073744): the derived
// and intermediate stores die against the inlined ~Snapshot.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class DockUpdateModuleData : public Snapshot
{
public:
	virtual void handle();

private:
	char m_pad[0x0C];
};

class SupplyCenterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	virtual ~SupplyCenterDockUpdateModuleData();

private:
	float m_valueMultiplier;
	int m_bonusScience;
	float m_bonusScienceMultiplier;
};

SupplyCenterDockUpdateModuleData::~SupplyCenterDockUpdateModuleData()
{
}

// The destructor's own vtable store is dead, so only this object keeps the
// vftable, and with it the scalar deleting destructor, in this TU.
void forceSupplyCenterDockUpdateModuleDataDeletingDestructor()
{
	SupplyCenterDockUpdateModuleData value;
}
