// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
// partial score=0.1908 date=2026-10-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc /Iinputs/reference/shims/stringinline
// stlport
//
// Retail 0x006AC1A0, 456 bytes. Probe (relocations masked): 463 bytes,
// shape 0.972, 5 structural differences, first at +001e. Frame, EH state
// machine, loop control flow, hash-walk and tail all match retail exactly.
//
// FINDINGS SINCE THE 0.81/0.848 BANKS (all measured, keep them):
//   1. EH MAP (tools/eh_info.py): state 0 is musicToLoad itself -- the class
//      HAS a tracked destructor (state 0 window, dtor inlined at function end,
//      folded to nothing on the early return because the exit test reads
//      musicToLoad.m_ptr directly). State 1 is aet, 2 aud, 3 astr. The
//      unwind funclets for states 0 and 1 both jmp ILT 0x000362FF ->
//      0x000877B0, so musicToLoad and aet are the SAME class; the pinned
//      ledger views for that class are the dtor body at 0x000877B0 and the
//      assign body at 0x00087750 (via ILT 0x0002C6D8 -- the exact callee of
//      this body's bind call).
//   2. The visible __declspec(noinline) operator= body in the TU is what
//      lets MSVC keep the AudioEventInfo* live in a register across the
//      bind call (no reload, no null re-test, `lea <reg>,[esi+4]` CSE'd
//      for both Interlocked pushes). Declaration-only reverts all three.
//   3. `while ((true) && it == it && it == it && it != end())`: the
//      self-compares fold to zero bytes and are what stops MSVC rotating
//      the loop (retail's back-edge targets the head test, no bottom
//      test). One self-compare also works (463B both, shape 0.965 vs
//      0.972); plain while/gotos/while(true) all rotate (470-517B).
//   4. Tail locals at FUNCTION scope (no braces around the tail) give
//      retail's slot layout exactly: musicToLoad E+0x00, astr E+0x04,
//      begin's return slot E+0x08 (aet shares it), aud E+0x10, frame
//      sub esp,0x80. A braced tail block merges astr onto the dead
//      cursor slot and costs 4 frame bytes.
//   5. `virtual ~AudioEventRTS()` must NOT be throw(): retail keeps the
//      `mov byte [esp+0x98],0` state store before the ~aud call (worth 8
//      bytes; the 0.81 bank's throw() measurements match this).
//
// REMAINING BLOCKER (one allocator/PRE decision, ~7 bytes, 2 sites):
// retail materialises the entry zero in ESI (`xor esi,esi` feeding both
// the musicToLoad store and the state=0 store), loads musicToLoad.m_ptr
// into ESI at the latch, and the loop-exit re-test reuses that ESI with
// no reload (`test esi,esi` at +0x141). This build stores two immediates
// at entry, loads the latch value into EAX, and reloads at the exit
// (`mov eax,[esp+0x10]; test eax,eax`, 4 bytes more). A `loaded` local
// threaded through the latch and exit tests DOES create the unified ESI
// web (verified: exit becomes `test esi,esi`) but it breaks the
// path-sensitive fold of musicToLoad's destructor on the early return
// (the exit test no longer reads the member, so the early path emits the
// full release, +54B). Everything else then follows from the missing web:
// cursor lands in EBP instead of EBX, &refcount in EBX instead of EBP,
// and retail's 2-byte `lea esp,[esp]` alignment pad before the bucket
// scan loop at +0xdc is absent.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "StringInline.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

void j_0000af6f(void);		// hash_map::begin, 0x006A0390
void j_0000ec91(void);		// rts::hash<AsciiString>::operator(), 0x000B8600
void j_0001ec13(void);		// AudioEventRTS(name, timeOfDay), 0x00B2D90
void j_00046a33(void);		// AudioEventRTS::bfmeGenerateFilename, 0x00B4840
void j_0000b7d5(void);		// AudioEventRTS::getFilename, 0x00B3B70
void j_00026f35(void);		// ~AudioEventRTS, 0x00B31F0

enum AudioType
{
	AT_Music = 0
};

namespace rts
{
template <class T>
struct hash
{
	UnsignedInt operator()(const T &key) const throw()
	{
		typedef UnsignedInt (hash<T>::*HashMember)(T) const;
		union HashBits
		{
			void (*freeFunction)(void);
			HashMember memberFunction;
		} call;
		call.freeFunction = j_0000ec91;
		return (this->*call.memberFunction)(key);
	}
};
}

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo() throw();

	void Add_Ref(void)
	{
		InterlockedIncrement(&m_refCount);
	}

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;						// +0x04
	char m_pad08[0x38 - 0x08];
	UnsignedInt m_type;						// +0x38
	char m_pad3c[0x84 - 0x3c];
	AudioType m_soundType;					// +0x84
};

// The shared ref-counted handle (CountedPtr). The copy-assign body is the
// verified 0x00087750 body (ILT 0x0002C6D8) and the destructor body the
// verified 0x000877B0 body (ILT 0x000362FF); keeping both visible here with
// __declspec(noinline) / inline lets MSVC prove the assignment does not
// write through the source reference, as retail's codegen does.
class CountedPtr
{
public:
	CountedPtr(void) : m_ptr(0) { }

	CountedPtr(AudioEventInfo *info) : m_ptr(info)
	{
		if (info)
			info->Add_Ref();
	}

	~CountedPtr(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	__declspec(noinline) CountedPtr &operator=(const CountedPtr &rhs)
	{
		if (this != &rhs)
		{
			if (rhs.m_ptr)
				rhs.m_ptr->Add_Ref();
			if (m_ptr)
				m_ptr->Release_Ref();
			m_ptr = rhs.m_ptr;
		}
		return *this;
	}

	AudioEventInfo *m_ptr;
};

// The 0x6C-byte AudioEventRTS the tail builds on the stack (0x000B2D90 zeroes
// its last dword at +0x6C). Its storage is only ever touched by the thunks
// above, so only the size is load-bearing.
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, Int timeOfDay);
	virtual ~AudioEventRTS();
	void bfmeGenerateFilename(void);
	AsciiString getFilename(void);

	unsigned char m_storage[0x6C];
};

class FileSystem
{
public:
	Bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

typedef _STL::hash_map<AsciiString, AudioEventInfo *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > AudioEventInfoHash;

class AudioEventInfoMap : public AudioEventInfoHash
{
public:
	const_iterator begin(void) const
	{
		typedef void (AudioEventInfoMap::*Begin)(const_iterator *result);
		union BeginBits
		{
			void (*freeFunction)(void);
			Begin memberFunction;
		} call;
		call.freeFunction = j_0000af6f;
		const_iterator result;
		((AudioEventInfoMap *)this->*call.memberFunction)(&result);
		return result;
	}
};

class __declspec(novtable) AudioManager
{
public:
	virtual Bool isMusicAlreadyLoaded(void) const;

private:
	char m_pad004[0x70 - 0x04];
	AudioEventInfoMap m_allAudioEventInfo;
};

// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
Bool AudioManager::isMusicAlreadyLoaded(void) const
{
	CountedPtr musicToLoad;
	AudioEventInfoHash::const_iterator it = m_allAudioEventInfo.begin();
	while ((true) && it == it && it == it && it != m_allAudioEventInfo.end())
	{
		AudioEventInfo *info = it->second;
		if (info)
		{
			CountedPtr aet(info);
			if (info->m_soundType == AT_Music && !(info->m_type & 0x600u))
				musicToLoad = *(const CountedPtr *)&aet;
		}

		++it;
		if (musicToLoad.m_ptr)
			break;
	}
	if (!musicToLoad.m_ptr)
		return false;

	AudioEventRTS aud(*(const AsciiString *)&musicToLoad, 2);
	aud.bfmeGenerateFilename();
	AsciiString astr = aud.getFilename();

	return TheFileSystem->doesFileExist(astr.str());
}
