// cl: /O2 /Ob0

class DockUpdateModuleData
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
