// ?bfmeInvoke@Gen_009EBA60Target@@QAEXPAX0@Z
// partial score=0.95 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
// ?bfmeInvoke@Gen_009EBA60Target@@QAEXPAX0@Z

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

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
	int nameToLowercaseKey(const char *name);
};

struct Gen_p12cd
{
	void *m_asset;
	int m_reserved4;
	int m_reserved8;
};

typedef _STL::pair<const int, Gen_p12cd> GenAssetPair;
typedef _STL::hash_map<int, Gen_p12cd> GenAssetHash;

namespace _STL
{

struct _Rb_tree_node_base;

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

}

struct GenAssetTreeNode
{
	char m_tree_links[0x10];
	void *m_value;
};

struct GenAssetTree
{
	char m_tree_header[8];
	GenAssetTreeNode *m_root;
};

struct GenAssetSource
{
	GenAssetTree *m_tree;
	int m_count;
};

struct GenAssetRecord
{
	char m_prefix[0xc];
	void **m_items;
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

	GenAssetSource *assetSource = (GenAssetSource *)source;
	if (assetSource->m_count == 0)
		return;

	CriticalSectionLock lock((int)&m_lock);
	int keySlot[2];
	keySlot[0] = m_hash_context->nameToLowercaseKey((const char *)name);
	if (keySlot[0] == 0)
		return;
	GenAssetHash::iterator *it = &m_assets.find(keySlot[0]);
	GenAssetHash::iterator found = *it;
	if (found._M_cur == 0)
		return;
	GenAssetRecord *record =
		(GenAssetRecord *)found._M_cur->_M_val.second.m_asset;
	if (record->m_items != 0)
		return;

	GenAssetTreeNode *entry;
	record->m_items = new void *[assetSource->m_count + 1];
	entry = assetSource->m_tree->m_root;
	int count = 0;
	while (entry != (GenAssetTreeNode *)assetSource->m_tree)
	{
		record->m_items[count++] = (void *)entry->m_value;
		entry = (GenAssetTreeNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
	record->m_items[count] = 0;
}
