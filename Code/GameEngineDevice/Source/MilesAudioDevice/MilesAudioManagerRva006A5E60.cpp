// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x006A5E60 (146 B), a non-virtual MilesAudioManager member.  Its
// only caller, PlayingAudio::~PlayingAudio (0x006BA030), calls it
// through ILT 0x000207A2 on the TheAudio singleton (0x012ED668) with the
// dying PlayingAudio as the one stack argument (ret 4).  m_type (+0xc) is
// the field 0x006A59F0 switches on, as Zero Hour releasePlayingAudio does
// on PlayingAudio::m_type.  Under the manager
// mutex (+0x95c) it hands the audio to 0x006A59F0 (the ledger's
// MilesAudioManager::rva006A59F0, ILT 0x0002669D) and, for a type-2 audio,
// clears dword +0x10 of the 0x40-byte slot the audio's +0x8 index selects
// in the array at +0xb44 (the 0x006A5570 scan walks the same array with the
// count at +0xb48).  The unwind funclet releases the lock through the
// family's out-of-line guard destructor at 0x006915E0.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class PlayingAudio
{
public:
	char m_pad000[8];
	int m_dword8;
	int m_type;
};

struct Rva006A5E60Slot
{
	char m_pad00[0x10];
	void *m_dword10;
	char m_pad14[0x40 - 0x14];
};

// The WaitForSingleObject status goes through a named local, as in the
// 0x006B4310 guard; the destructor clears the flag like 0x006915E0 does.
class Rva006A5E60MutexGuard
{
public:
	Rva006A5E60MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		unsigned long status = WaitForSingleObject(handle, 0xFFFFFFFF);
		if (status != 0x102)
			m_owned = 1;
	}

	~Rva006A5E60MutexGuard()
	{
		if (m_owned)
		{
			ReleaseMutex(m_handle);
			m_owned = 0;
		}
	}

private:
	void *m_handle;
	char m_owned;
};

class MilesAudioManager
{
public:
	void rva006A59F0(PlayingAudio *release);
	void rva006A5E60(PlayingAudio *audio);

private:
	char m_pad000[0x95c];
	void *m_mutex;
	char m_pad960[0xb44 - 0x960];
	Rva006A5E60Slot *m_slotsB44;
};

void MilesAudioManager::rva006A5E60(PlayingAudio *audio)
{
	Rva006A5E60MutexGuard guard(m_mutex);
	rva006A59F0(audio);
	if (audio->m_type == 2)
		m_slotsB44[audio->m_dword8].m_dword10 = 0;
}
