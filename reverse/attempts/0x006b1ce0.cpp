// ?d_006b1ce0@@YAXXZ
// partial score=0.95 date=2026-09-21
// ?d_006b1ce0@@YAXXZ
// partial score~0.95 date=2026-09-21
// Retail 0x006B1CE0: Rva006B3F90Owner::initFilters3D(Wrapper*, const Coord3D*),
// the method DECLARED but not defined in the already-landed
// Code/GameEngineDevice/Source/MilesAudioDevice/Rva006B3F90Configure3D.cpp,
// which calls it via a member-pointer thunk at the end of configure3D().
// This file redeclares an independent, layout-matching view of the same
// class/structs (each landed source in this codebase keeps its own opaque
// view; the field offsets below were proven against configure3D's own
// switch(inner->m_type) sample-selection code, which this function repeats
// verbatim) plus the compute()/fade-clamp shape shared with the sibling
// bodies at 0x006B1A00 and 0x006B1B40 (same m_settings@0xc, same
// Rva006AE150Owner compute() base, same per-instance sample table at
// this+0xb44 with 0x40-byte stride).
//
// ZH twin: GeneralsMD/Code/GameEngineDevice/Source/MilesAudioDevice/
// MilesAudioManager.cpp, MilesAudioManager::initFilters3D. BFME's low-pass
// (occlusion) block always calls AIL_set_3D_sample_occlusion (passing 0
// when the ZH guard `m_lowPassFreq > 0 && !isOnScreen(pos)` is false)
// instead of ZH's skip-the-call-entirely shape; "isOnScreen" is reached
// here as a raw vtable slot (0x184 bytes = index 97) on `this`, since the
// real interface it belongs to isn't visible from this body alone.
//
// Size is now byte-EXACT (301B) and only 15 non-reloc bytes differ, all one
// mirrored pair: retail binds `this` to ebx and the "no 3D handle" default
// to edi; ours binds the opposite way. This is a whole-body callee-saved
// register swap (docs/shape_levers.md's documented dead end), not a
// semantic or layout gap -- every instruction, branch target, and call
// argument shape is otherwise identical. Two structural fixes got the size
// from 337/316/312 down to exact: (1) the occlusion setter must be called
// TWICE, once per branch with its own literal argument expression
// (`AIL_set_3D_sample_occlusion(sample, One - info->m_lowPassFreq)` /
// `AIL_set_3D_sample_occlusion(sample, 0.0f)`), not once from a shared
// `Real occlusion` local -- retail prepares each branch's argument directly
// on the stack rather than through a named variable; (2) the raw vtable
// slot 0x184 call must be a single fused expression
// (`(this->*(Fn&)((*(void***)this)[0x184/4]))(position)`), not stored to a
// named function-pointer local first, or MSVC emits "mov reg,[slot]; call
// reg" (8B) instead of retail's fused "call dword ptr [reg+0x184]" (6B).

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
extern void j_00027124();
extern void j_000445d0();
extern void j_0002e60e();

#define Rva006B1CE0One (*(const Real *)0x01075334)
#define Rva006B1CE0Zero (*(const Real *)0x01075350)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Rva006B1CE0AudioInfo
{
	char m_pad00[0x70];
	Real m_lowPassFreq;
};

class Rva006B1CE0AudioEvent
{
public:
	char m_pad00[8];
	Rva006B1CE0AudioInfo *m_audioInfo;
};

struct Rva006B1CE0Inner
{
	char m_pad00[8];
	int m_index;
	int m_type;
	char m_pad10[4];
	Rva006B1CE0AudioEvent *m_audioEvent;
	char m_pad18[0x10];
	Real m_fadeFrame;
};

struct Rva006B1CE0Wrapper
{
	Rva006B1CE0Inner *m_inner;
};

struct Rva006B1CE0Settings
{
	char m_pad00[0x3c];
	int m_fadeAudioFrames;
};

struct Rva006B1CE0SampleEntry
{
	char m_pad00[4];
	unsigned int m_sample;
	char m_pad08[0x38];
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

class Rva006B1CE0Owner : public Rva006AE150Owner
{
public:
	void rva006B1CE0InitFilters3D(
		Rva006B1CE0Wrapper *wrapper, const Coord3D *position);

private:
	Rva006B1CE0Settings *m_settings;
	char m_pad10[0xb34];
	Rva006B1CE0SampleEntry *m_samples;

	typedef Bool (Rva006B1CE0Owner::*Rva006B1CE0IsOnScreenFn)(
		const Coord3D *position);

	Bool rva006B1CE0IsOnScreen(const Coord3D *position)
	{
		return (this->*(Rva006B1CE0IsOnScreenFn &)(
			(*(void ***)this)[0x184 / 4]))(position);
	}

	typedef void (Rva006B1CE0Owner::*Rva006B1CE0Opaque445D0)(
		Rva006B1CE0Wrapper *, Real *);
	__forceinline void rva006B1CE0CallOpaque445D0(Rva006B1CE0Wrapper *wrapper, Real *value)
	{
		union
		{
			void (*freeFn)();
			Rva006B1CE0Opaque445D0 memberFn;
		} fn;
		fn.freeFn = ::j_000445d0;
		(this->*fn.memberFn)(wrapper, value);
	}

	typedef void (Rva006B1CE0Owner::*Rva006B1CE0Opaque2E60E)(
		Rva006B1CE0Wrapper *);
	__forceinline void rva006B1CE0CallOpaque2E60E(Rva006B1CE0Wrapper *wrapper)
	{
		union
		{
			void (*freeFn)();
			Rva006B1CE0Opaque2E60E memberFn;
		} fn;
		fn.freeFn = ::j_0002e60e;
		(this->*fn.memberFn)(wrapper);
	}
};

void Rva006B1CE0Owner::rva006B1CE0InitFilters3D(
	Rva006B1CE0Wrapper *wrapper, const Coord3D *position)
{
	Rva006B1CE0Inner *inner = wrapper->m_inner;

	unsigned int sample;
	switch (inner->m_type)
	{
	case 1:
		sample = (unsigned int)inner->m_index;
		break;
	case 2:
	{
		sample = m_samples[inner->m_index].m_sample;
		break;
	}
	default:
		sample = 0;
		break;
	}

	Rva006B1CE0AudioEvent *event = inner->m_audioEvent;
	Real volume = compute((Rva006AE150Argument *)event, 1);
	Real fade = 1.0f - ((Real)wrapper->m_inner->m_fadeFrame /
		(Real)m_settings->m_fadeAudioFrames);
	if (fade < Rva006B1CE0Zero)
		fade = Rva006B1CE0Zero;
	else if (fade > Rva006B1CE0One)
		fade = Rva006B1CE0One;
	volume = volume * fade;

	AIL_set_3D_sample_volume(sample, volume);

	typedef Real (Rva006B1CE0AudioEvent::*GetPitchScale)(void) const;
	union
	{
		void (*freeGetPitchScale)();
		GetPitchScale memberGetPitchScale;
	} getPitchScale;
	getPitchScale.freeGetPitchScale = ::j_00027124;
	Real pitchScale =
		(inner->m_audioEvent->*getPitchScale.memberGetPitchScale)();
	if (pitchScale != Rva006B1CE0Zero)
	{
		int rate = (int)(AIL_3D_sample_playback_rate(sample) * pitchScale);
		AIL_set_3D_sample_playback_rate(sample, rate);
	}

	if (inner->m_audioEvent->m_audioInfo->m_lowPassFreq > Rva006B1CE0Zero &&
		!rva006B1CE0IsOnScreen(position))
		AIL_set_3D_sample_occlusion(sample,
			Rva006B1CE0One - inner->m_audioEvent->m_audioInfo->m_lowPassFreq);
	else
		AIL_set_3D_sample_occlusion(sample, 0.0f);

	rva006B1CE0CallOpaque445D0(wrapper, &pitchScale);
	rva006B1CE0CallOpaque2E60E(wrapper);
}
