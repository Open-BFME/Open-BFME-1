// ?update@WargBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.96 date=2026-09-10
// cl: /O2

enum UpdateSleepTime { UPDATE_SLEEP_INVALID = 0 };

struct ObjectStatusBits
{
	unsigned int m_words[3];

	UpdateSleepTime wargSleep() const
	{
		ObjectStatusBits status = *this;
		return (UpdateSleepTime)((status.m_words[1] & 0x40) ? 30 : 20);
	}
};

struct Object
{
	unsigned char m_pad[0x90];
	ObjectStatusBits m_status;
};

class WargBehavior
{
public:
	virtual ~WargBehavior();
	virtual UpdateSleepTime update();

private:
	unsigned int m_moduleData;
	Object *m_object;
};

UpdateSleepTime WargBehavior::update()
{
	return m_object->m_status.wargSleep();
}
