// cl: /DNDEBUG /MD /EHsc
// Identity: the unique DefaultSoundEffect parser at 0xB1030 calls the audio
// factory through vtable slot +0x110, reaches 0x6AE710, and assigns this
// 0x98-byte family through ILT 0x3C6D7 -> 0xB0F00. Its INI table at
// 0x010813F8 witnesses fourteen AudioEventInfo fields, including volume+0x10.
// Canonical INIAudioEventInfo.cpp has the same parser/factory/assignment flow.
// Keep BFME layout views and unknown nested types; the Zero Hour layout differs.
// Constants here are layout witnesses, not claims about runtime INI values.
// Member names follow INI table 0x010813F8. Raw integer/volatile storage views
// preserve retail code generation, including the bit patterns of float fields.

// Retail 0x000B0D10: AudioEventInfo's default constructor.
// The vtable at 0x010818CC, the matched copy constructor at 0x000B5B10, the
// destructor at 0x000B0DF0, and BfmeThingCIA::bfmeInitCIA at 0x000B5450
// identify this body as AudioEventInfo's constructor.
// This TU keeps the byte layout local so MSVC preserves the retail stores.

struct Two
{
	volatile int value;

	__forceinline void set()
	{
		value = 2;
	}
};

struct One
{
	volatile float value;

	__forceinline void set()
	{
		value = 1.0f;
	}
};

struct AudioEventInfo
{
public:
	AudioEventInfo();

private:
	volatile int m_vft;
	volatile int m_zero;
	// Matched copy row and BFME parser diagnostic identify +0x08 as the name.
	volatile int m_name;
	volatile int m_filename;
	volatile int m_volume;
	volatile int m_volumeShift;
	volatile int m_minVolume;
	// Matched BFME parsePitchShift at 0x000AFFF0 writes +0x1C and +0x20.
	volatile int m_pitchShiftMin;
	volatile int m_pitchShiftMax;
	One m_24;
	// Matched BFME parseDelay at 0x000AFF40 writes +0x28 and +0x2C.
	volatile int m_delayMin;
	volatile int m_delayMax;
	volatile int m_limit;
	Two m_priority;
	volatile int m_type;
	volatile int m_control;
	volatile int m_sounds;
	volatile int m_44;
	volatile int m_48;
	volatile int m_4c;
	volatile int m_attackSounds;
	volatile int m_54;
	volatile int m_58;
	volatile int m_5c;
	volatile int m_decaySounds;
	volatile int m_64;
	volatile int m_68;
	volatile int m_6c;
	volatile int m_lowPassFreq;
	volatile int m_minDistance;
	volatile int m_maxDistance;
	One m_7c;
	One m_80;
	Two m_84;
	volatile int m_88;
	volatile int m_8c;
	volatile int m_90;
	volatile int m_94;
};

AudioEventInfo::AudioEventInfo()
{
	m_zero = 0;
	m_vft = 0x010818CC;
	m_name = 0;
	m_filename = 0;
	m_volume = 0x42c80000;
	m_volumeShift = 0;
	m_minVolume = 0;
	m_pitchShiftMin = 0;
	m_pitchShiftMax = 0;
	m_delayMin = 0;
	m_delayMax = 0;
	m_limit = 0x19;
	m_priority.set();
	m_type = 0;
	m_control = 0;
	m_24.set();
	m_sounds = 0;
	m_44 = 0;
	m_48 = 0;
	m_4c = 0;
	m_attackSounds = 0;
	m_54 = 0;
	m_58 = 0;
	m_5c = 0;
	m_decaySounds = 0;
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_lowPassFreq = 0;
	m_minDistance = 0x42c80000;
	m_maxDistance = 0x447a0000;
	m_7c.set();
	m_80.set();
	m_84.set();
	m_88 = -1;
	m_8c = 0;
	m_90 = 0;
	m_94 = 0;
}
