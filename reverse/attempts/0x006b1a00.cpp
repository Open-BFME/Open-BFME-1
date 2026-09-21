// ?d_006b1a00@@YAXXZ
// partial score=0.82 date=2026-09-21
// ?d_006b1a00@@YAXXZ
// partial score~0.82 date=2026-09-21
// Retail 0x006B1A00: BFME Miles fading-audio volume update, reached by the
// fading-list processor at 0x006B2FC0 (two call sites).  A sibling of the
// PlayingAudio sample-start helper 0x006B1B40 (same compute()/fade shape,
// same PlayingAudio/PlayingAudioRef/AudioSettings layout).  Type dispatch
// (playing->m_type) mirrors ZH's MilesAudioManager::processFadingList
// switch(playing->m_type) for cases PAT_Sample(0)/PAT_3DSample(1)/
// PAT_Stream, but BFME preserves the sample/stream's live pan (queries it
// via the Miles getter before the setter, using the *real* mss32.dll import
// names read straight from the PE import directory: AIL_sample_volume_pan
// and AIL_stream_volume_pan are the GET variants) instead of ZH's hardcoded
// 0.5f, and inserts a new, BFME-only m_type==2 case *before* ZH's
// PAT_Stream (which shifts to m_type==3 here): it looks up a 3D-sample
// handle from a per-instance 0x40-byte-stride table at this+0xb44, indexed
// by the PlayingAudio's m_sample field reinterpreted as an integer, then
// shares the m_type==1 tail (null check + AIL_set_3D_sample_volume). No ZH
// counterpart names the m_type==2 case, so its identity stays address-
// derived (do not call it PAT_Stream -- confirmed PAT_Stream is m_type==3
// here).
//
// Size is 1 byte short (251 vs retail 252) and 45 non-reloc bytes differ,
// ALL of them inside the m_type==1||2 dispatch (from +0x9c onward); the
// fade/volume prologue and both the sample(0) and stream(3) cases are
// BYTE-EXACT.  Retail's shape there is "dec eax; je case1Tail; dec eax;
// jne default" (6 bytes) where case1's own body (mov ecx,[ecx+8]) sits
// physically first and the m_type==2/table path *jumps into the middle*
// of it, past that one mov, to a shared "test ecx,ecx" tail -- i.e. the
// compiler cross-jumped two textually distinct blocks into one shared
// suffix. A plain if/else, an if/else on --type, and an explicit
// switch(type){case 2: ...; default: ...} were all tried (this file keeps
// the switch form, closest at 251B/45 diffs); none reproduced the same
// dec/dec/je/jne shape or the shared mid-block jump target. Treat as an
// MSVC 7.1 cross-block tail-merge residue, not a semantic or layout gap.

typedef float Real;
typedef unsigned char Bool;
typedef void *HSAMPLE;
typedef void *H3DSAMPLE;
typedef void *HSTREAM;

extern "C" __declspec(dllimport) void __stdcall _AIL_sample_volume_pan(
	HSAMPLE sample, Real *volume, Real *pan);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_sample_volume_pan(
	HSAMPLE sample, Real volume, Real pan);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_3D_sample_volume(
	H3DSAMPLE sample, Real volume);
extern "C" __declspec(dllimport) void __stdcall _AIL_stream_volume_pan(
	HSTREAM stream, Real *volume, Real *pan);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_stream_volume_pan(
	HSTREAM stream, Real volume, Real pan);

#define Rva006B1B40One (*(const Real *)0x01075334)
#define Rva006B1B40Zero (*(const Real *)0x01075350)

class Rva006B1B40AudioEvent;

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

struct Rva006B1A00TableEntry
{
	char m_pad0[4];
	void *m_slot;
	char m_pad8[0x38];
};

class Rva006B1B40MilesAudioManager : public Rva006AE150Owner
{
public:
	void rva006B1A00UpdateFadeVolume(Rva006B1B40PlayingAudioRef *playingRef);

private:
	Rva006B1B40AudioSettings *m_audioSettings;
	char m_pad10[0xb34];
	Rva006B1A00TableEntry *m_slotTable;
};

void Rva006B1B40MilesAudioManager::rva006B1A00UpdateFadeVolume(
	Rva006B1B40PlayingAudioRef *playingRef)
{
	Rva006B1B40AudioEvent *event = playingRef->m_ptr->m_event;
	Real volume = compute((Rva006AE150Argument *)event, 1);
	Real fade = 1.0f - ((Real)playingRef->m_ptr->m_fadeFrame /
		(Real)m_audioSettings->m_fadeAudioFrames);
	if (fade < Rva006B1B40Zero)
		fade = Rva006B1B40Zero;
	else if (fade > Rva006B1B40One)
		fade = Rva006B1B40One;
	volume = volume * fade;

	Real pan;
	int type = playingRef->m_ptr->m_type;
	if (type == 0)
	{
		HSAMPLE sample = playingRef->m_ptr->m_sample;
		_AIL_sample_volume_pan(sample, 0, &pan);
		sample = playingRef->m_ptr->m_sample;
		_AIL_set_sample_volume_pan(sample, volume, pan);
		return;
	}

	if (type == 1 || type == 2)
	{
		H3DSAMPLE sample3D;
		switch (type)
		{
		case 2:
		{
			int index = (int)(long)playingRef->m_ptr->m_sample;
			sample3D = m_slotTable[index].m_slot;
			break;
		}
		default:
			sample3D = (H3DSAMPLE)playingRef->m_ptr->m_sample;
			break;
		}
		if (sample3D)
			_AIL_set_3D_sample_volume(sample3D, volume);
		return;
	}

	if (type == 3)
	{
		HSTREAM stream = (HSTREAM)playingRef->m_ptr->m_sample;
		_AIL_stream_volume_pan(stream, 0, &pan);
		stream = (HSTREAM)playingRef->m_ptr->m_sample;
		_AIL_set_stream_volume_pan(stream, volume, pan);
	}
}
