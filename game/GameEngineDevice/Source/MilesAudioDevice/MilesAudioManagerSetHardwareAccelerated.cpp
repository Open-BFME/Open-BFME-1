// ?setHardwareAccelerated@MilesAudioManager@@AAEXE@Z  retail 0x006A9910, 747 bytes
// (ret 4 at +0x2E8; the 8-entry speaker-config jump table follows at 0x006A9BFC).
// cl: /O2 /Ob1 /EHs-c- /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
//
// Identity: matched MilesAudioManager::openDevice (0x006B78D0) calls it as
// setHardwareAccelerated(prefs.getUseEAX3()) through ILT 0x0001F046.
// Shape: the Zero Hour selectProvider skeleton (EAX3, then Dolby Surround, then
// the Miles Fast 2D fallback), with one `success` flag and getProviderIndex
// called on string-literal temporaries, which gives each AsciiString its own
// frame slot as retail does (0x14-byte frame).

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
const Bool FALSE_BOOL = 0;
const Bool TRUE_BOOL = 1;

#include "ascii_string.h"

struct ProviderInfo
{
	AsciiString m_name;
	UnsignedInt m_id;
	int m_valid;
};

class DirectSoundInfo
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual int __stdcall getSpeakerConfig(unsigned int *config) = 0;
};

struct AudioLODInfo
{
	int m_maximumAmbientStreams;
	Bool m_allowDolby;
	Bool m_allowReverb;
	char m_padding[2];
};

class GameLODManager
{
	// These are the shipped AudioLOD fields at +0x170 and +0x16cc.
	// They remain public here because this TU only mirrors the retail layout.
	public:
	char m_beforeAudioLOD[0x170];
	AudioLODInfo m_audioLOD[2];
	char m_betweenAudioLODAndIndex[0x154c];

public:
	int m_audioLODIndex;
};

extern GameLODManager *TheGameLODManager;

class BfmeAwakenLog
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0c() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1c() = 0;
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual void v2c() = 0;
	virtual void v30() = 0;
	virtual void v34() = 0;
	virtual BfmeAwakenLog *v38(const char *message) = 0;
	virtual void v3c() = 0;
	virtual void v40() = 0;
	virtual void v44() = 0;
	virtual void v48() = 0;
	virtual void v4c(int value) = 0;
};

class BfmeAwakenDebug
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0c() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1c() = 0;
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual void v2c() = 0;
	virtual void v30() = 0;
	virtual void v34() = 0;
	virtual void v38() = 0;
	virtual void v3c() = 0;
	virtual void v40() = 0;
	virtual void v44() = 0;
	virtual void v48() = 0;
	virtual void v4c() = 0;
	virtual void v50() = 0;
	virtual void v54() = 0;
	virtual void v58() = 0;
	virtual void v5c() = 0;
	virtual void v60() = 0;
	virtual void v64() = 0;
	virtual void v68() = 0;
	virtual BfmeAwakenLog *v6c(int first, int second) = 0;
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

class VideoPlayer
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0c() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1c() = 0;
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual void v2c() = 0;
	virtual void v30() = 0;
	virtual void v34() = 0;
	virtual void v38() = 0;
	virtual void v3c() = 0;
	virtual void v40() = 0;
	virtual void v44() = 0;
	virtual void v48() = 0;
	virtual void v4c() = 0;
	virtual void v50() = 0;
	virtual void notifyVideoPlayerOfNewProvider(Bool nowHasValid) = 0;
};

extern VideoPlayer *TheVideoPlayer;

extern "C" __declspec(dllimport) void __stdcall AIL_get_DirectSound_info(
	void *sample, void **directSound, void *unused);
extern "C" __declspec(dllimport) int __stdcall AIL_open_3D_provider(
	UnsignedInt provider);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_rolloff_factor(
	UnsignedInt provider, float factor);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_speaker_type(
	UnsignedInt provider, UnsignedInt speakerType);
extern "C" __declspec(dllimport) const char *__stdcall AIL_last_error(void);

extern void j_00017d3c(void);
extern void j_0001cce7(void);
extern void j_0002214c(void);
extern void j_00033d89(void);
extern void j_0003da23(void);
extern void j_0003e045(void);

class MilesAudioManager
{
public:
	virtual void v00() = 0; virtual void v01() = 0; virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0; virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0; virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0; virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0; virtual void v18() = 0; virtual void v19() = 0;
	virtual void v20() = 0; virtual void v21() = 0; virtual void v22() = 0; virtual void v23() = 0;
	virtual void v24() = 0; virtual void v25() = 0; virtual void v26() = 0; virtual void v27() = 0;
	virtual void v28() = 0; virtual void v29() = 0; virtual void v30() = 0; virtual void v31() = 0;
	virtual void v32() = 0; virtual void v33() = 0; virtual void v34() = 0; virtual void v35() = 0;
	virtual void v36() = 0; virtual void v37() = 0; virtual void v38() = 0; virtual void v39() = 0;
	virtual void v40() = 0; virtual void v41() = 0; virtual void v42() = 0; virtual void v43() = 0;
	virtual void v44() = 0; virtual void v45() = 0;
	virtual Bool isOn(int which) const = 0;
	virtual UnsignedInt getProviderIndex(const AsciiString &providerName) const;
	void createListener(void);

private:
	void setHardwareAccelerated(Bool accelerated);

	char m_pad004[0x618 - 0x004];
	UnsignedInt m_bfme618;
	char m_pad61C[0x632 - 0x61C];
	Bool m_bfme632;
	char m_pad633[0x654 - 0x633];
	ProviderInfo m_provider3D[64];
	UnsignedInt m_providerCount;
	UnsignedInt m_selectedProvider;
	char m_pad95C[0xB60 - 0x95C];
	int m_speakerTypeB60;
};

// MSVC 7.1 reserves __thiscall in a free-function-pointer typedef.  These
// pointer-to-member views retain the retail ECX/stack ABI while routing each
// call through its existing ILT symbol.
struct MilesAudioManagerCallView
{
	void call(void);
	void callWithValue(int value);
};
typedef void (MilesAudioManagerCallView::*MilesAudioManagerCall)(void);
typedef void (MilesAudioManagerCallView::*MilesAudioManagerValueCall)(int value);

void MilesAudioManager::setHardwareAccelerated(Bool accelerated)
{
	if (!isOn(4))
		return;

	if (m_selectedProvider < m_providerCount)
	{
		// The 0x0003E045 ILT enters the already-owned sample-pool helper.
		union { void (*asFunction)(void); MilesAudioManagerValueCall asMember; } initPoolsCast;
		initPoolsCast.asFunction = j_0003e045;
		(reinterpret_cast<MilesAudioManagerCallView *>(this)->*initPoolsCast.asMember)(7);
		union { void (*asFunction)(void); MilesAudioManagerCall asMember; } clearVOACast;
		clearVOACast.asFunction = j_0002214c;
		(reinterpret_cast<MilesAudioManagerCallView *>(this)->*clearVOACast.asMember)();
		union { void (*asFunction)(void); MilesAudioManagerCall asMember; } clearVOBCast;
		clearVOBCast.asFunction = j_00033d89;
		(reinterpret_cast<MilesAudioManagerCallView *>(this)->*clearVOBCast.asMember)();
		m_bfme618 = 0;
		union { void (*asFunction)(void); MilesAudioManagerCall asMember; } closeCast;
		closeCast.asFunction = j_00017d3c;
		(reinterpret_cast<MilesAudioManagerCallView *>(this)->*closeCast.asMember)();
	}

	DirectSoundInfo *directSound;
	AIL_get_DirectSound_info(0, reinterpret_cast<void **>(&directSound), 0);
	if (directSound != 0)
	{
		unsigned int speakerConfig;
		directSound->getSpeakerConfig(&speakerConfig);
		switch ((unsigned char)speakerConfig)
		{
		case 0:
			m_speakerTypeB60 = 0;
			break;
		case 1:
			m_speakerTypeB60 = 1;
			break;
		case 2:
			m_speakerTypeB60 = 0;
			break;
		case 3:
			m_speakerTypeB60 = 3;
			break;
		case 4:
			m_speakerTypeB60 = 0;
			break;
		case 5:
			m_speakerTypeB60 = 2;
			break;
		case 6:
			m_speakerTypeB60 = 4;
			break;
		case 7:
			m_speakerTypeB60 = 5;
			break;
		default:
			m_speakerTypeB60 = 0;
			break;
		}
	}

	Bool setSpeakerType = FALSE_BOOL;
	Bool success = FALSE_BOOL;
	UnsignedInt providerIndex;
	if (accelerated)
	{
		providerIndex = MilesAudioManager::getProviderIndex("Creative Labs EAX 3 (TM)");
		if (providerIndex != (UnsignedInt)-1)
		{
			success = AIL_open_3D_provider(m_provider3D[providerIndex].m_id) == 0;
			if (!success)
			{
				if (_bfme_debugReportingEnabled())
				{
					_bfme_debugRecordCallsite(1);
					TheBfmeAwakenDebug->v60();
					BfmeAwakenLog *report = TheBfmeAwakenDebug->v6c(0, 0);
					report = report->v38("You do not have an EAX3-enabled sound card. Switching to software support.\n\nError code: ");
					report = report->v38(AIL_last_error());
					report = report->v38("\n\nTo remove this message, go to options.ini and change the line UseEAX3For3DAudio=1 to UseEAX3For3DAudio=0");
					report->v4c(2);
				}
			}
			else
				setSpeakerType = FALSE_BOOL;
		}
	}

	if (!success)
	{
		int speakerType = m_speakerTypeB60;
		if (speakerType > 0 && speakerType <= 5)
		{
			GameLODManager *lod = TheGameLODManager;
			if (lod == 0 || lod->m_audioLODIndex < 0 || lod->m_audioLODIndex >= 2 ||
				lod->m_audioLOD[lod->m_audioLODIndex].m_allowDolby)
			{
				providerIndex = MilesAudioManager::getProviderIndex("Dolby Surround");
				if (providerIndex != (UnsignedInt)-1)
				{
					success = AIL_open_3D_provider(m_provider3D[providerIndex].m_id) == 0;
					if (success)
						setSpeakerType = TRUE_BOOL;
				}
			}
		}

		if (!success)
		{
			m_selectedProvider = (UnsignedInt)-1;
			providerIndex = MilesAudioManager::getProviderIndex("Miles Fast 2D Positional Audio");
			success = AIL_open_3D_provider(m_provider3D[providerIndex].m_id) == 0;
			if (success)
				setSpeakerType = TRUE_BOOL;
		}
	}

	if (success)
	{
		m_selectedProvider = providerIndex;
		AIL_set_3D_rolloff_factor(m_provider3D[providerIndex].m_id, 0.0f);
		union { void (*asFunction)(void); MilesAudioManagerCall asMember; } samplePoolCast;
		samplePoolCast.asFunction = j_0003da23;
		(reinterpret_cast<MilesAudioManagerCallView *>(this)->*samplePoolCast.asMember)();
		createListener();
		if (setSpeakerType)
		{
			if (m_bfme632)
				AIL_set_3D_speaker_type(m_provider3D[providerIndex].m_id, 1);
			else
				AIL_set_3D_speaker_type(m_provider3D[providerIndex].m_id,
					m_speakerTypeB60);
		}
		if (TheVideoPlayer)
			TheVideoPlayer->notifyVideoPlayerOfNewProvider(1);
	}
}
