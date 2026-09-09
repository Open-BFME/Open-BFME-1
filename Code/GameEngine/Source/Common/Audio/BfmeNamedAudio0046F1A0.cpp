// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// bfmeNamedAudio0046F1A0, retail 0x0046F1A0.

#include "StringInline.h"

class AudioEventRTS
{
public:
    AudioEventRTS(const AsciiString &eventName, int extra);
    virtual void slot00();
    ~AudioEventRTS();

    void *m_beforeEventInfo;
    void *m_eventInfo;

private:
    unsigned char m_padding[0x64];
};

class AudioClientUpdate
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
	virtual unsigned int addAudioEvent(AudioEventRTS *event) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void getInfoForAudioEvent(const AudioEventRTS *event) const = 0;
};

extern AudioClientUpdate *TheAudioClientUpdate;

// ?bfmeNamedAudio0046F1A0@@YAXPBD@Z
void __cdecl bfmeNamedAudio0046F1A0(const char *text)
{
    if (TheAudioClientUpdate)
    {
        AudioEventRTS event(AsciiString(text), 2);
		TheAudioClientUpdate->getInfoForAudioEvent(&event);
		if (event.m_eventInfo)
			TheAudioClientUpdate->addAudioEvent(&event);
	}
}
