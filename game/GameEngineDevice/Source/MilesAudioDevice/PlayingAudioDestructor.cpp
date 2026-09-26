extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

class ClientSubsystem
{
};

class BfmeBaseASCa
{
public:
	virtual ~BfmeBaseASCa() {}

	volatile long m_refCount;
};

class Rva00691200RefBase
{
public:
	virtual ~Rva00691200RefBase();

	void Release()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva00691200Pad
{
	unsigned char m_padding[0x70];
};

class Rva00691200Obj : public Rva00691200Pad, public Rva00691200RefBase
{
};

class Rva00691200Holder
{
public:
	~Rva00691200Holder()
	{
		Rva00691200Obj *object = m_pointer;
		if (object)
		{
			Rva00691200RefBase *ref =
				(Rva00691200RefBase *)((char *)object + 0x70);
			ref->Release();
		}
	}

	Rva00691200Obj *m_pointer;
};

class Rva00690FF0Handle
{
public:
	~Rva00690FF0Handle();

	void *m_pointer;
};

class PlayingAudio;
extern void j_000207a2();
extern ClientSubsystem *TheAudioClientUpdate;

class PlayingAudio : public BfmeBaseASCa
{
public:
	virtual ~PlayingAudio();

private:
	void *m_milesHandle;
	int m_type;
	volatile int m_status;
	Rva00691200Holder m_audioEvent;
	Rva00690FF0Handle m_file;
	unsigned int m_value1c;
	unsigned int m_value20;
	unsigned int m_value24;
	unsigned int m_value28;
	float m_volume;
	int m_playingAudioIndex;
	unsigned char m_flags[0x0b];
};

PlayingAudio::~PlayingAudio()
{
	if (TheAudioClientUpdate)
	{
		typedef void (ClientSubsystem::*RemovePlayingAudio)(PlayingAudio *);
		union
		{
			void (__cdecl *freeFunction)();
			RemovePlayingAudio memberFunction;
		} remove;
		remove.freeFunction = ::j_000207a2;
		(TheAudioClientUpdate->*remove.memberFunction)(this);
	}

}
