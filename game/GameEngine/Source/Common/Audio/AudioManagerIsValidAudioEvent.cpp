// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// AudioManager::isValidAudioEvent, retail 0x0069CFB0 (189 bytes).
//
// Identity: AudioManager vtable 0x0111C0C0 slot 23 (+0x5C) reaches this body
// through ILT 0x00041952, and the body calls slot 43 (+0xAC), the matched
// AudioManager::getInfoForAudioEvent at 0x00699FD0. The flow is the Zero Hour
// GameAudio.cpp body under BFME's manager mutex (+0x95C) with a null guard.
//
// The guard parks the wait result in a named status local before testing it,
// as MilesAudioManagerIsCurrentlyPlaying.cpp does. Testing the call result
// directly swaps the this/event registers (ESI/EDI) against retail.

#include "ascii_string.h"

typedef bool Bool;

template<> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

class AudioEventInfo;

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

	const AsciiString &getEventName(void) const { return m_eventName; }
	const AudioEventInfo *getAudioEventInfo(void) const { return m_eventInfo; }

private:
	char m_pad004[4];
	AudioEventInfo *m_eventInfo;
	char m_pad00C[8];
	AsciiString m_eventName;
};

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class AudioManagerMutex
{
public:
	AudioManagerMutex(void *mutex)
	{
		m_held = false;
		m_mutex = mutex;
		unsigned long status = WaitForSingleObject(m_mutex, 0xFFFFFFFFu);
		if (status != 0x102u)
			m_held = true;
	}

	~AudioManagerMutex()
	{
		if (m_held)
		{
			ReleaseMutex(m_mutex);
			m_held = false;
		}
	}

private:
	void *m_mutex;
	bool m_held;
};

class AudioManager
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22();
	virtual Bool isValidAudioEvent(const AudioEventRTS *eventToCheck) const;	// slot 23, +0x5C
	virtual void vslot24(); virtual void vslot25(); virtual void vslot26(); virtual void vslot27();
	virtual void vslot28(); virtual void vslot29(); virtual void vslot30(); virtual void vslot31();
	virtual void vslot32(); virtual void vslot33(); virtual void vslot34(); virtual void vslot35();
	virtual void vslot36(); virtual void vslot37(); virtual void vslot38(); virtual void vslot39();
	virtual void vslot40(); virtual void vslot41(); virtual void vslot42();
	virtual void getInfoForAudioEvent(const AudioEventRTS *eventToFindAndFill) const;	// slot 43, +0xAC

private:
	char m_pad004[0x95c - 4];
	void *m_mutex;
};

Bool AudioManager::isValidAudioEvent(const AudioEventRTS *eventToCheck) const
{
	AudioManagerMutex guard(m_mutex);
	if (!eventToCheck)
		return false;

	if (eventToCheck->getEventName().isEmpty())
		return false;

	getInfoForAudioEvent(eventToCheck);

	return (eventToCheck->getAudioEventInfo() != 0);
}
