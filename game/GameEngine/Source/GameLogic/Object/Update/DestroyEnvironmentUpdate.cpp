// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DestroyEnvironmentUpdateModuleData default ctor.

class DestroyEnvironmentUpdateModuleData
{
public:
	DestroyEnvironmentUpdateModuleData();
	virtual ~DestroyEnvironmentUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned int m_0c;
};

// ??0DestroyEnvironmentUpdateModuleData@@QAE@XZ
DestroyEnvironmentUpdateModuleData::DestroyEnvironmentUpdateModuleData()
{
	m_08 = 0;
	m_0c = 100;
}