// cl: /DNDEBUG /MD /EHsc
// GlobalWeatherSystem::setWeather. Switches the current weather index and
// plays that entry's sound through TheAudio. Same +0x0C/+0x10/+0x28 layout
// as the constructor and destructor.

class AsciiString
{
public:
	char *m_data;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	~AudioEventRTS();

private:
	unsigned char m_raw[0x70];
};

class ClientSubsystem
{
public:
#define SLOT(n) virtual void slot##n();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03)
	SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11)
	SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16)
	virtual unsigned addAudioEvent(const AudioEventRTS *event);
	SLOT(18)
	virtual void removeAudioEvent(unsigned handle);
#undef SLOT
};

extern ClientSubsystem *TheAudioClientUpdate;

class WeatherData
{
public:
	AsciiString m_sound;
	int m_hasLightning;
};

class GlobalWeatherSystem
{
public:
	void setWeather(int which);

private:
	unsigned char m_pad[0x0C];
	int m_current;
	unsigned m_handle;
	int m_unk14;
	void *m_str18;
	void *m_str1C;
	int m_unk20;
	int m_unk24;
	WeatherData m_weather[5];
};

void GlobalWeatherSystem::setWeather(int which)
{
	if (m_current == which)
		return;

	TheAudioClientUpdate->removeAudioEvent(m_handle);

	AsciiString *name = &m_weather[which].m_sound;
	m_handle = 1;
	m_current = which;
	if (name->m_data)
	{
		AudioEventRTS ev(*name, 0);
		m_handle = TheAudioClientUpdate->addAudioEvent(&ev);
	}
}
