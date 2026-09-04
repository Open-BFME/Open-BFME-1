// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded 5-arg thiscall into channel at this+0xB8+index*0x1C4.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);

class Rva0069AFC0Block
{
public:
	void apply(void *a, void *b, void *c, void *d, void *e);
};

class Rva0069AFC0Owner
{
public:
	void call(void *a, void *b, void *c, void *d, void *e, int index);

	char m_pad0[0x95c];
	void *m_mutex;
};

void Rva0069AFC0Owner::call(void *a, void *b, void *c, void *d, void *e, int index)
{
	void *mutex = m_mutex;
	unsigned char held = 0;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = 1;

	void *arg_e = e;
	void *arg_d = d;
	void *arg_c = c;
	void *arg_b = b;
	void *arg_a = a;
	int idx = index;
	((Rva0069AFC0Block *)((char *)this + 0xB8 + idx * 0x1C4))->apply(
		arg_a, arg_b, arg_c, arg_d, arg_e);

	if (held)
		ReleaseMutex(mutex);
}
