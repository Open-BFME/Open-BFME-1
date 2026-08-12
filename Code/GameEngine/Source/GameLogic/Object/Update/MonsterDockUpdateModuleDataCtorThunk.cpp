// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of MonsterDockUpdateModuleData.

class DockUpdateModuleData
{
public:
	DockUpdateModuleData();
	virtual ~DockUpdateModuleData() {}

private:
	unsigned char m_pad[0x0c];
};

class MonsterDockDataMember
{
public:
	MonsterDockDataMember();

private:
	unsigned int m_value;
};

class MonsterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	MonsterDockUpdateModuleData();
	virtual ~MonsterDockUpdateModuleData();

private:
	MonsterDockDataMember m_member;
	unsigned int m_initialDockCount;
};

// ??0MonsterDockUpdateModuleData@@QAE@XZ
MonsterDockUpdateModuleData::MonsterDockUpdateModuleData() :
	DockUpdateModuleData(),
	m_member(),
	m_initialDockCount(0)
{
}
