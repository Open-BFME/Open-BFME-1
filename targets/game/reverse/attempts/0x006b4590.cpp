// ?friend_forcePlayAudioEventRTS@MilesAudioManager@@UAEXPBVAudioEventRTS@@@Z
// partial score=0.2536 date=2026-10-29
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// MilesAudioManager::friend_forcePlayAudioEventRTS (retail 0x006B4590, 481 B).
//
// Identity: MilesAudioManager vtable 0x0111C0C0 slot 66 routes through ILT
// 0x000415F6 to this body (ilt_oracle CONFIRMED for this name), and it keeps
// Zero Hour's force-play flow: resolve the event info, check the sound class
// is on, copy the event, generate its filename and play info, apply the
// adjusted value keyed by the event name, AIL_quick_load_and_play the file,
// set its volume against the slot volume with pan 0.5 and remember the handle
// in m_audioForcePlayed. BFME holds the manager mutex (+0x95C) throughout and
// keeps the adjusted-value map and volume per audio slot (+0xB8, 0x1C4 apart).
//
// The layouts below are TU-local views of only the witnessed fields.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <map>
#include "ascii_string.h"

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

typedef void *HAUDIO;
extern "C" __declspec(dllimport) HAUDIO __stdcall AIL_quick_load_and_play(const char *filename, int loopCount, int wait);
extern "C" __declspec(dllimport) void __stdcall AIL_quick_set_volume(HAUDIO audio, float volume, float pan);

typedef float Real;
typedef int Int;

enum AudioPriority
{
	AP_LOWEST
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &right);
	~AudioEventRTS();

	void bfmeGenerateFilename();
	void generatePlayInfo();
	AsciiString getFilename();
	Real getPitchShift() const;
	void setAudioPriority(AudioPriority priority);
	unsigned int getSoundClass() const;

	char m_unmodelled00[0x8];
	const void *m_eventInfo;				// +0x08
	char m_unmodelled0C[0x14 - 0xc];
	AsciiString m_eventName;				// +0x14
	char m_unmodelled18[0x28 - 0x18];
	Int m_slot;								// +0x28
	char m_unmodelled2C[0x70 - 0x2c];
};

class MilesAudioScopedMutex
{
public:
	__forceinline MilesAudioScopedMutex(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		if (WaitForSingleObject(m_mutex, 0xFFFFFFFFu) != 0x102u)
			m_held = 1;
	}

	__forceinline ~MilesAudioScopedMutex(void)
	{
		if (m_held)
		{
			ReleaseMutex(m_mutex);
			m_held = 0;
		}
	}

private:
	void *m_mutex;
	unsigned char m_held;
};

namespace _STL
{
template <>
struct less<AsciiString>
{
	bool operator()(const AsciiString &a, const AsciiString &b) const { return a.compare(b) < 0; }
};
}

// The adjusted-value map's node holds the name at +0x10 and the value at
// +0x14; its find is the matched _M_find at 0x005C7770.
struct Rva005C7770Value
{
	AsciiString m_key;
	AudioPriority m_value;
};

struct Rva005C7770KeyOfValue
{
	const AsciiString &operator()(const Rva005C7770Value &x) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva005C7770Value, Rva005C7770KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva005C7770Value> > AdjustedValueTree;

struct MilesAudioSlot
{
	char m_unmodelled000[0xf4];
	Real m_volume;							// +0xF4
	char m_unmodelled0F8[0x1b8 - 0xf8];
	AdjustedValueTree m_adjustedValues;		// +0x1B8
};

#define MILES_SLOT(n) virtual void slot##n(void);

class MilesAudioManager
{
public:
	MILES_SLOT(00) MILES_SLOT(01) MILES_SLOT(02) MILES_SLOT(03) MILES_SLOT(04)
	MILES_SLOT(05) MILES_SLOT(06) MILES_SLOT(07) MILES_SLOT(08) MILES_SLOT(09)
	MILES_SLOT(10) MILES_SLOT(11) MILES_SLOT(12) MILES_SLOT(13) MILES_SLOT(14)
	MILES_SLOT(15) MILES_SLOT(16) MILES_SLOT(17) MILES_SLOT(18) MILES_SLOT(19)
	MILES_SLOT(20) MILES_SLOT(21) MILES_SLOT(22) MILES_SLOT(23) MILES_SLOT(24)
	MILES_SLOT(25) MILES_SLOT(26) MILES_SLOT(27) MILES_SLOT(28) MILES_SLOT(29)
	MILES_SLOT(30) MILES_SLOT(31) MILES_SLOT(32) MILES_SLOT(33) MILES_SLOT(34)
	MILES_SLOT(35) MILES_SLOT(36) MILES_SLOT(37) MILES_SLOT(38) MILES_SLOT(39)
	MILES_SLOT(40) MILES_SLOT(41) MILES_SLOT(42)
	virtual void getInfoForAudioEvent(const AudioEventRTS *eventToFindAndFill);
	MILES_SLOT(44) MILES_SLOT(45)
	virtual bool isOn(unsigned int soundClass);
	MILES_SLOT(47) MILES_SLOT(48) MILES_SLOT(49) MILES_SLOT(50) MILES_SLOT(51)
	MILES_SLOT(52) MILES_SLOT(53) MILES_SLOT(54) MILES_SLOT(55) MILES_SLOT(56)
	MILES_SLOT(57) MILES_SLOT(58) MILES_SLOT(59) MILES_SLOT(60) MILES_SLOT(61)
	MILES_SLOT(62) MILES_SLOT(63) MILES_SLOT(64) MILES_SLOT(65)
	virtual void friend_forcePlayAudioEventRTS(const AudioEventRTS *eventToPlay);

	void rva006B15A0(const AsciiString *filename);
	void rva006AF840();

private:
	char m_unmodelled004[0xb8 - 0x4];
	MilesAudioSlot m_slots[1];				// +0xB8, 0x1C4 apart
	char m_unmodelled27C[0x95c - 0xb8 - sizeof(MilesAudioSlot)];
	void *m_mutex;							// +0x95C
	char m_unmodelled960[0x9bc - 0x960];
	_STL::list<HAUDIO> m_audioForcePlayed;	// +0x9BC
};

#undef MILES_SLOT

// ?friend_forcePlayAudioEventRTS@MilesAudioManager@@UAEXPBVAudioEventRTS@@@Z
void MilesAudioManager::friend_forcePlayAudioEventRTS(const AudioEventRTS *eventToPlay)
{
	MilesAudioScopedMutex scopedLock(m_mutex);

	if (!eventToPlay->m_eventInfo)
	{
		getInfoForAudioEvent(eventToPlay);
		if (!eventToPlay->m_eventInfo)
			return;
	}

	if (!isOn(eventToPlay->getSoundClass()))
		return;

	AudioEventRTS event = *eventToPlay;

	event.bfmeGenerateFilename();
	event.generatePlayInfo();

	AdjustedValueTree &values = m_slots[event.m_slot].m_adjustedValues;
	AdjustedValueTree::iterator it = values.find(event.m_eventName);
	if (it != values.end())
	{
		AudioPriority *value = &it->m_value;
		if (value)
			event.setAudioPriority(*value);
	}

	AsciiString fileToPlay = event.getFilename();
	HAUDIO haud = AIL_quick_load_and_play(fileToPlay.str(), 1, 0);
	if (haud)
	{
		rva006B15A0(&fileToPlay);
		rva006AF840();
		AIL_quick_set_volume(haud, m_slots[event.m_slot].m_volume * event.getPitchShift(), 0.5f);
		m_audioForcePlayed.push_back(haud);
	}
}
