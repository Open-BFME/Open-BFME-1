// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
// partial score=0.81 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc /Iinputs/reference/shims/stringinline
// stlport

// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
// Retail 0x006AC1A0, 456 bytes. Replaces the naked __emit copy in
// AudioManager_isMusicAlreadyLoadedMethodThunk.cpp.
//
// Identity: the AudioManager vtable head installed at 0x0111C0C0 carries this
// method in slot +0x138, and the two named callers (GameAudio.cpp:238/246 and
// GameEngine.cpp:435) spell it isMusicAlreadyLoaded on TheAudio exactly as
// Zero Hour GameAudio.h:292 declares it. The name is not contradicted by the
// body: it returns FileSystem::doesFileExist() on the generated filename of an
// AT_Music event, and nothing else in the class has that shape.
//
// Body: the Zero Hour AudioManager::isMusicAlreadyLoaded walk of
// m_allAudioEventInfo (+0x70), with the three differences the disassembly
// proves. The retained handle is a refcounted CountedPtr, not a raw pointer:
// the entry is Add_Ref'd on inspection (InterlockedIncrement at +0x58),
// copy-assigned through the shared CountedPtr operator= ILT 0x0002C6D8 when it
// matches, and released with a deleting destructor when the temporary dies.
// The scan stops at the FIRST match instead of taking the last, and the entry
// must also carry none of the m_type (+0x38) mask 0x600. AudioEventRTS is then
// built from the retained handle with the thin (name, timeOfDay) constructor
// reached through ILT 0x0001EC13.
//
// MEASURED 2026-09-27 (probe, relocations masked): 465 bytes against retail's
// 456, 316 differing non-reloc bytes, 0.810 of instructions equal once
// registers and constants are normalised, 21 structural differences. The frame
// is now retail's exactly -- sub esp,0x80, the four saved registers, the EH
// scope record at +0x90, the same live slots -- and the entry sequence is
// retail's instruction for instruction apart from one register name.
//
// Levers established, each measured (do not retry them):
//   LOOP HEADER. The break must be the LAST statement of the loop body and the
//   ++it must follow the guard, not sit in a for-header. The while spelling
//   with ++it last duplicates `return false` at the latch and costs 17 bytes
//   (506 -> 489); the for-header spelling trades retail's folded
//   `test ebx,ebx` for a materialised cmp and is no better. Either way MSVC
//   only emits retail's `xor <reg>,<reg>` zero register when the latch
//   re-tests the loop condition, which is worth 4 bytes at the entry stores.
//   throw(). `virtual ~AudioEventRTS() throw();` (-8) and
//   `void bind(const CountedPtr &) throw();` (-16) are worth 24 bytes together.
//   throw() on ~AudioEventInfo, on rts::hash<AsciiString>::operator() or on
//   getFilename / bfmeGenerateFilename / doesFileExist / the AudioEventRTS
//   constructor changes nothing; throw() on isMusicAlreadyLoaded ITSELF drops
//   the SEH frame and the body (370 bytes) and is wrong.
//   NOT levers (each byte-identical to the line above, measured): binding the
//   map to a reference or pointer local; swapping the two declaration orders;
//   nesting the aet block, the break block, the tail block or the whole loop
//   one or two levels deeper; an uninitialised pad local in the loop or tail
//   body; test-operand and comparison-polarity respellings; and the frame,
//   register, copy, store, sib, bool, test, constant and branch families from
//   tools/shape_family_levers.py, which generate one choice here.
//
// REMAINING BLOCKER: one allocator decision, worth 9 bytes and ~300 of the
// 316. Retail holds the entry's zero in ESI and the loop cursor in EBX, so the
// zero dies at +0x2d, ESI is free to carry `second`, and MSVC keeps the
// AudioEventInfo* live in a register across both Interlocked calls -- giving
// `lea ebp,[esi+4]` once, no reload of the temporary and no null re-test. This
// build holds the zero in EBX for the whole body and the cursor in ESI, so it
// re-reads the temporary out of memory, re-tests it for null twice, and spends
// `cmp reg,ebx` where retail spends `test reg,reg`. Seventeen source
// perturbations failed to flip the pair; it is not reachable by respelling.
// The second, smaller residue is the frame slot: retail's block-scoped aet sits
// at +0x18, on the dead cursor, and shares it, while its tail-block astr holds
// +0x14 alone; this build puts both at +0x14. Block nesting does not move it
// (see the pad-local probe above), so that choice is MSVC-internal.
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

// Retail reaches each of these bodies through its own incremental-link thunk,
// and the thunks are what the call sites name, so the calls are spelled through
// them (each thunk is a bare jmp, hence the thiscall member-function-pointer
// union the caller uses to get retail's stack cleanup).
void j_0000af6f(void);		// hash_map::begin, 0x006A0390
void j_0000ec91(void);		// rts::hash<AsciiString>::operator(), 0x000B8600
void j_0002c6d8(void);		// CountedPtr::operator=, 0x00087750
void j_0001ec13(void);		// AudioEventRTS(name, timeOfDay), 0x000B2D90
void j_00046a33(void);		// AudioEventRTS::bfmeGenerateFilename, 0x000B4840
void j_0000b7d5(void);		// AudioEventRTS::getFilename, 0x000B3B70
void j_00026f35(void);		// ~AudioEventRTS, 0x000B31F0

enum AudioType
{
	AT_Music = 0
};

namespace rts
{
// Retail's instantiation takes the key BY VALUE (0x000B8600 is
// `int __stdcall rts::hash<AsciiString>::operator()(AsciiString) const`), which
// is why _M_bkt_num copy-constructs the node key into the outgoing argument
// slot; the copy is released by the callee. The empty functor is what puts
// _M_buckets at +0x04 of the hashtable, the layout 0x006A0390 and the inlined
// _M_skip_to_next both read.
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

	long m_refCount;					// +0x04
	char m_pad08[0x38 - 0x08];
	UnsignedInt m_type;					// +0x38
	char m_pad3c[0x84 - 0x3c];
	AudioType m_soundType;				// +0x84
};

// The retained handle. Four bytes holding a refcounted AudioEventInfo: the
// copy-assign is out of line at the shared CountedPtr operator= ILT
// 0x0002C6D8, and the destructor hands the reference back, deleting through
// the vtable when it was the last one.
class CountedPtr
{
public:
	CountedPtr(void) : m_ptr(0) { }
	CountedPtr(AudioEventInfo *info) : m_ptr(info)
	{
		m_ptr->Add_Ref();
	}

	~CountedPtr(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	void bind(const CountedPtr &other) throw()
	{
		typedef void (CountedPtr::*BindCall)(const CountedPtr &);
		union BindBits
		{
			void (*freeFunction)(void);
			BindCall memberFunction;
		} call;
		call.freeFunction = j_0002c6d8;
		(this->*call.memberFunction)(other);
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
	virtual ~AudioEventRTS() throw();
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
	// Retail's begin() is the ICF-shared out-of-line instantiation reached
	// through its own ILT, so the map hides the header's inline begin() and
	// hands the call that address instead. The C-style cast on this is what
	// lets the pointer-to-member carry the plain thiscall the thunk expects
	// while the walk itself stays a const one.
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
	AudioEventInfoHash::const_iterator it;
	it = m_allAudioEventInfo.begin();
	while (it != m_allAudioEventInfo.end())
	{
		if (it->second)
		{
			CountedPtr aet(it->second);
			if (aet.m_ptr->m_soundType == AT_Music && !(aet.m_ptr->m_type & 0x600u))
				musicToLoad.bind(aet);
		}

		if (musicToLoad.m_ptr)
			break;

		++it;
	}
	if (!musicToLoad.m_ptr)
		return false;

	{
		AudioEventRTS aud(*(const AsciiString *)&musicToLoad, 2);
		aud.bfmeGenerateFilename();
		AsciiString astr = aud.getFilename();

		return TheFileSystem->doesFileExist(astr.str());
	}
}
