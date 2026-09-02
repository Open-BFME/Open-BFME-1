// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded increment of a counter at +0x84. WaitForSingleObject on
// the handle at +0x95c with INFINITE; ReleaseMutex only when the wait
// did not return WAIT_TIMEOUT. Returns the previous counter value.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Open269A220
{
public:
	int increment();

private:
	char m_pad84[0x84];
	int m_count;
	char m_pad95c[0x95c - 0x88];
	void *m_mutex;
};

// ?increment@Open269A220@@QAEHXZ
int Open269A220::increment()
{
	void *handle = m_mutex;
	char ok = 0;
	if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
		ok = 1;
	int old = m_count;
	m_count = old + 1;
	if (ok)
		ReleaseMutex(handle);
	return old;
}
