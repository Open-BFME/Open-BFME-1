// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded thiscall into channel block at this+0xB8+index*0x1C4.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);

// Retail ILT 0x00047A64 lands on 0x006999C0, matched as
// Rva00699180Owner::setVolumes(float, unsigned char).
class Rva00699180Owner
{
public:
	void setVolumes(float a, unsigned char b);
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
	((Rva00699180Owner *)((char *)this + 0xB8 + idx * 0x1C4))->setVolumes(*(float *)&a, *(unsigned char *)&b);

	if (held)
		ReleaseMutex(mutex);
}
