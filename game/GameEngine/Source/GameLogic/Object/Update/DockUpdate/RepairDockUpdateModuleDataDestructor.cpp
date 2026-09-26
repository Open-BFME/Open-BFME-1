// cl: /O2 /Ob0

class DockUpdateModuleData
{
public:
	virtual void handle();

private:
	char m_pad[0x0C];
};

class RepairDockUpdateModuleData : public DockUpdateModuleData
{
public:
	virtual ~RepairDockUpdateModuleData();

private:
	float m_framesForFullHeal;
};

RepairDockUpdateModuleData::~RepairDockUpdateModuleData()
{
}
