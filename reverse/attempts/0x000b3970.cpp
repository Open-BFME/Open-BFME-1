// ?generateFilename@AudioEventRTS@@QAEXXZ
// partial score=0.35 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// AudioEventRTS::generateFilename at retail RVA 0x000B3970 (400B). BLOCKED:
// see notes below and reverse/re_attempts.log. This file records the shape
// found via tools/dis_retail.py 0x000B3970 and the ZH twin
// (reference/.../AudioEventRTS.cpp generateFilename) for the next attempt;
// it compiles but is not byte-exact.
//
// Confirmed against the retail bytes:
//  - this+0x46 (bool) gates the whole body together with this+8
//    (m_eventInfo); on failure it is a bare early return, no assignment.
//  - m_filenameToLoad = generateFilenamePrefix(m_eventInfo->m_soundType, false)
//    is a real thiscall member call (0x0003B769, already landed at
//    Code/GameEngine/Source/Common/Audio/AudioEventRTSGenerateFilenamePrefix.cpp)
//    with ecx implicitly still `this` (never reloaded).
//  - AudioEventInfo::m_soundType lives at +0x84 (matches generateFilenamePrefix's
//    arg fetch and the `cmp eax,2` branch).
//  - The `cmp eax, 2` branch is a single literal compare, not the ZH
//    `soundType == AT_Music || soundType == AT_Streaming` pair -- BFME
//    numbers whichever "simple single filename" AudioType as 2, or folds
//    the OR into one immediate; not resolved.
//  - BLOCKER: the random/sequential pick path calls a still-unconverted
//    retail helper at 0x000B2430 (?d_000b2430@@YAXXZ, 104B, dump) through a
//    non-portable convention: eax=index count, edx=array pointer, cl=a bool
//    flag, no stack args -- not __cdecl/__thiscall/__fastcall. This reads as
//    an MSVC "static function, single call site" custom register-passing
//    optimization, only reproducible in our TU once 0x000B2430 itself is
//    converted (so its true signature and the array element layout used by
//    the cumulative-count walk in its body are known). Until then this body
//    cannot byte-match past the AT_SoundEffect/random branch.

typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	AsciiString &operator=(const AsciiString &other);
	~AsciiString();
	void concat(const AsciiString &other);

	static const AsciiString TheEmptyString;

private:
	void *m_data;
};

enum AudioType { AT_SoundEffect = 2 };

struct SoundEntry
{
	AsciiString m_filename;
	int m_weight;
};

class AudioEventInfo
{
public:
	char m_pad[0x3c];
	unsigned int m_control;             // +0x3c, bit 1 tested (AC_RANDOM)
	char m_pad2[0x4c - 0x40];
	SoundEntry *m_soundsBegin;           // +0x4c
	SoundEntry *m_soundsEnd;             // +0x50
	char m_pad3[0x30];
	AudioType m_soundType;               // +0x84
};

// BLOCKED: real convention is eax/edx/cl, not this -- see file header.
extern Int chooseCumulativeSound(Int count, const SoundEntry *arr, Bool logical);

class AudioEventRTS
{
public:
	void generateFilename(void);

	AsciiString generateFilenamePrefix(AudioType audioTypeToPlay, Bool addLength);
	void adjustForLocalization(AsciiString &filename);
	AsciiString generateFilenameExtension(AudioType audioTypeToPlay);

private:
	void *m_pad_0;                        // +0 (m_eventName etc, not modeled)
	AsciiString m_filenameToLoad;        // +4
	AudioEventInfo *m_eventInfo;         // +8
	char m_pad_c[0x42 - 0xc];
	bool m_isLogicalAudio;               // +0x42
	char m_pad_43[0x46 - 0x43];
	bool m_needsFilenameGenerated;       // +0x46
	char m_pad_47[0x58 - 0x47];
	Int m_playingAudioIndex;             // +0x58
};

void AudioEventRTS::generateFilename(void)
{
	if (!m_needsFilenameGenerated || !m_eventInfo)
		return;

	m_needsFilenameGenerated = false;

	m_filenameToLoad = generateFilenamePrefix(m_eventInfo->m_soundType, false);

	Int which = 0;

	if (m_eventInfo->m_soundType == AT_SoundEffect)
	{
		if (m_eventInfo->m_soundsBegin == m_eventInfo->m_soundsEnd)
		{
			m_filenameToLoad = AsciiString::TheEmptyString;
			return;
		}

		Int count = (Int)(m_eventInfo->m_soundsEnd - m_eventInfo->m_soundsBegin);

		if (m_eventInfo->m_control & 2)
		{
			if (count <= 1)
			{
				which = 0;
			}
			else
			{
				for (;;)
				{
					which = chooseCumulativeSound(count, m_eventInfo->m_soundsBegin, m_isLogicalAudio);
					if (which != m_playingAudioIndex || which == -1)
						break;
				}
				if (which == -1)
				{
					m_filenameToLoad = AsciiString::TheEmptyString;
					return;
				}
				m_playingAudioIndex = which;
			}
		}
		else
		{
			m_playingAudioIndex = m_playingAudioIndex + 1;
			which = m_playingAudioIndex;
		}

		m_filenameToLoad.concat(m_eventInfo->m_soundsBegin[which].m_filename);
	}
	else
	{
		m_filenameToLoad.concat(m_eventInfo->m_soundsBegin[0].m_filename);
		adjustForLocalization(m_filenameToLoad);
		return;
	}

	m_filenameToLoad.concat(generateFilenameExtension(m_eventInfo->m_soundType));
	adjustForLocalization(m_filenameToLoad);
}
