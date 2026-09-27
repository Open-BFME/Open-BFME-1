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
	DockUpdateModuleData();
	virtual void handle();

private:
	char m_pad[0x0C];
};

class RailedTransportDockUpdateModuleData : public DockUpdateModuleData
{
	int m_pullInsideDurationInFrames;
	int m_pushOutsideDurationInFrames;

public:
	RailedTransportDockUpdateModuleData();
	virtual ~RailedTransportDockUpdateModuleData();
};

RailedTransportDockUpdateModuleData::RailedTransportDockUpdateModuleData()
{
	m_pullInsideDurationInFrames = 0;
	m_pushOutsideDurationInFrames = 0;
}

RailedTransportDockUpdateModuleData::~RailedTransportDockUpdateModuleData()
{
}
