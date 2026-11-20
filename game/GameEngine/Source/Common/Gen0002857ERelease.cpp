// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?release@Gen0002857E@@QAEXXZ
// Mutex-guarded decrement of the counter at +0x34. When the count hits
// zero, stamp +0x38 with AIL_ms_count and notify the owner at [this+4].

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) unsigned int __stdcall AIL_ms_count(void);



// The owner notification goes through ILT 0x00008A62, the ledger's 5-byte row
// ?j_00008a62@@YAXXZ (game/gen_small/thunks_003.cpp), jmp to 0x00693EC0, as
// tools/callees.py 0x6ba220 136 prints.  Nothing defines the pinned
// ?notify@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z, so the call names the
// thunk through a raw pointer bridge that keeps the thiscall shape.
void j_00008a62();
class Gen0002857EOwner
{
public:
	char m_pad[0x48];
	void *m_mutex;
};

class Gen0002857EMutexGuard
{
public:
	Gen0002857EMutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Gen0002857EMutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Gen0002857E
{
public:
	void release();

private:
	char m_pad04[4];
	Gen0002857EOwner *m_owner;
	char m_pad34[0x34 - 8];
	volatile int m_count;
	unsigned int m_stamp;
};

void Gen0002857E::release()
{
	Gen0002857EMutexGuard guard(m_owner->m_mutex);
	m_count--;
	if (m_count == 0)
	{
		m_stamp = AIL_ms_count();
		union
		{
			void (*raw)(void);
			void (Gen0002857EOwner::*typed)(Gen0002857E *);
		} notify;
		notify.raw = &j_00008a62;
		(m_owner->*notify.typed)(this);
	}
}
