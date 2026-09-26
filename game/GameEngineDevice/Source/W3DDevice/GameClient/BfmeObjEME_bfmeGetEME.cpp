// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport

// AssetRegistry raw name lookup at 0x009EED20. The matched wrapper
// bfmeGoEMEb (0x009EC0B0) loads g_theAssetRegistry and thiscalls this
// body; Render_Obj_Exists_Impl is the bool twin of the same walk.

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

class BfmeObjEME
{
public:
	void *bfmeGetEME(void *name);

private:
	unsigned char m_unmodelled_000[0x2c];
	CRITICAL_SECTION m_lock;
	unsigned char m_unmodelled_048[0x1a8];
	NameKeyGenerator *m_hash_context;
};

// ?bfmeGetEME@BfmeObjEME@@QAEPAXPAX@Z
void *BfmeObjEME::bfmeGetEME(void *name)
{
	CriticalSectionLock lock((int)&m_lock);
	unsigned int key = m_hash_context->nameToLowercaseKey((const char *)name);
	if (key == 0)
		return 0;
	typedef _STL::hash_map<unsigned int, void *> AssetRegistryHash;
	AssetRegistryHash *assets =
		(AssetRegistryHash *)((char *)this + 0x44);
	AssetRegistryHash::iterator it = assets->find(key);
	if (it == assets->end())
		return 0;
	return (void *)key;
}
