// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport

// Retail 0x006AE710 creates the BFME audio-info object for a missing name.
// The constructor vtable, the shared mutex, and the map lookup identify this
// as AudioManager::newAudioEventInfo.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "StringInline.h"


inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	const char *leftText = left.str();
	const char *rightText = right.str();
	while (*leftText && *leftText == *rightText)
	{
		++leftText;
		++rightText;
	}
	return *leftText == *rightText;
}

typedef long Long;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	Long volatile *addend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	Long volatile *addend);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

class BfmeA1202
{
public:
	BfmeA1202();
	virtual ~BfmeA1202();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	Long m_refCount;
	char m_pad008[0x98 - 0x08];
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(void) : m_info(0) {}

	AudioEventInfoRef(BfmeA1202 *info) : m_info(info)
	{
		if (m_info)
			InterlockedIncrement(&m_info->m_refCount);
	}

	~AudioEventInfoRef(void)
	{
		if (m_info)
			m_info->Release_Ref();
	}

	BfmeA1202 *m_info;
};

class AudioManagerMutex
{
public:
	__forceinline AudioManagerMutex(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		if (WaitForSingleObject(m_mutex, 0xFFFFFFFFu) != 0x102u)
			m_held = 1;
	}

	__forceinline ~AudioManagerMutex(void)
	{
		if (m_held)
		{
			ReleaseMutex(m_mutex);
			m_held = 0;
		}
	}

private:
	void *m_mutex;
	unsigned char m_held;
};

typedef _STL::hash_map<AsciiString, BfmeA1202 *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Rva006A7AD0Map;

struct Rva006A7AD0Node
{
	Rva006A7AD0Node *m_next;
	AsciiString m_key;
	BfmeA1202 *m_value;
};

extern void j_0000691a(void);
extern void j_00027e03(void);
extern void j_00041669(void);

class AudioEventInfoMap : public Rva006A7AD0Map
{
public:
	void *findNode(const AsciiString &key) const
	{
		typedef void *(AudioEventInfoMap::*Find)(const AsciiString &) const;
		union FindBits
		{
			void (*freeFunction)(void);
			Find memberFunction;
		} find;
		find.freeFunction = j_0000691a;
		return (this->*find.memberFunction)(key);
	}

	BfmeA1202 *&operator[](const AsciiString &key)
	{
		typedef BfmeA1202 *&(AudioEventInfoMap::*Lookup)(const AsciiString &);
		union LookupBits
		{
			void (*freeFunction)(void);
			Lookup memberFunction;
		} lookup;
		lookup.freeFunction = j_00027e03;
		return (this->*lookup.memberFunction)(key);
	}
};

struct Rva006AAF10Element
{
	BfmeA1202 *m_info;

	Rva006AAF10Element(const Rva006AAF10Element &other) : m_info(other.m_info)
	{
		if (m_info)
			InterlockedIncrement(&m_info->m_refCount);
	}

	~Rva006AAF10Element(void)
	{
		if (m_info)
			m_info->Release_Ref();
	}
};

typedef _STL::vector<Rva006AAF10Element,
	_STL::allocator<Rva006AAF10Element> > AudioInfoVector;

class AudioManager
{
public:
	virtual AudioEventInfoRef newAudioEventInfo(const AsciiString &audioName);

private:
	char m_pad004[0x6c];
	AudioEventInfoMap m_allAudioEventInfo;
	char m_pad084[4];
	AudioInfoVector m_audioInfos;
	char m_pad094[0x630 - 0x94];
	unsigned char m_infoDirty;
	char m_pad631[0x95c - 0x631];
	void *m_mutex;
};

AudioEventInfoRef AudioManager::newAudioEventInfo(const AsciiString &audioName)
{
	AudioManagerMutex guard(m_mutex);
	Rva006A7AD0Node *node = (Rva006A7AD0Node *)m_allAudioEventInfo.findNode(audioName);
	if (node)
	{
		BfmeA1202 *info = node->m_value;
		return AudioEventInfoRef(info);
	}

	m_infoDirty = 0;
	AudioEventInfoRef info = new BfmeA1202;
	m_audioInfos.push_back(*reinterpret_cast<const Rva006AAF10Element *>(&info));
	m_allAudioEventInfo[audioName] = info.m_info;
	return AudioEventInfoRef(m_allAudioEventInfo[audioName]);
}
