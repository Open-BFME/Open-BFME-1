// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SlaveWatcherBehaviorModuleData default ctor.

class SlaveWatcherBehaviorModuleData
{
public:
	SlaveWatcherBehaviorModuleData();
	virtual ~SlaveWatcherBehaviorModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned int m_0c;
};

// ??0SlaveWatcherBehaviorModuleData@@QAE@XZ
SlaveWatcherBehaviorModuleData::SlaveWatcherBehaviorModuleData()
{
	m_08 = 0;
	m_0c = 0;
}