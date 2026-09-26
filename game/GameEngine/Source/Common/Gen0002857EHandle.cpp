// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?handle@Gen0002857E@@QAEXXZ
// Mutex-guarded increment of the counter at +0x34. The handle lives at
// [this+4]+0x48. WaitForSingleObject with INFINITE; ReleaseMutex only when
// the wait did not return WAIT_TIMEOUT.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Gen0002857EOwner
{
public:
	char m_pad[0x48];
	void *m_mutex;
};

class Gen0002857E
{
public:
	void handle();

private:
	char m_pad04[4];
	Gen0002857EOwner *m_owner;
	char m_pad34[0x34 - 8];
	int m_count;
};

void Gen0002857E::handle()
{
	void *handle = m_owner->m_mutex;
	char ok = 0;
	if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
		ok = 1;
	m_count = m_count + 1;
	if (ok)
		ReleaseMutex(handle);
}
