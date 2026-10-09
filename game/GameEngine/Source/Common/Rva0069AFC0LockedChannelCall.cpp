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

// Matched ledger row ?setParams@Rva006998C0Owner@@QAEXMMHHH@Z at 0x006998C0
// (defined in game/GameEngine/Source/Common/Rva006998C0SetParams.cpp).
class Rva006998C0Owner
{
public:
	void setParams(float a, float b, int c, int d, int e);
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
	((Rva006998C0Owner *)((char *)this + 0xB8 + idx * 0x1C4))->setParams(
		*(float *)&a, *(float *)&b, (int)c, (int)d, (int)e);

	if (held)
		ReleaseMutex(mutex);
}
