// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ
// partial score=0.35 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
//
// Retail 0x009EEF10, 200 bytes, still claimed by the Code/gen_asm dump.
// reverse/symbols.csv already pins this name here because Rva009EBDC0 calls it.
//
// The model below is the one the LANDED Find_Asset at 0x009EEC60 proved and
// needs no re-derivation: critical section at +0x2C, hash_map at +0x44,
// AssetReference with the unguarded raw-pointer constructor and the
// Release_Ref destructor.  What this body adds is the hash_map ITERATOR stored
// in the registry at +0x58/+0x5C -- retail reads the node at +0x58 and the
// hashtable back-pointer at +0x5C, which is exactly STLport's _Ht_iterator
// layout, and its advance re-derives the bucket with a `div` off the node's key
// and then scans forward, so the container is a hash_map keyed by the same
// unsigned int Find_Asset uses.
//
// MEASURED, AND THIS IS THE FINDING: the unwind frame follows the NAMED return
// object, not the lock.  Returning `AssetReference((**cursor).second)` directly
// after advancing compiles to 100 bytes with no fs:[0] registration at all; a
// local iterator copy assigned back gives 122, still frameless; naming the
// result object before the advance restores the frame and takes the body to
// 182 of 200.  What is still wrong at that point starts at +0x15, where retail
// reserves ONE stack slot (`push ecx`) and the named form reserves two
// (`sub esp,8`) -- so retail materialises the returned reference without the
// extra temporary while still arming the state.
//
// IDENTITY IS NOT AT ISSUE: the name is the pinned one.
// stlport
//
// Open-BFME5: AssetRegistry::Find_Asset, the counted lookup reverse/symbols.csv
// already pins at 0x009EEC60 because Rva009EBEC0 returns its result.
//
// The layout is the one Render_Obj_Exists.cpp already proved for this class --
// the critical section at +0x2C, the hash_map at +0x44 and the name-key
// generator at +0x1F0 -- and the AssetReference model is the one
// Rva009EBEC0.cpp already carries, with the raw-pointer constructor this body
// needs added: retail bumps the sixteen-bit count at +4 of the found asset
// WITHOUT a null test, which the copy constructor's guarded form cannot do.
//
// The destructor on AssetReference is load-bearing: it is what arms the second
// unwind state. Without it the same body compiles to 175 bytes and the state
// store ahead of EnterCriticalSection disappears.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

struct CRITICAL_SECTION
{
	unsigned char m_data[0x1c];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(int lock) : m_lock(lock)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_lock);
	}

	int m_lock;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToLowercaseKey(const char *name);
};

class CountedAsset
{
public:
	void Release_Ref();
};

class AssetReference
{
public:
	AssetReference() : m_object( 0 ) {}
	AssetReference( CountedAsset *object ) : m_object( object )
	{
		++*(unsigned short *)((char *)object + 4);
	}
	AssetReference( const AssetReference &that ) : m_object( that.m_object )
	{
		if ( m_object )
		{
			++*(unsigned short *)((char *)m_object + 4);
		}
	}
	~AssetReference()
	{
		if ( m_object )
		{
			m_object->Release_Ref();
		}
	}

private:
	CountedAsset *m_object;
};

class AssetRegistry
{
public:
	AssetReference Find_Asset(const char *name);
	AssetReference Get_Current_Asset();

private:
	unsigned char m_unmodelled_000[0x2c];
	CRITICAL_SECTION m_lock;
	unsigned char m_unmodelled_048[0x1a8];
	NameKeyGenerator *m_hash_context;
};

// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ
AssetReference AssetRegistry::Get_Current_Asset()
{
	CriticalSectionLock lock((int)&m_lock);

	typedef _STL::hash_map<unsigned int, CountedAsset *> AssetRegistryHash;
	AssetRegistryHash *assets = (AssetRegistryHash *)((char *)this + 0x44);
	AssetRegistryHash::iterator *cursor =
		(AssetRegistryHash::iterator *)((char *)this + 0x58);

	if (*cursor == assets->end())
		return AssetReference();

	AssetReference result((**cursor).second);
	++*cursor;
	return result;
}
