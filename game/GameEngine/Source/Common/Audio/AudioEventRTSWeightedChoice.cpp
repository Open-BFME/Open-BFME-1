// Address-derived static helper; retail debug file identifies AudioEventRTS.cpp.
// count is total weight, not vector length. Entries are 8B (name pointer, weight).
// MSVC chooses EAX=count, EDX=range, CL=logical when the body is visible.
// The write barrier emits no bytes; it preserves retail separate zero-return tails.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

// Retail inlines the AsciiString concat and clear at their call sites.

template <> inline void StringBase<char>::concat(const StringBase<char> &s)
{
	concat(s.str(), s.getLength());
}

extern int GetGameLogicRandomValue(int,int,char*,int);
extern int GetGameAudioRandomValue(int,int,char*,int);
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
struct WeightedSoundB2430 { AsciiString name; unsigned weight; };
struct WeightedSoundRangeB2430 { WeightedSoundB2430 *begin,*end,*capacity; };
static __declspec(noinline) int bfmeWeightedChoiceB2430(unsigned totalWeight,const WeightedSoundRangeB2430*range,bool useLogicRandom) {
 if (!(totalWeight>0)) return -1;
 unsigned remainingWeight;
 if(useLogicRandom) remainingWeight=GetGameLogicRandomValue(0,totalWeight-1,"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",55);
 else remainingWeight=GetGameAudioRandomValue(0,totalWeight-1,"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",59);
 WeightedSoundB2430 *soundEntry=range->begin;
 if(soundEntry!=range->end) { do {
  if(remainingWeight<soundEntry->weight) goto found;
  remainingWeight-=soundEntry->weight; ++soundEntry;
 } while(soundEntry!=range->end);
 return 0; }
found: if(soundEntry==range->end){_WriteBarrier();return 0;}
 return soundEntry-range->begin;
}
extern float GetGameAudioRandomValueReal(float lo, float hi, char *file, int line);
#define AUDIO_EVENT_RTS_FILE "F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp"

enum AudioType
{
	AT_Music = 0,
	AT_Streaming = 1,
	AT_SoundEffect = 2
};

__forceinline AudioType retainAudioType(AudioType type)
{
	return type;
}

enum PortionToPlay
{
	PP_Attack = 0,
	PP_Sound = 1
};

// The out-of-line accessors at 0x000AF8A0 and 0x000AF8B0 return the attack and
// decay weighted-sound vectors at AudioEventInfo+0x50 and +0x60.
class Rva000AF8A0FieldAddress
{
public:
	unsigned char *get();
};

class Rva000AF8B0
{
public:
	void *fieldAt60() const;
};

class AudioEventInfo
{
public:
	const WeightedSoundRangeB2430 *getAttackSounds() { return (const WeightedSoundRangeB2430 *)((Rva000AF8A0FieldAddress *)this)->get(); }
	const WeightedSoundRangeB2430 *getDecaySounds() { return (const WeightedSoundRangeB2430 *)((Rva000AF8B0 *)this)->fieldAt60(); }

	char m_pad00[0x14];
	float m_volumeShift;					// +0x14
	char m_pad18[4];
	float m_pitchShiftMin;					// +0x1C
	float m_pitchShiftMax;					// +0x20
	char m_pad24[0x5c - 0x24];
	unsigned m_attackTotalWeight;				// +0x5C
	char m_pad60[0x6c - 0x60];
	unsigned m_decayTotalWeight;				// +0x6C
	char m_pad70[0x84 - 0x70];
	AudioType m_soundType;					// +0x84
};

class AudioEventRTS
{
public:
	// Inline boundaries that retail's register choices need: reading the event
	// info through this accessor, and the sound type through retainAudioType
	// (as AudioEventRTSAdjustForLocalization.cpp does), put each pointer chain
	// in EAX the way retail does.
	__forceinline const AudioEventInfo *peekEventInfo(void) const
	{
		return m_eventInfo;
	}

	AsciiString generateFilenamePrefix(AudioType audioTypeToPlay, bool localized);
	AsciiString generateFilenameExtension(AudioType audioTypeToPlay);
	void generatePlayInfo();

protected:
	void adjustForLocalization(AsciiString &strToAdjust);

private:
	char m_pad00[8];
	AudioEventInfo *m_eventInfo;				// +0x08
	char m_pad0C[0x18 - 0x0c];
	AsciiString m_attackName;				// +0x18
	AsciiString m_decayName;				// +0x1C
	char m_pad20[0x42 - 0x20];
	bool m_isLogicalAudio;					// +0x42
	char m_pad43[0x4c - 0x43];
	float m_pitchShift;					// +0x4C
	float m_volumeShift;					// +0x50
	char m_pad54[0x60 - 0x54];
	int m_portionToPlayNext;				// +0x60
};

// ?generatePlayInfo@AudioEventRTS@@QAEXXZ
// Retail 0x000B3C60, 664 bytes: the Zero Hour twin (AudioEventRTS.cpp) with
// BFME's weighted attack/decay choice. It shares this TU with the static
// weighted-choice helper so the helper keeps retail's EAX/EDX/CL convention.
void AudioEventRTS::generatePlayInfo()
{
	float pitchShiftMax = m_eventInfo->m_pitchShiftMax;
	float pitchShiftMin = m_eventInfo->m_pitchShiftMin;
	m_pitchShift = GetGameAudioRandomValueReal(pitchShiftMin, pitchShiftMax, AUDIO_EVENT_RTS_FILE, 641);
	m_volumeShift = GetGameAudioRandomValueReal(peekEventInfo()->m_volumeShift + 1.0f, 1.0f, AUDIO_EVENT_RTS_FILE, 642);

	if (m_eventInfo->m_soundType == AT_SoundEffect)
	{
		m_portionToPlayNext = PP_Attack;
		unsigned attackTotalWeight = m_eventInfo->m_attackTotalWeight;
		int attackToPlay = bfmeWeightedChoiceB2430(attackTotalWeight, m_eventInfo->getAttackSounds(), m_isLogicalAudio);
		if (attackToPlay >= 0)
		{
			m_attackName = generateFilenamePrefix(retainAudioType(peekEventInfo()->m_soundType), false);
			const WeightedSoundB2430 *attackSounds = m_eventInfo->getAttackSounds()->begin;
			m_attackName.concat(attackSounds[attackToPlay].name);
			m_attackName.concat(generateFilenameExtension(retainAudioType(peekEventInfo()->m_soundType)));
			adjustForLocalization(m_attackName);
		}
		else
		{
			m_portionToPlayNext = PP_Sound;
		}

		unsigned decayTotalWeight = m_eventInfo->m_decayTotalWeight;
		int decayToPlay = bfmeWeightedChoiceB2430(decayTotalWeight, m_eventInfo->getDecaySounds(), m_isLogicalAudio);
		if (decayToPlay >= 0)
		{
			m_decayName = generateFilenamePrefix(retainAudioType(peekEventInfo()->m_soundType), false);
			const WeightedSoundB2430 *decaySounds = m_eventInfo->getDecaySounds()->begin;
			m_decayName.concat(decaySounds[decayToPlay].name);
			m_decayName.concat(generateFilenameExtension(retainAudioType(peekEventInfo()->m_soundType)));
			adjustForLocalization(m_decayName);
		}
		else
		{
			m_decayName.clear();
		}
	}
	else
	{
		m_portionToPlayNext = PP_Sound;
	}

	m_isLogicalAudio = false;
}

// ?forceWeightedChoiceB2430@@YAHIPBUWeightedSoundRangeB2430@@_N@Z absent-from-retail
// Absent-from-retail callsite to expose the static helper to MSVC optimization.
int forceWeightedChoiceB2430(unsigned count, const WeightedSoundRangeB2430*range,bool logical) { return bfmeWeightedChoiceB2430(count,range,logical); }
