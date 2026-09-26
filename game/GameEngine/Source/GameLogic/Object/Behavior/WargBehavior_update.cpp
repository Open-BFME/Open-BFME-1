// ?update@WargBehavior@@UAE?AW4UpdateSleepTime@@XZ
// The BFME WargBehavior update returns a short wake interval while the
// object's attack-status bit is set, and a longer interval otherwise.
// Keep the status copy explicit: this is the retail layout at Object+0x90.
// cl: /O2

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0
};

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
	Object *object = m_object;
	return object->m_status.wargSleep();
}
