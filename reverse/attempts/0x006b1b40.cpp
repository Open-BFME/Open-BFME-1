// ?d_006b1b40@@YAXXZ
// partial score=0.88 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x006B1B40: BFME Miles sample filter setup reached by the
// PlayingAudio sample-start helper at 0x006B3E30.  The address-qualified
// method name preserves the BFME fork's one-reference argument shape.
// Size now matches retail exactly (332B): the delay-block "value = 0.0"
// reset and the reverb-off "wet" argument must be literal 0.0f, not a
// load of the Rva006B1B40Zero global -- retail bakes both as an immediate
// (mov [esp+N],0 / push 0) since MSVC treats a true float literal as a
// compile-time bit pattern instead of a memory dereference.
// Remaining 41 non-reloc bytes are pure MSVC 7.1 register-allocation
// residue (ecx/edx/eax permutations and one fld operand-order swap in the
// fade divide and the delay/reverb argument setup); confirmed resistant to
// declaration-order, named-temp, and comparison-operand-order rewrites --
// each left the compiled shape hash unchanged, so treat as compiler-
// internal scheduling, not a semantic or layout error.

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
extern void j_00027124();

#define Rva006B1B40One (*(const Real *)0x01075334)
#define Rva006B1B40Zero (*(const Real *)0x01075350)

struct Rva006B1B40AudioInfo
{
	char m_pad00[0x7c];
	Real m_reverbDry;
	Real m_reverbWet;
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

void Rva006B1B40MilesAudioManager::rva006B1B40InitFilters(
	Rva006B1B40PlayingAudioRef *playingRef)
{
	Rva006B1B40PlayingAudio *playing = playingRef->m_ptr;
	HSAMPLE sample = playing->m_sample;

	Real volume = compute(
		(Rva006AE150Argument *)playing->m_event, 1);
	Real fade = 1.0f - ((Real)playingRef->m_ptr->m_fadeFrame /
		(Real)m_audioSettings->m_fadeAudioFrames);
	if (fade < Rva006B1B40Zero)
		fade = Rva006B1B40Zero;
	else if (fade > Rva006B1B40One)
		fade = Rva006B1B40One;

	_AIL_set_sample_volume_pan(sample, volume * fade, 0.5f);

	typedef Real (Rva006B1B40AudioEvent::*GetPitchScale)(void) const;
	union
	{
		void (*freeGetPitchScale)();
		GetPitchScale memberGetPitchScale;
	} getPitchScale;
	getPitchScale.freeGetPitchScale = ::j_00027124;
	volatile Real pitchScale =
		(playing->m_event->*getPitchScale.memberGetPitchScale)();
	if (pitchScale == Rva006B1B40Zero)
	{
	}
	else
	{
		int rate = _AIL_sample_playback_rate(sample);
		rate = (int)(rate * pitchScale);
		_AIL_set_sample_playback_rate(sample, rate);
	}

	if (playing->m_event->m_delay > Rva006B1B40Zero)
	{
		HPROVIDER delayFilter = this->m_delayFilter;
		Real value = playing->m_event->m_delay;
		_AIL_set_sample_processor(sample, 1, delayFilter);
		_AIL_set_filter_sample_preference(sample, "Mono Delay Time", &value);
		value = 0.0f;
		_AIL_set_filter_sample_preference(sample, "Mono Delay", &value);
		_AIL_set_filter_sample_preference(sample, "Mono Delay Mix", &value);
	}

	if (this->m_reverbEnabled)
		_AIL_set_sample_reverb_levels(sample, playing->m_event->m_info->m_reverbDry,
			playing->m_event->m_info->m_reverbWet);
	else
		_AIL_set_sample_reverb_levels(sample, 1.0f, 0.0f);
}
