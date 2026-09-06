// ?d_001fc6b0@@YAXXZ
// partial score=0.9 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	char *m_data;
};

enum ObjectID
{
	OBJECT_ID_UNUSED = 0
};

// BFME's AudioEventRTS object is 0x70 bytes at this call site.  This local
// view keeps the constructor and scalar destructor ABI while preserving that
// stack footprint.
class BfmeAudioEventRTS
{
public:
	BfmeAudioEventRTS(const AsciiString &name, ObjectID owner);
	~BfmeAudioEventRTS();
	unsigned char m_raw[0x70];
};

class ClientSubsystem
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual int addAudioEvent(const BfmeAudioEventRTS *event);
	virtual void slot18();
	virtual void removeAudioEvent(unsigned int handle);
};

extern ClientSubsystem *TheAudioClientUpdate;

struct GateOpenAndCloseBehaviorModuleDataView
{
	unsigned char m_pad00[0x1c];
	AsciiString m_openSound;
	unsigned char m_pad20[4];
	AsciiString m_closeSound;
};

struct GateOpenAndCloseBehaviorObjectView
{
	unsigned char m_pad00[0x74];
	ObjectID m_id;
};

enum GateOpenAndCloseState
{
	GATE_STATE_0 = 0,
	GATE_STATE_1 = 1,
	GATE_STATE_2 = 2,
	GATE_STATE_3 = 3
};

class GateOpenAndCloseBehavior
{
public:
	void playSound();

private:
	unsigned char m_pad00[8];
	GateOpenAndCloseBehaviorModuleDataView *m_moduleData;
	GateOpenAndCloseBehaviorObjectView *m_object;
	unsigned char m_pad10[0x18];
	GateOpenAndCloseState m_state;
	unsigned char m_pad2c[0x18];
	unsigned int m_audioHandle;
	bool m_audioPlaying;
};

// The helper is called after a gate state change to replace the event for the
// transition currently represented by m_state.
void GateOpenAndCloseBehavior::playSound()
{
	TheAudioClientUpdate->removeAudioEvent(m_audioHandle);
	GateOpenAndCloseBehaviorModuleDataView *data = m_moduleData;
	GateOpenAndCloseState state = m_state;
	GateOpenAndCloseBehaviorObjectView *object = m_object;
	switch (state)
	{
	case 0:
	case 1:
		if (data->m_openSound.m_data != 0)
		{
			BfmeAudioEventRTS event(data->m_openSound, object->m_id);
			TheAudioClientUpdate->addAudioEvent(&event);
		}
		break;
	case 2:
	case 3:
		if (data->m_closeSound.m_data != 0)
		{
			BfmeAudioEventRTS event(data->m_closeSound, object->m_id);
			TheAudioClientUpdate->addAudioEvent(&event);
		}
		break;
	}
	m_audioPlaying = true;
}
