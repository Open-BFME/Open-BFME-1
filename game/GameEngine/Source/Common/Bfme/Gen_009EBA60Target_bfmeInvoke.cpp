// ?bfmeInvoke@Gen_009EBA60Target@@QAEXPAX0@Z
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
//
// The member the matched guarded dispatcher bfmeDispatch_009EBA60
// (S3GuardedDispatchers.cpp) calls on the registry g_theAssetRegistry
// (0x0134FAAC) points at; targets/game/reverse/symbols.csv already pins this name at
// 0x009EEAC0. The layout is the one the landed constructor
// ??0Gen_dtor_009eb9e0@@QAE@XZ size-checks and Find_Asset.cpp uses: the
// critical section at +0x2C, the hash_map<int, Gen_t_009f14c0_p12cd> at
// +0x44 (the constructor's type, whose begin() is pinned at 0x009EE0F0; the
// out-of-line find retail calls is its 60-byte body at 0x009EE6D0) and the
// name-key generator at +0x1F0.
//
// The second argument is a pointer set: retail tests its node count at +4,
// walks it from the header's leftmost node with the STLport tree increment
// and reads each value at node+0x10. Under the registry lock the named
// entry's record gets, if it has none yet, a null-terminated new[] copy of
// that set at +0xC.
//
// The find result is converted to a const_iterator, which is what keeps the
// returned temporary and the iterator in separate frame slots the way retail
// does (the table half of the copy lands at esp+0x1C).

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <set>

struct CRITICAL_SECTION
{
	unsigned char m_data[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
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

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;

struct Gen_t_009f14c0_p12cd
{
	void *m_asset;
	int a[2];
	Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd(const Gen_t_009f14c0_p12cd &);
	~Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd &operator=(const Gen_t_009f14c0_p12cd &);
};

typedef _STL::hash_map<int, Gen_t_009f14c0_p12cd> GenAssetHash;

struct GenAssetRecord
{
	char m_prefix[0xc];
	Rva001408C0Key *m_items;
};

class Gen_009EBA60Target
{
public:
	void bfmeInvoke(void *name, void *source);

private:
	char m_prefix[0x2c];
	CRITICAL_SECTION m_lock;
	GenAssetHash m_assets;
	char m_gap[0x1f0 - 0x44 - sizeof(GenAssetHash)];
	NameKeyGenerator *m_hash_context;
};

void Gen_009EBA60Target::bfmeInvoke(void *name, void *source)
{
	if (name == 0)
		return;

	const Rva001408C0Set &keys = *(const Rva001408C0Set *)source;
	if (keys.size() == 0)
		return;

	CriticalSectionLock lock(&m_lock);
	int key = m_hash_context->nameToLowercaseKey((const char *)name);
	if (key == 0)
		return;

	GenAssetHash::const_iterator found = m_assets.find(key);
	if (found == m_assets.end())
		return;

	GenAssetRecord *record = (GenAssetRecord *)(*found).second.m_asset;
	if (record->m_items != 0)
		return;

	record->m_items = new Rva001408C0Key[keys.size() + 1];
	int count = 0;
	for (Rva001408C0Set::const_iterator it = keys.begin(); it != keys.end(); ++it)
		record->m_items[count++] = *it;
	record->m_items[count] = 0;
}
