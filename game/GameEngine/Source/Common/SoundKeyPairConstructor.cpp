// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// SoundKeyPair constructor; retail 0x003CFB00 (127 bytes).
// EH cleanup uses the actual retail thunks for the string at +0x0C and
// four-byte vectors at +0x24/+0x30; helper identities stay local.

extern void j_0000d828(void);
extern void j_0002874a(void);

class LargeGroupAudioMap;

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap();
	~LargeGroupAudioKeyMap();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};


// The +0x0C member is an AsciiString: retail's EH funclet calls ILT
// 0x0000D828, whose body is the existing AsciiString dtor at 0x0005EE90.
#include "ascii_string.h"

class SoundKeyVector
{
public:
	SoundKeyVector() : m_begin(0), m_end(0), m_capacity(0) {}
	__forceinline ~SoundKeyVector()
	{
		typedef void (SoundKeyVector::*Destroy)();
		union { void (*raw)(void); Destroy member; } target;
		target.raw = j_0002874a;
		(this->*target.member)();
	}

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

// The existing incremental-link ILT 0x0002874A reaches the exact 45-byte
// four-byte STL vector-base destructor at 0x003CE830.

extern void j_000486cb(void);

struct Rva003CF790Call
{
	void reserve(unsigned int count);
};

static __forceinline void callRva003CF790(void *receiver, unsigned int count)
{
	typedef void (Rva003CF790Call::*Action)(unsigned int);
	union
	{
		void (*raw)(void);
		Action member;
	} fn;
	fn.raw = j_000486cb;
	(reinterpret_cast<Rva003CF790Call *>(receiver)->*fn.member)(count);
}

class SoundKeyPair
{
public:
	SoundKeyPair(LargeGroupAudioMap *owner);

private:
	LargeGroupAudioKeyMap m_keyMap;
	AsciiString m_headerKey;
	void *m_groups[4];
	LargeGroupAudioMap *m_owner;
	SoundKeyVector m_second;
	SoundKeyVector m_first;
};

SoundKeyPair::SoundKeyPair(LargeGroupAudioMap *owner)
	: m_owner(owner)
{
	m_groups[0] = 0;
	m_groups[1] = 0;
	m_groups[2] = 0;
	m_groups[3] = 0;
	callRva003CF790(&m_first, 40);
	callRva003CF790(&m_second, 40);
}
