// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x006B1B40: BFME twin of ZH MilesAudioManager::initFilters, reached from 0x006B3E30.
// Owners stay address-derived; the argument is one PlayingAudio reference, not ZH's sample/event pair.

typedef float Real;
typedef unsigned char Bool;
typedef void *HSAMPLE;
typedef void *HPROVIDER;

extern "C" __declspec(dllimport) void __stdcall _AIL_set_sample_volume_pan(
	HSAMPLE sample, Real volume, Real pan);
extern "C" __declspec(dllimport) int __stdcall _AIL_sample_playback_rate(
	HSAMPLE sample);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_sample_playback_rate(
	HSAMPLE sample, int rate);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_sample_processor(
	HSAMPLE sample, int effect, HPROVIDER provider);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_filter_sample_preference(
	HSAMPLE sample, const char *name, Real *value);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_sample_reverb_levels(
	HSAMPLE sample, Real dry, Real wet);

// Miles takes (dry, wet); retail passes +0x80 as dry and +0x7c as wet.
struct Rva006B1B40AudioInfo
{
	char m_pad00[0x7c];
	Real m_reverbWet;
	Real m_reverbDry;
};

class Rva006B1B40AudioEvent
{
public:
	char m_pad00[8];
	Rva006B1B40AudioInfo *m_info;
	char m_pad0c[0x40];
	Real m_pitchScale;
	char m_pad50[4];
	Real m_delay;
};

// Pitch getter at 0x000B21C0 reads the event's +0x4c.
class Rva000B21C0Owner
{
public:
	Real body(void) const;
};

class Rva006B1B40RefCountClass
{
public:
	virtual ~Rva006B1B40RefCountClass();

private:
	volatile long m_refCount;
};

class Rva006B1B40PlayingAudio : public Rva006B1B40RefCountClass
{
public:
	HSAMPLE m_sample;
	int m_type;
	int m_status;
	Rva006B1B40AudioEvent *m_event;
	void *m_file;
	char m_pad1c[0x0c];
	Real m_fadeFrame;
};

class Rva006B1B40PlayingAudioRef
{
public:
	Rva006B1B40PlayingAudio *m_ptr;
	Rva006B1B40PlayingAudio *operator->(void) const
	{
		return m_ptr;
	}
};

struct Rva006B1B40AudioSettings
{
	char m_pad00[0x3c];
	int m_fadeAudioFrames;
};

class Rva006AE150Argument;
class Rva006AE150Owner
{
public:
	virtual void rva006AE150UnusedVirtual(void) {}
	Real compute(Rva006AE150Argument *argument, int apply);

private:
	char m_basePad[8];
};

class Rva006B1B40MilesAudioManager : public Rva006AE150Owner
{
public:
	void rva006B1B40InitFilters(Rva006B1B40PlayingAudioRef *playingRef);

private:
	Rva006B1B40AudioSettings *m_audioSettings;
	char m_pad10[0x623];
	Bool m_reverbEnabled;
	char m_pad634[0x334];
	HPROVIDER m_delayFilter;
};

// ?rva006B1B40InitFilters@Rva006B1B40MilesAudioManager@@QAEXPAVRva006B1B40PlayingAudioRef@@@Z
void Rva006B1B40MilesAudioManager::rva006B1B40InitFilters(
	Rva006B1B40PlayingAudioRef *playingRef)
{
	Rva006B1B40PlayingAudio *playing = playingRef->m_ptr;
	Rva006B1B40AudioEvent *event = playing->m_event;
	HSAMPLE sample = playing->m_sample;

	Real volume = compute((Rva006AE150Argument *)event, 1);
	Real fade = 1.0f - ((Real)playingRef->m_ptr->m_fadeFrame /
		(Real)m_audioSettings->m_fadeAudioFrames);
	if (fade < 0.0f)
		fade = 0.0f;
	else if (fade > 1.0f)
		fade = 1.0f;

	_AIL_set_sample_volume_pan(sample, volume * fade, 0.5f);

	Real pitchScale =
		((const Rva000B21C0Owner *)playing->m_event)->body();
	if (pitchScale == 0.0f)
	{
	}
	else
	{
		_AIL_set_sample_playback_rate(sample, (int)(_AIL_sample_playback_rate(sample) * pitchScale));
	}

	if (playing->m_event->m_delay > 0.0f)
	{
		Real value;
		value = playing->m_event->m_delay;
		_AIL_set_sample_processor(sample, 1, m_delayFilter);
		_AIL_set_filter_sample_preference(sample, "Mono Delay Time", &value);
		value = 0.0f;
		_AIL_set_filter_sample_preference(sample, "Mono Delay", &value);
		_AIL_set_filter_sample_preference(sample, "Mono Delay Mix", &value);
	}

	if (m_reverbEnabled)
		_AIL_set_sample_reverb_levels(sample, playing->m_event->m_info->m_reverbDry,
			playing->m_event->m_info->m_reverbWet);
	else
		_AIL_set_sample_reverb_levels(sample, 1.0f, 0.0f);
}
