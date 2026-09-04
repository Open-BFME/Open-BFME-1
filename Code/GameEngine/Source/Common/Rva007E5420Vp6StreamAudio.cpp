// Retail 0x007E5420: VP6 stream movie-audio setup.
// The stream layout is shared with the neighbouring VP6 decode/render bodies:
// the two audio handles live at +0x5c and +0x60.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
	void concat(const char *text, int length);
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, int extra);
	~AudioEventRTS();

	void *m_vptr;
	char m_pad04[4];
	void *m_eventInfo;
	char m_pad0c[0x70 - 0x0c];
};

class Rva007E5420AudioManager
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
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void slot0d();
	virtual void slot0e();
	virtual void slot0f();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual int addAudioEvent(const AudioEventRTS *event);

	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1a();
	virtual void slot1b();
	virtual void slot1c();
	virtual void slot1d();
	virtual void slot1e();
	virtual void slot1f();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2a();
	virtual void getInfoForAudioEvent(const AudioEventRTS *event);
	virtual void slot2c();
	virtual void slot2d();
	virtual void slot2e();
	virtual void slot2f();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3a();
	virtual void slot3b();
	virtual void slot3c();
	virtual void slot3d();
	virtual void slot3e();
	virtual void slot3f();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4a();
	virtual void slot4b();
	virtual void slot4c();
	virtual int finishAudioSetup();
};

extern Rva007E5420AudioManager *TheAudio;

class Rva007E5420Vp6Stream
{
public:
	int setAudio(const AsciiString &name);

private:
	char m_pad00[0x5c];
	int m_audioHandle;
	int m_musicHandle;
};

int Rva007E5420Vp6Stream::setAudio(const AsciiString &name)
{
	int result = 0;
	m_audioHandle = 1;
	m_musicHandle = 1;

	AsciiString musicName(name);
	musicName.concat("_Music", 6);

	if (TheAudio)
	{
		AudioEventRTS event(name, 2);
		TheAudio->getInfoForAudioEvent(&event);
		if (event.m_eventInfo)
		{
			m_audioHandle = TheAudio->addAudioEvent(&event);
			result = -TheAudio->finishAudioSetup();
		}

		AudioEventRTS musicEvent(musicName, 2);
		TheAudio->getInfoForAudioEvent(&musicEvent);
		if (musicEvent.m_eventInfo)
		{
			m_musicHandle = TheAudio->addAudioEvent(&musicEvent);
			result = -TheAudio->finishAudioSetup();
		}
	}

	return result;
}
