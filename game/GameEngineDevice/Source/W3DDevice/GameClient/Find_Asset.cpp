// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
//
// Open-BFME5: AssetRegistry::Find_Asset, the counted lookup targets/game/reverse/symbols.csv
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

private:
	unsigned char m_unmodelled_000[0x2c];
	CRITICAL_SECTION m_lock;
	unsigned char m_unmodelled_048[0x1a8];
	NameKeyGenerator *m_hash_context;
};

// ?Find_Asset@AssetRegistry@@QAE?AVAssetReference@@PBD@Z
AssetReference AssetRegistry::Find_Asset(const char *name)
{
	CriticalSectionLock lock((int)&m_lock);
	unsigned int key = (unsigned int)m_hash_context->nameToLowercaseKey(name);
	if (key == 0)
		return AssetReference();

	typedef _STL::hash_map<unsigned int, CountedAsset *> AssetRegistryHash;
	AssetRegistryHash *assets = (AssetRegistryHash *)((char *)this + 0x44);
	AssetRegistryHash::iterator it = assets->find(key);
	if (it == assets->end())
		return AssetReference();

	return AssetReference((*it).second);
}
