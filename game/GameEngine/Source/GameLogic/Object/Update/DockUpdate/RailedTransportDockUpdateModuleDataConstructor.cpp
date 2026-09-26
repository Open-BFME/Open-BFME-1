// cl: /O2 /Ob0

class DockUpdateModuleData
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
