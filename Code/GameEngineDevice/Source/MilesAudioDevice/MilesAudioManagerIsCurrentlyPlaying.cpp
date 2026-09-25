// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A2750 is MilesAudioManager::isCurrentlyPlaying: primary
// MilesAudioManager vtable 0x0111C0C0 slot +0xB0 routes through ILT
// 0x0003ADB9 to this body, and EvaUpdate.cpp / Rva003720F0AudioRefresh.cpp
// call the slot by name.  It takes the manager mutex (+0x95C) and asks the
// playing-list search at 0x006A20D0 (reads the +0x9C8/+0x9CC/+0x9D0 playing
// lists, reached through ILT 0x00008549) with both out pointers null.
//
// The guard keeps the Zero Hour ScopedMutex shape: the wait result goes into
// a named status local before it is tested.  Testing the call result
// directly swaps the this/mutex registers (ESI/EDI) against retail.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

typedef bool Bool;
typedef unsigned int AudioHandle;

class MilesAudioScopedMutex
{
public:
	MilesAudioScopedMutex(void *mutex)
	{
		m_held = false;
		m_mutex = mutex;
		unsigned long status = WaitForSingleObject(m_mutex, 0xFFFFFFFFu);
		if (status != 0x102u)
			m_held = true;
	}

	~MilesAudioScopedMutex()
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

class MilesAudioManager
{
public:
	virtual Bool isCurrentlyPlaying(AudioHandle handle);
	Bool rva006A20D0(AudioHandle handle, void *out1, void *out2);

private:
	char m_pad004[0x95c - 4];
	void *m_mutex;
};

Bool MilesAudioManager::isCurrentlyPlaying(AudioHandle handle)
{
	MilesAudioScopedMutex lock(m_mutex);
	return rva006A20D0(handle, 0, 0);
}
