// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x00221570. Flag-gated per-frame AudioEventRTS copy, object-id
// stamp, and TheAudio queue. Sibling of 0x00221630.

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &other);
	~AudioEventRTS();
	void setObjectID(unsigned id);

private:
	char m_body[0x70];
};

class AudioManager
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual unsigned addAudioEvent(const AudioEventRTS *event);
};

extern AudioManager *TheAudio;

class GameLogic
{
public:
	char m_pad[0x3C];
	int m_frame;
};

extern GameLogic *TheGameLogic;

class Gen_00221570
{
public:
	void bfmePlay();

	void *m_unused0;
	char *m_audioBase;
	char *m_object;
	char m_mid[0x7C - 0xC];
	int m_stamp;
	char m_mid2[0xB5 - 0x80];
	unsigned char m_flag;
};

// ?bfmePlay@Gen_00221570@@QAEXXZ
void Gen_00221570::bfmePlay()
{
	if (m_flag != 0)
	{
		int frame = TheGameLogic->m_frame;
		if (frame != m_stamp)
		{
			if (m_audioBase != 0)
			{
				AudioEventRTS event(*(const AudioEventRTS *)(m_audioBase + 0x34));
				char *obj = m_object;
				unsigned id = *(unsigned *)(obj + 0x74);
				event.setObjectID(id);
				const AudioEventRTS *p = &event;
				TheAudio->addAudioEvent(p);
			}
			m_stamp = frame;
		}
	}
}
