// ?d_000b3970@@YAXXZ
// partial score=0.75 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: AudioEventRTS::generateFilename, retail 0x000B3970, 400B.
// The BFME AudioEventInfo sound range contains eight-byte weighted entries;
// its field getter and the weighted-choice helper are pinned from the direct
// retail call sites rather than inferred from the Zero Hour vector typedef.

extern int GetGameLogicRandomValue(int, int, char *, int);
extern int GetGameAudioRandomValue(int, int, char *, int);
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
extern void j_000017ee(void);
extern void j_000067d5(void);
extern void j_0002b855(void);
extern void j_0002dfb5(void);
extern void j_0003b769(void);

template <typename T>
class StringBase
{
public:
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

	void concat(const StringBase<T> &other);

	~StringBase()
	{
		releaseBuffer();
	}

private:
	void set(const StringBase<T> &other);
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::operator=(other);
		return *this;
	}

	void concat(const AsciiString &other)
	{
		StringBase<char>::concat(other);
	}

	__forceinline void concatViaThunk(const AsciiString &other)
	{
		typedef void (StringBase<char>::*ConcatThunk)(const StringBase<char> &);
		union
		{
			void (*function)(void);
			ConcatThunk member;
		} thunk;
		thunk.function = j_0002b855;
		(this->*thunk.member)(other);
	}
};

struct WeightedSoundB2430
{
	AsciiString m_filename;
	unsigned m_weight;
};

struct WeightedSoundRangeB2430
{
	WeightedSoundB2430 *m_begin;
	WeightedSoundB2430 *m_end;
	WeightedSoundB2430 *m_capacity;
};

static __declspec(noinline) int bfmeWeightedChoiceB2430(
	unsigned count, const WeightedSoundRangeB2430 *range, bool logical)
{
	if (!(count > 0))
		return -1;

	unsigned value;
	--count;
	if (logical)
		value = GetGameLogicRandomValue(0, count,
			"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",
			55);
	else
		value = GetGameAudioRandomValue(0, count,
			"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",
			59);

	WeightedSoundB2430 *it = range->m_begin;
	if (it != range->m_end)
	{
		do
		{
			if (value < it->m_weight)
				goto found;
			value -= it->m_weight;
			++it;
		}
		while (it != range->m_end);
		return 0;
	}

found:
	if (it == range->m_end)
	{
		_WriteBarrier();
		return 0;
	}
	return (int)(it - range->m_begin);
}

enum AudioType
{
	AT_Music = 0,
	AT_Streaming = 1,
	AT_SoundEffect = 2,
	AT_AmbientStream = 3,
	AT_SoundEffectAlt = 4
};

class AudioEventInfo
{
public:
	char m_pad0[0x0c];
	AsciiString m_filename;
	char m_pad1[0x3c - 0x10];
	unsigned m_control;
	WeightedSoundRangeB2430 m_sounds;
	unsigned m_totalWeight;
	char m_pad2[0x84 - 0x50];
	AudioType m_soundType;

	const AsciiString &getFilename() const;
};

class AudioEventRTS
{
public:
	AsciiString generateFilenamePrefix(AudioType audioTypeToPlay, bool localized);
	AsciiString generateFilenameExtension(AudioType audioTypeToPlay);
	void adjustForLocalization(AsciiString &filename);

	__forceinline void generateFilenameExtensionViaThunk(
		AudioType audioTypeToPlay, AsciiString &filename)
	{
		typedef AsciiString (AudioEventRTS::*ExtensionThunk)(AudioType);
		union
		{
			void (*function)(void);
			ExtensionThunk member;
		} thunk;
		thunk.function = j_000067d5;
		filename.concatViaThunk((this->*thunk.member)(audioTypeToPlay));
	}

	__forceinline void adjustForLocalizationViaThunk(AsciiString &filename)
	{
		typedef void (AudioEventRTS::*AdjustThunk)(AsciiString &);
		union
		{
			void (*function)(void);
			AdjustThunk member;
		} thunk;
		thunk.function = j_0002dfb5;
		(this->*thunk.member)(filename);
	}


private:
	char m_pad0[4];
	AsciiString m_filenameToLoad;
	AudioEventInfo *m_eventInfo;
	char m_pad1[0x42 - 0x0c];
	bool m_isLogicalAudio;
	char m_pad2[0x46 - 0x43];
	bool m_needsFilenameGenerated;
	char m_pad3[0x58 - 0x47];
	int m_playingAudioIndex;

public:
	void generateFilename();
};

void AudioEventRTS::generateFilename()
{
	if (!m_needsFilenameGenerated || !m_eventInfo)
		return;

	AsciiString *filenameToLoad = &m_filenameToLoad;
	WeightedSoundRangeB2430 *sounds;
	unsigned totalWeight;
	m_needsFilenameGenerated = false;
	*filenameToLoad = generateFilenamePrefix(m_eventInfo->m_soundType, false);
	unsigned which = 0;

	if (m_eventInfo->m_soundType != AT_SoundEffect)
	{
		filenameToLoad->concatViaThunk(m_eventInfo->getFilename());
		adjustForLocalizationViaThunk(*filenameToLoad);
		return;
	}

	typedef WeightedSoundRangeB2430 *(AudioEventInfo::*SoundsThunk)(void);
	union
	{
		void (*function)(void);
		SoundsThunk member;
	} soundsThunk;
	soundsThunk.function = j_000017ee;
	sounds = (m_eventInfo->*soundsThunk.member)();
	WeightedSoundB2430 *begin = sounds->m_begin;
	WeightedSoundB2430 *end = sounds->m_end;
	totalWeight = m_eventInfo->m_totalWeight;
	if (!totalWeight || begin == end)
		goto empty_filename;

	unsigned count = (unsigned)(end - begin);
	if (m_eventInfo->m_control & 2)
	{
		if (count <= 1)
			which = 0;
		else
		{
				do
			{
				which = (unsigned)bfmeWeightedChoiceB2430(
					totalWeight,
					sounds,
					m_isLogicalAudio);
			}
			while (which == m_playingAudioIndex);
			if (which == (unsigned)-1)
				goto empty_filename;
			m_playingAudioIndex = which;
		}
	}
	else
	{
		which = ++m_playingAudioIndex;
		which %= count;
	}

	filenameToLoad->concatViaThunk(begin[which].m_filename);
	generateFilenameExtensionViaThunk(m_eventInfo->m_soundType, *filenameToLoad);
	adjustForLocalizationViaThunk(*filenameToLoad);
	return;

empty_filename:
	*filenameToLoad = *(const AsciiString *)0x01336E50;
}
