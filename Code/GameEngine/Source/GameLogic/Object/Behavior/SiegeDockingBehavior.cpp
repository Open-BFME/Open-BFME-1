// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeDockingBehaviorModuleData default ctor.

class SiegeDockingBehaviorModuleData
{
public:
	SiegeDockingBehaviorModuleData();
	virtual ~SiegeDockingBehaviorModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
};

// ??0SiegeDockingBehaviorModuleData@@QAE@XZ
SiegeDockingBehaviorModuleData::SiegeDockingBehaviorModuleData()
{
	m_08 = 0;
}