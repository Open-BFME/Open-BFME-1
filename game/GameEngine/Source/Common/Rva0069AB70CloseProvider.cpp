// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Close selected 3D provider: restore speaker type, close listener+provider.

extern "C" __declspec(dllimport) void __stdcall _AIL_set_3D_speaker_type(
	int handle, int speaker_type);
extern "C" __declspec(dllimport) void __stdcall _AIL_close_3D_listener(void *listener);
extern "C" __declspec(dllimport) void __stdcall _AIL_close_3D_provider(int provider);

class VideoPlayer
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21(int);
};

extern VideoPlayer *TheVideoPlayer;

class Rva0069AB70Owner
{
public:
	void closeProvider();

	char m_bytes[0xb64];
};

void Rva0069AB70Owner::closeProvider()
{
	unsigned int selected = *(unsigned int *)(m_bytes + 0x958);
	if (selected >= *(unsigned int *)(m_bytes + 0x954))
		return;

	VideoPlayer *vp = TheVideoPlayer;
	if (vp)
		vp->v21(0);

	if (m_bytes[0x632])
	{
		int index = *(int *)(m_bytes + 0x958);
		int scaled = index + index * 2;
		_AIL_set_3D_speaker_type(
			*(int *)(m_bytes + 0x658 + scaled * 4),
			*(int *)(m_bytes + 0xb60));
	}

	_AIL_close_3D_listener(*(void **)(m_bytes + 0x964));

	int index = *(int *)(m_bytes + 0x958);
	int scaled = index + index * 2;
	*(void **)(m_bytes + 0x964) = 0;
	_AIL_close_3D_provider(*(int *)(m_bytes + 0x658 + scaled * 4));
	*(int *)(m_bytes + 0x958) = -1;
}
