// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Identity: the unique DefaultSoundEffect parser at 0xB1030 calls the audio
// factory through vtable slot +0x110, reaches 0x6AE710, and assigns this
// 0x98-byte family through ILT 0x3C6D7 -> 0xB0F00. Its INI table at
// 0x010813F8 witnesses fourteen AudioEventInfo fields, including volume+0x10.
// Canonical INIAudioEventInfo.cpp has the same parser/factory/assignment flow.
// Keep BFME layout views and unknown nested types; the Zero Hour layout differs.
// Constants here are layout witnesses, not claims about runtime INI values.
// Member names follow INI table 0x010813F8. Raw integer/volatile storage views
// preserve retail code generation, including the bit patterns of float fields.
// stlport

// Retail 0x000B0F00, 243 bytes.  This is the copy-assignment body for the
// two-slot BFME audio-info family whose constructor at 0x000B0D10 installs
// vtable 0x010818CC and whose destructor at 0x000B0DF0 tears down these same
// two strings and four vectors.  The assignment deliberately leaves the
// polymorphic prefix untouched, as retail does; this TU emits no vtable.

#include <vector>

#include "ascii_string.h"

struct Gen_t_000b0c00_p8cd
{
	int a[2];
	Gen_t_000b0c00_p8cd();
	Gen_t_000b0c00_p8cd(const Gen_t_000b0c00_p8cd &other);
	~Gen_t_000b0c00_p8cd();
	Gen_t_000b0c00_p8cd &operator=(const Gen_t_000b0c00_p8cd &other);
};

struct Gen_t_000b0560_p8pod
{
	int a[2];
};

// Layout/codegen surrogate for the opaque polymorphic prefix; no recovered
// real base-class identity is claimed. No external rows or pins use this type.
class AudioEventInfoOpaqueBase
{
	public:
		AudioEventInfoOpaqueBase() : m_zero(0) {}
		AudioEventInfoOpaqueBase(const AudioEventInfoOpaqueBase &) : m_zero(0) {}
		virtual ~AudioEventInfoOpaqueBase() {}

	private:
		int m_zero;
};

struct AudioEventInfo : public AudioEventInfoOpaqueBase
{
	public:
		AudioEventInfo(const AudioEventInfo &other);
		virtual ~AudioEventInfo();
		AudioEventInfo &operator=(const AudioEventInfo &other);

	private:
		AsciiString m_name;
		AsciiString m_filename;
		int m_volume;
		int m_volumeShift;
		int m_minVolume;
		// Matched BFME parsePitchShift at 0x000AFFF0 writes +0x1C and +0x20.
		int m_pitchShiftMin;
		int m_pitchShiftMax;
		int m_word24;
		// Matched BFME parseDelay at 0x000AFF40 writes +0x28 and +0x2C.
		int m_delayMin;
		int m_delayMax;
		int m_limit;
		int m_priority;
		int m_type;
		int m_control;
		_STL::vector<Gen_t_000b0c00_p8cd> m_sounds;
		int m_word4c;
		_STL::vector<Gen_t_000b0c00_p8cd> m_attackSounds;
		int m_word5c;
		_STL::vector<Gen_t_000b0c00_p8cd> m_decaySounds;
		int m_word6c;
		int m_lowPassFreq;
		int m_minDistance;
		int m_maxDistance;
		int m_word7c;
		int m_word80;
		int m_word84;
		int m_word88;
		_STL::vector<Gen_t_000b0560_p8pod> m_vector8c;
};

AudioEventInfo::AudioEventInfo(const AudioEventInfo &other)
	: AudioEventInfoOpaqueBase(other),
	  m_name(other.m_name),
	  m_filename(other.m_filename),
	  m_volume(other.m_volume),
	  m_volumeShift(other.m_volumeShift),
	  m_minVolume(other.m_minVolume),
	  m_pitchShiftMin(other.m_pitchShiftMin),
	  m_pitchShiftMax(other.m_pitchShiftMax),
	  m_word24(other.m_word24),
	  m_delayMin(other.m_delayMin),
	  m_delayMax(other.m_delayMax),
	  m_limit(other.m_limit),
	  m_priority(other.m_priority),
	  m_type(other.m_type),
	  m_control(other.m_control),
	  m_sounds(other.m_sounds),
	  m_word4c(other.m_word4c),
	  m_attackSounds(other.m_attackSounds),
	  m_word5c(other.m_word5c),
	  m_decaySounds(other.m_decaySounds),
	  m_word6c(other.m_word6c),
	  m_lowPassFreq(other.m_lowPassFreq),
	  m_minDistance(other.m_minDistance),
	  m_maxDistance(other.m_maxDistance),
	  m_word7c(other.m_word7c),
	  m_word80(other.m_word80),
	  m_word84(other.m_word84),
	  m_word88(other.m_word88),
	  m_vector8c(other.m_vector8c)
{
}

AudioEventInfo &AudioEventInfo::operator=(const AudioEventInfo &other)
{
	m_name = other.m_name;
	m_filename = other.m_filename;
	m_volume = other.m_volume;
	m_volumeShift = other.m_volumeShift;
	m_minVolume = other.m_minVolume;
	m_pitchShiftMin = other.m_pitchShiftMin;
	m_pitchShiftMax = other.m_pitchShiftMax;
	m_word24 = other.m_word24;
	m_delayMin = other.m_delayMin;
	m_delayMax = other.m_delayMax;
	m_limit = other.m_limit;
	m_priority = other.m_priority;
	m_type = other.m_type;
	m_control = other.m_control;
	m_sounds = other.m_sounds;
	m_word4c = other.m_word4c;
	m_attackSounds = other.m_attackSounds;
	m_word5c = other.m_word5c;
	m_decaySounds = other.m_decaySounds;
	m_word6c = other.m_word6c;
	m_lowPassFreq = other.m_lowPassFreq;
	m_minDistance = other.m_minDistance;
	m_maxDistance = other.m_maxDistance;
	m_word7c = other.m_word7c;
	m_word80 = other.m_word80;
	m_word84 = other.m_word84;
	m_word88 = other.m_word88;
	m_vector8c = other.m_vector8c;
	return *this;
}
