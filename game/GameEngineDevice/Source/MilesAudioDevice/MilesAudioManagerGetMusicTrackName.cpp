// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
// ?getMusicTrackName@MilesAudioManager@@UBE?AVAsciiString@@XZ
// Retail 0x0069D920, 277 bytes (ret 4 at +0x112). MilesAudioManager vtable
// 0x0111C0C0 slot 34; ilt_oracle CONFIRMS the name at this address (exact).
// The body follows Zero Hour's MilesAudioManager::getMusicTrackName
// (GeneralsMD/Code/GameEngineDevice/Source/MilesAudioDevice/
// MilesAudioManager.cpp): under the +0x95C mutex it reports the first queued
// AR_Play request whose pending event is music, else the current stream's
// event name, else the empty string. BFME adds the event's +0x28 match
// against this+0x604 and replaces Zero Hour's playing-stream loop with the
// slot lookup at 0x0069D620 (ILT 0x0001815B, pinned on the
// Rva0069F740Owner view of this object, see Rva0069F740Check.cpp).
// Field names past Zero Hour's are address-derived. Loading the slot index
// into a local before the call gives retail's ECX/EDX argument registers.
#include "ascii_string.h"

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

struct AudioEventInfo
{
	char m_pad00[0x84];
	int m_soundType;
};

struct AudioEventRTS
{
	char m_pad00[8];
	AudioEventInfo *m_eventInfo;
	char m_pad0c[0x14 - 0x0c];
	AsciiString m_eventName;
	char m_pad18[0x28 - 0x18];
	int m_x28;

	const AudioEventInfo *getAudioEventInfo() const { return m_eventInfo; }
	const AsciiString &getEventName() const { return m_eventName; }
};

struct AudioRequest
{
	int m_request;
	AudioEventRTS *m_pendingEvent;
};

struct PlayingAudio
{
	char m_pad00[0x14];
	AudioEventRTS *m_audioEventRTS;
};

template <class T> struct ListNode
{
	ListNode *m_next;
	ListNode *m_prev;
	T m_data;
};

struct Rva0069F740Ref { ListNode<PlayingAudio *> *m_node; };

class Rva0069F740Owner
{
public:
	Rva0069F740Ref getSlot(int group, int inner);
};

class Rva0069F740Lock
{
public:
	Rva0069F740Lock(void *handle)
	{
		unsigned char z = 0;
		m_held = z;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xffffffffu) != 0x102u)
			m_held = 1;
	}
	~Rva0069F740Lock()
	{
		if (m_held)
			ReleaseMutex(m_handle);
	}
	void *m_handle;
	unsigned char m_held;
};

enum { AR_Play = 0 };
enum { AT_Music = 0 };

class MilesAudioManager
{
public:
	virtual AsciiString getMusicTrackName(void) const;

	char m_pad04[0x4c - 4];
	ListNode<AudioRequest *> *m_audioRequests;
	char m_pad50[0x604 - 0x50];
	int m_x604;
	char m_pad608[0x95c - 0x608];
	void *m_mutex;
	char m_pad960[0x9d0 - 0x960];
	ListNode<PlayingAudio *> *m_sentinel;
	char m_pad9d4[0xac4 - 0x9d4];
	int m_current[3];
};

AsciiString MilesAudioManager::getMusicTrackName(void) const
{
	Rva0069F740Lock lock(m_mutex);
	ListNode<AudioRequest *> *ait;
	for (ait = m_audioRequests->m_next; ait != m_audioRequests; ait = ait->m_next) {
		if (ait->m_data->m_request != AR_Play) {
			continue;
		}
		if (!ait->m_data->m_pendingEvent) {
			continue;
		}
		if (ait->m_data->m_pendingEvent->m_x28 == m_x604 &&
			ait->m_data->m_pendingEvent->getAudioEventInfo()->m_soundType == AT_Music) {
			return ait->m_data->m_pendingEvent->getEventName();
		}
	}

	int inner = m_current[m_x604];
	ListNode<PlayingAudio *> *it = ((Rva0069F740Owner *)this)->getSlot(m_x604, inner).m_node;
	if (it != m_sentinel) {
		return it->m_data->m_audioEventRTS->getEventName();
	}
	return AsciiString::TheEmptyString;
}
