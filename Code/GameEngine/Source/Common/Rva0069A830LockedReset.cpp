// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded Miles room-type clear when provider index != -1.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_3D_room_type(int handle, int room);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_digital_master_room_type(
	void *dig, int room);

class Rva0069A830Owner
{
public:
	void reset();

	char m_bytes[0xb58];
};

void Rva0069A830Owner::reset()
{
	void *mutex = *(void **)(m_bytes + 0x95c);
	unsigned char held = 0;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = 1;

	int index = *(int *)(m_bytes + 0x958);
	*(int *)(m_bytes + 0xb54) = 0;
	if (index != -1)
	{
		int scaled = index + index * 2;
		_AIL_set_3D_room_type(*(int *)(m_bytes + 0x658 + scaled * 4), 0);
		_AIL_set_digital_master_room_type(*(void **)(m_bytes + 0x960), 0);
	}
	if (m_bytes[0x633])
	{
		m_bytes[0x633] = 0;
		m_bytes[0x634] = 1;
	}
	if (held)
		ReleaseMutex(mutex);
}
