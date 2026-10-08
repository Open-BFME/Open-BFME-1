// cl: /Igame/Libraries/Source/WWVegas/WWLib
// The surrounding constructor establishes the two event-name fields at +0x14
// and +0x18; this body is the paired operation that starts both events and
// remembers their handles.  The local facades preserve BFME's retail layouts
// without importing the later Zero Hour audio-vtable order.

#include "ascii_string.h"

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, int owner);
	~AudioEventRTS();

	char m_head[8];
	void *m_eventInfo;
	char m_rest[0x64];
};

class AudioManager
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual unsigned int addAudioEvent(AudioEventRTS *event);
	virtual void v5c();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void v6c();
	virtual void v70();
	virtual void v74();
	virtual void v78();
	virtual void v7c();
	virtual void v80();
	virtual void v84();
	virtual void v88();
	virtual void v8c();
	virtual void v90();
	virtual void v94();
	virtual void v98();
	virtual void v9c();
	virtual void va0();
	virtual void va4();
	virtual void va8();
	virtual void prepareAudioEvent(AudioEventRTS *event);
};

extern AudioManager *TheAudio; // retail 0x012ED668

class Rva00491110
{
public:
	void startAudio();

private:
	char m_head[0x14];
	AsciiString m_firstEventName;
	AsciiString m_secondEventName;
	unsigned int m_firstHandle;
	unsigned int m_secondHandle;
};

void Rva00491110::startAudio()
{
	m_firstHandle = 1;
	m_secondHandle = 1;

	if (TheAudio == 0)
		return;

	AudioEventRTS first(m_firstEventName, 2);
	TheAudio->prepareAudioEvent(&first);
	if (first.m_eventInfo != 0)
		m_firstHandle = TheAudio->addAudioEvent(&first);

	AudioEventRTS second(m_secondEventName, 2);
	TheAudio->prepareAudioEvent(&second);
	if (second.m_eventInfo != 0)
		m_secondHandle = TheAudio->addAudioEvent(&second);
}
