// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport

// Open-BFME5: the wrapper and its AssetRegistry lookup implementation.

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

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

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

class NameKeyGenerator
{
public:
	NameKeyType nameToLowercaseKey(const char *name);
};

class AssetRegistry
{
public:
	bool Render_Obj_Exists_Impl(const char *name);

private:
	unsigned char m_unmodelled_000[0x2c];
	CRITICAL_SECTION m_lock;
	unsigned char m_unmodelled_048[0x1a8];
	NameKeyGenerator *m_hash_context;
};

extern AssetRegistry *g_theAssetRegistry;

// ?Render_Obj_Exists_Impl@AssetRegistry@@QAE_NPBD@Z
bool AssetRegistry::Render_Obj_Exists_Impl(const char *name)
{
	CriticalSectionLock lock((int)&m_lock);
	unsigned int key = m_hash_context->nameToLowercaseKey(name);
	if (key == 0)
		return false;
	typedef _STL::hash_map<unsigned int, void *> AssetRegistryHash;
	AssetRegistryHash *assets =
		(AssetRegistryHash *)((char *)this + 0x44);
	AssetRegistryHash::iterator it = assets->find(key);
	return it != assets->end();
}

// ?Render_Obj_Exists@@YA_NPBD@Z
bool Render_Obj_Exists(const char *name)
{
	if (name)
	{
		AssetRegistry *reg = g_theAssetRegistry;
		if (reg)
			return reg->Render_Obj_Exists_Impl(name);
	}
	return false;
}
