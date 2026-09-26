// cl: /O2 /Ob0

class DockUpdateModuleData
{
public:
	virtual void handle();

private:
	char m_pad[0x0C];
};

class SupplyWarehouseDockUpdateModuleData : public DockUpdateModuleData
{
public:
	virtual ~SupplyWarehouseDockUpdateModuleData();

private:
	int m_startingBoxes;
	int m_deleteWhenEmpty;
};

SupplyWarehouseDockUpdateModuleData::~SupplyWarehouseDockUpdateModuleData()
{
}
