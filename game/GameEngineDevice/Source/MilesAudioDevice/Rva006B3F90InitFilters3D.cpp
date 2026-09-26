// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail 0x006B1CE0: the 3D filter setup that Rva006B3F90Owner::configure3D
// (0x006B3F90) tail-calls through ILT 0x000091BA with its wrapper and position.
// Zero Hour twin: MilesAudioManager::initFilters3D -- volume, pitch shift, then
// the low-pass occlusion gated on m_lowPassFreq > 0 and the position being off
// screen. BFME looks the 3D sample up from the playing-audio wrapper, scales the
// volume by the fade, always sets occlusion (0 when the filter is off), and ends
// with two owner calls. Layouts follow the landed configure3D and 0x006B1B40
// views of the same objects; owners stay address-derived.

typedef float Real;
typedef unsigned char Bool;

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_volume(
	unsigned int sample, Real volume);
extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_playback_rate(
	unsigned int sample);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_playback_rate(
	unsigned int sample, int rate);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_occlusion(
	unsigned int sample, Real occlusion);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// AudioEventInfo+0x70 m_lowPassFreq (name_oracle field_names witness).
struct Rva006B3F90AudioInfo
{
	char m_pad00[0x70];
	Real m_lowPassFreq;
};

struct Rva006B3F90AudioEvent
{
	char m_pad00[8];
	Rva006B3F90AudioInfo *m_audioInfo;
};

struct Rva006B3F90Inner
{
	char m_pad00[8];
	int m_index;
	int m_type;
	char m_pad10[4];
	Rva006B3F90AudioEvent *m_audioEvent;
	char m_pad18[0x10];
	Real m_fadeFrame;
};

struct Rva006B3F90Wrapper
{
	Rva006B3F90Inner *m_inner;
};

struct Rva006B3F90Settings
{
	char m_pad00[0x3c];
	int m_fadeAudioFrames;
};

struct Rva006B3F90SampleEntry
{
	char m_pad00[4];
	unsigned int m_sample;
	char m_pad08[0x38];
};

// Pitch getter at 0x000B21C0 reads the event's +0x4c.
class Rva000B21C0Owner
{
public:
	Real body(void) const;
};

// Same manager object: setReverb's view also keeps the sample pool at +0xb44.
struct Rva0069A6F0Playing;
class Rva0069A6F0Owner
{
public:
	void setReverb(Rva0069A6F0Playing **pp);
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

class Rva006B3F90Owner : public Rva006AE150Owner
{
public:
	void initFilters3D(Rva006B3F90Wrapper *wrapper, const Coord3D *position);

	// 0x006A1C60: thiscall, ret 8; stores 0 or 1 through its second argument.
	void rva006A1C60(Rva006B3F90Wrapper *wrapper, Bool *result);

private:
	Rva006B3F90Settings *m_settings;
	char m_pad10[0xb34];
	Rva006B3F90SampleEntry *m_samples;

	// Virtual slot 0x184 (index 97); ZH's isOnScreen(pos) sits at this point.
	Bool virtualSlot184(const Coord3D *position)
	{
		typedef Bool (Rva006B3F90Owner::*Fn)(const Coord3D *position);
		return (this->*(Fn &)((*(void ***)this)[0x184 / 4]))(position);
	}
};

void Rva006B3F90Owner::initFilters3D(
	Rva006B3F90Wrapper *wrapper, const Coord3D *position)
{
	Rva006B3F90Inner *inner = wrapper->m_inner;

	unsigned int sample;
	switch (inner->m_type)
	{
	case 1:
		sample = (unsigned int)inner->m_index;
		break;
	case 2:
		sample = m_samples[inner->m_index].m_sample;
		break;
	default:
		sample = 0;
		break;
	}

	Rva006B3F90AudioEvent *event = inner->m_audioEvent;
	Real volume = compute((Rva006AE150Argument *)event, 1);
	Real fade = 1.0f - ((Real)wrapper->m_inner->m_fadeFrame /
		(Real)m_settings->m_fadeAudioFrames);
	if (fade < 0.0f)
		fade = 0.0f;
	else if (fade > 1.0f)
		fade = 1.0f;
	volume = volume * fade;

	AIL_set_3D_sample_volume(sample, volume);

	{
		Real pitchScale =
			((const Rva000B21C0Owner *)inner->m_audioEvent)->body();
		if (pitchScale != 0.0f)
		{
			int rate = (int)(AIL_3D_sample_playback_rate(sample) * pitchScale);
			AIL_set_3D_sample_playback_rate(sample, rate);
		}
	}

	if (inner->m_audioEvent->m_audioInfo->m_lowPassFreq > 0.0f)
	{
		if (!virtualSlot184(position))
			AIL_set_3D_sample_occlusion(sample,
				1.0f - inner->m_audioEvent->m_audioInfo->m_lowPassFreq);
		else
			AIL_set_3D_sample_occlusion(sample, 0.0f);
	}
	else
		AIL_set_3D_sample_occlusion(sample, 0.0f);

	{
		Bool result;
		rva006A1C60(wrapper, &result);
	}
	((Rva0069A6F0Owner *)this)->setReverb((Rva0069A6F0Playing **)wrapper);
}
