// ?d_006a2750@@YAXXZ
// partial score=0.95 date=2026-09-09
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A2750 is the MilesAudioManager implementation reached by the
// primary audio vtable's +0xB0 slot.  The slot is called by name from
// EvaUpdate.cpp and Rva003720F0AudioRefresh.cpp.  Its short wrapper protects
// the shared manager lists with the +0x95C mutex, then calls the existing
// three-argument list-search helper through retail ILT 0x00008549.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int AudioHandle;

__declspec(dllimport) int __stdcall bfmeWait1012(void *mutex, int timeout);
extern "C" __declspec(dllimport) int __stdcall Rva01358ECC(void *mutex);
extern void j_00008549(void);

class MilesAudioScopedMutex
{
public:
	__forceinline MilesAudioScopedMutex(void *mutex, int timeout)
	{
		m_held = 0;
		m_mutex = mutex;
		if (bfmeWait1012(m_mutex, timeout) != 0x102)
			m_held = 1;
	}

	__forceinline ~MilesAudioScopedMutex(void)
	{
		if (m_held)
		{
			Rva01358ECC(m_mutex);
			m_held = 0;
		}
	}

private:
	void *m_mutex;
	unsigned char m_held;
};

class MilesAudioManager
{
public:
	virtual bool isCurrentlyPlaying(AudioHandle handle);
	bool findPlaying(AudioHandle handle, void *playing, void *request);

private:
	friend class MilesAudioScopedMutex;
	char m_pad004[0x95c - 4];
	void *m_mutex;
};

bool MilesAudioManager::isCurrentlyPlaying(AudioHandle handle)
{
	unsigned char *raw = (unsigned char *)this;
	void *mutex = *(void **)(raw + 0x95c);
	MilesAudioScopedMutex guard(mutex, -1);
	typedef bool (MilesAudioManager::*FindPlaying)(AudioHandle, void *, void *);
	union
	{
		void (__cdecl *freeFunction)();
		FindPlaying memberFunction;
	} findPlaying;
	findPlaying.freeFunction = (void (__cdecl *)())::j_00008549;
	bool result = (this->*findPlaying.memberFunction)(handle, 0, 0);
	return result;
}
