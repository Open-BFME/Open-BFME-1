// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_USE_OWN_NAMESPACE 1

#include <deque>

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

class RefCountedPlayingAudio
{
public:
	virtual ~RefCountedPlayingAudio();
	void Add_Ref() { InterlockedIncrement(&m_refCount); }
	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}
private:
	long m_refCount;
};

class PlayingAudio : public RefCountedPlayingAudio {};

class PlayingAudioRef
{
public:
	PlayingAudioRef() : m_ptr(0) {}
	PlayingAudioRef(const PlayingAudioRef &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}
	~PlayingAudioRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
private:
	PlayingAudio *m_ptr;
};

typedef _STL::deque<PlayingAudioRef> PlayingAudioDeque;

struct Rva006B9320Field
{
	char m_pad00[0x28];
	int m_field28;
	char m_pad2c[0x18];
	unsigned char m_flag44;
	char m_pad45[0x1f];
	int m_field64;
};

struct Rva006B9320Request
{
	int m_action;
	Rva006B9320Field *m_field;
	void *m_payload;
	char m_pad0c[4];
	unsigned char m_flag10;
	unsigned char m_flag11;
};

class AudioEventRTS
{
public:
	bool getIsLogicalAudio() const;
};


class Gen_006A6AF0
{
public:
	void bfmePrep(int a, int c);
};

class Rva006A56A0
{
public:
	void rva006A56A0(int a, int b, int c);
};

class Rva006A5870
{
public:
	void case4(Rva006B9320Request *request);

private:
	char m_bfmePad[0x9D4];
	PlayingAudioDeque m_bfmeCells[6];
	int m_bfmeMap[1];
};

// ?case4@Rva006A5870@@QAEXPAURva006B9320Request@@@Z
void Rva006A5870::case4(Rva006B9320Request *request)
{
	Rva006B9320Field *field = request->m_field;
	int b = field->m_field64;
	int a = field->m_field28;

	if (m_bfmeMap[a] == b)
	{
		((Gen_006A6AF0 *)this)->bfmePrep(a, !request->m_flag10);
		field = request->m_field;
		((Rva006A56A0 *)this)->rva006A56A0(a, b, !((AudioEventRTS *)field)->getIsLogicalAudio());
		return;
	}

	if (!m_bfmeCells[b + a * 2].empty())
		m_bfmeCells[b + a * 2].pop_back();
}
