// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BFME's replacement-state handoff for TemporarilyDefectUpdate.
// Retail 0x002B0EA0, called through ILT 0x000411C3.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

class Thing;
class ModuleData;
class Team;

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void setTeam(Team *team) = 0;

	UnsignedInt getID() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x74);
	}

	Team *getTeam() const
	{
		return *(Team *const *)((const char *)this + 0x23c);
	}

};

class PB_DeepBase
{
public:
	virtual void deepBaseAnchor() = 0;

protected:
	Thing *m_thing;
	Object *m_object;
};

class PB_Iface1
{
public:
	virtual void iface1Anchor() = 0;
};

class PB_Iface2
{
public:
	virtual void iface2Anchor() = 0;
};

class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
protected:
	UnsignedInt m_f14;
	int m_f18;
	int m_f1c;

	void setWakeFrame(Object *object, UpdateSleepTime when);
};

class TemporarilyDefectUpdate : public UpdateModule
{
public:
	void bfmeTransferDefection(Object *source, UnsignedInt endFrame);

private:
	UnsignedInt m_endFrame;
	UnsignedInt m_startFrame;
	UnsignedInt m_defectorID;
	unsigned char m_fxFired;
};

class GameLogic
{
public:
	UnsignedInt m_beforeFrame[0x3c / sizeof(UnsignedInt)];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// ?bfmeTransferDefection@TemporarilyDefectUpdate@@QAEXPAVObject@@I@Z
void TemporarilyDefectUpdate::bfmeTransferDefection(Object *source, UnsignedInt endFrame)
{
	if (m_endFrame != 0 || source == 0)
		return;

	if (m_object == 0 || (*(const UnsignedInt *)((const char *)m_object + 0x94) & 0x20000000) != 0)
		return;

	m_defectorID = source->getID();
	Thing *thing = m_thing;
	m_object->setTeam(source->getTeam());

	UnsignedInt frame = TheGameLogic->m_frame;
	m_startFrame = frame;
	if (endFrame > 0)
		m_endFrame = endFrame;
	if (endFrame <= 0)
		m_endFrame = *(const UnsignedInt *)((const char *)thing + 8) + frame;

	setWakeFrame(m_object, (UpdateSleepTime)10);
	m_fxFired = 0;
}
