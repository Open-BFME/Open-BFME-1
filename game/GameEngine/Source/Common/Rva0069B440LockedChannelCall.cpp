// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded thiscall into channel block at this+0xB8+index*0x1C4.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);

class Rva0069B440Block
{
public:
	void apply(void *a, void *b);
};

class Rva0069B440Owner
{
public:
	void call(void *a, void *b, int index);

	char m_pad0[0x95c];
	void *m_mutex;
};

void Rva0069B440Owner::call(void *a, void *b, int index)
{
	void *mutex = m_mutex;
	unsigned char held = 0;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = 1;

	int idx = index;
	void *arg_b = b;
	void *arg_a = a;
	((Rva0069B440Block *)((char *)this + 0xB8 + idx * 0x1C4))->apply(arg_a, arg_b);

	if (held)
		ReleaseMutex(mutex);
}
