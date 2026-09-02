// ?setWake@Gen00256CD0@@QAEXI@Z
// partial score=0.98 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: wrapper that converts an absolute wake frame into setWakeFrame.
// object at +8; destroyed bit is byte +0x90 bit 0; TheGameLogic frame at +0x3C.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class GameLogic
{
public:
	unsigned char m_unmodelled_00[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	unsigned char m_unmodelled_00[0x90];
	unsigned char m_status0;
};

class Gen00256CD0
{
public:
	void setWake(UnsignedInt frame);

private:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
};

// ?setWake@Gen00256CD0@@QAEXI@Z
void Gen00256CD0::setWake(UnsignedInt frame)
{
	Object *obj = m_object;
	if (obj->m_status0 & 1)
		return;
	if (frame && frame != (UnsignedInt)UPDATE_SLEEP_FOREVER)
		setWakeFrame(obj, (UpdateSleepTime)(frame - TheGameLogic->m_frame));
	else
	{
		frame = (UnsignedInt)UPDATE_SLEEP_FOREVER;
		setWakeFrame(obj, (UpdateSleepTime)frame);
	}
}
