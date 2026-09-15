// cl: /DNDEBUG /MD /EHsc
//
// SoundFadeTransition::update at retail RVA 0x0059D2D0.
// The vtable at 0x00D0C780 and the field table at 0x00D0C7C8 identify this
// object as the SOUNDFADE transition.  The field table names StartFrame at
// +0x10, EndFrame at +0x14, and FadeInUnfrozenSounds at +0x18.

typedef int Int;
typedef unsigned char Bool;

class AudioClientUpdate
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8(); virtual void slotAC();
	virtual void slotB0(); virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual void slotC0(); virtual void slotC4(); virtual void slotC8(); virtual void slotCC();
	virtual void slotD0(); virtual void slotD4(); virtual void slotD8(); virtual void slotDC();
	virtual void slotE0(); virtual void slotE4(); virtual void slotE8(); virtual void slotEC();
	virtual void unfreezeSounds(int fadeIn);
};

extern AudioClientUpdate *TheAudioClientUpdate;

class SoundFadeTransition
{
public:
	virtual void slot00();
	virtual void init(void *window);
	virtual void update(Int frame);
	virtual void reverse();
	virtual void draw();
	virtual void skip();
	virtual Bool isFinished();
	virtual Int getFrameLength();

	Int m_frameLength;
	Bool m_isFinished;
	Bool m_isForward;
	Bool m_isReversed;
	Bool m_pad0B;
	void *m_win;
	Int m_startFrame;
	Int m_endFrame;
	Bool m_fadeInUnfrozenSounds;
	Bool m_soundsUnfrozen;
};

void SoundFadeTransition::update(Int frame)
{
	if (frame < m_startFrame || frame > m_endFrame)
		return;

	if ((m_isForward && (frame == m_endFrame || m_startFrame == m_endFrame)) ||
		(!m_isForward && (frame == m_startFrame || m_startFrame == m_endFrame)))
	{
		if (m_soundsUnfrozen)
		{
			if (m_fadeInUnfrozenSounds)
				TheAudioClientUpdate->unfreezeSounds(0);
			else
				TheAudioClientUpdate->unfreezeSounds(1);
			m_soundsUnfrozen = false;
		}
		m_isFinished = true;
	}
	else if (!m_soundsUnfrozen)
	{
		TheAudioClientUpdate->slotEC();
		m_soundsUnfrozen = true;
	}
}
