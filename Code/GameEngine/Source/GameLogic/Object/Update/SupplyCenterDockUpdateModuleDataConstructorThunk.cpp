// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SupplyCenterDockUpdateModuleData ctor.
// Base size 0x10; then float@10, int@14=-1, float@18.

class DockUpdateModuleData
{
public:
	DockUpdateModuleData();
	virtual ~DockUpdateModuleData();

private:
	unsigned char m_pad[0x0c];
};

class SupplyCenterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	SupplyCenterDockUpdateModuleData();
	virtual ~SupplyCenterDockUpdateModuleData();

private:
	float m_10;
	int m_14;
	float m_18;
};

// ??0SupplyCenterDockUpdateModuleData@@QAE@XZ
SupplyCenterDockUpdateModuleData::SupplyCenterDockUpdateModuleData()
{
	m_10 = 1.0f;
	m_18 = 1.0f;
	m_14 = -1;
}
