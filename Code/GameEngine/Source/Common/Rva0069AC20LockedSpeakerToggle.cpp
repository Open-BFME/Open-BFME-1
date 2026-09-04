// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded toggle of +0x632; drives _AIL_set_3D_speaker_type on provider.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_3D_speaker_type(
	int handle, int speaker_type);

class Rva0069AC20Owner
{
public:
	void toggle();

	char m_bytes[0xb64];
};

void Rva0069AC20Owner::toggle()
{
	void *mutex = *(void **)(m_bytes + 0x95c);
	unsigned char held = 0;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = 1;

	unsigned char on = m_bytes[0x632] == 0;
	m_bytes[0x632] = on;
	if (on)
	{
		int index = *(int *)(m_bytes + 0x958);
		int scaled = index + index * 2;
		_AIL_set_3D_speaker_type(*(int *)(m_bytes + 0x658 + scaled * 4), 1);
	}
	else
	{
		int speaker = *(int *)(m_bytes + 0xb60);
		if (speaker == 1)
		{
			int index = *(int *)(m_bytes + 0x958);
			int scaled = index + index * 2;
			_AIL_set_3D_speaker_type(*(int *)(m_bytes + 0x658 + scaled * 4), 5);
		}
		else
		{
			int index = *(int *)(m_bytes + 0x958);
			int scaled = index + index * 2;
			_AIL_set_3D_speaker_type(*(int *)(m_bytes + 0x658 + scaled * 4), speaker);
		}
	}

	if (held)
		ReleaseMutex(mutex);
}
