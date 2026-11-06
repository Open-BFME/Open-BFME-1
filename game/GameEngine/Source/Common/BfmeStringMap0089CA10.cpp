// cl: /O2 /DNDEBUG /MD
// Open-address string-map find at retail 0x0089CA10: hashes the key into a
// bucket, then probes up to 8 slots forward and 8 backward inside the table.

// The shared empty EA string block at 0x012D5298 is one global, EA's
// EAStringC::StringDataC g_rva012D5298Empty (defined in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp).  MSVC mangles the type
// into a global's name, so the reference must carry that exact spelling; the
// TU-local BfmeStringData0089CA10 view is only reached through a cast.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;

// Retail RVA 0x009F6FA0 jumps through IAT VA 0x0135933C to
// MSVCR71._strcmpi. Keep a direct call so the import library supplies that thunk.
extern "C" int __cdecl _strcmpi(const char *left, const char *right);

struct BfmeStringData0089CA10
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

static inline BfmeStringData0089CA10 *localEmptyString1285()
{
	return reinterpret_cast<BfmeStringData0089CA10 *>(&g_rva012D5298Empty);
}

struct BfmeStringKey0089CA10
{
	BfmeStringData0089CA10 *m_data;
};

struct BfmeStringEntry0089CA10
{
	BfmeStringData0089CA10 *m_data;
	void *m_value;
};

class BfmeStringMap0089CA10
{
public:
	int m_count;
	BfmeStringEntry0089CA10 *m_entries;
	BfmeStringEntry0089CA10 *findInMap0089CA10(const BfmeStringKey0089CA10 &key);
	__forceinline BfmeStringEntry0089CA10 *findInline(const BfmeStringKey0089CA10 &key);
	unsigned int m_proto08;
	unsigned int m_prototype0c;
};

static inline bool matchEntry0089CA10(
	const BfmeStringEntry0089CA10 *entry, const BfmeStringKey0089CA10 &key)
{
	if (entry->m_data == key.m_data)
		return true;
	if (entry->m_data->m_hash != key.m_data->m_hash)
		return false;
	return _strcmpi(reinterpret_cast<const char *>(entry->m_data) + 8,
		reinterpret_cast<const char *>(key.m_data) + 8) == 0;
}

BfmeStringEntry0089CA10 *BfmeStringMap0089CA10::findInMap0089CA10(const BfmeStringKey0089CA10 &key)
{
	unsigned short keyHash = key.m_data->m_hash;
	int bucket = (m_count - 1) & keyHash;
	BfmeStringData0089CA10 *data = m_entries[bucket].m_data;
	if (data == 0)
		return 0;
	if (data != localEmptyString1285()
		&& matchEntry0089CA10(&m_entries[bucket], key))
		return &m_entries[bucket];
	int start = bucket - 8;
	int high;
	if (start < 0)
	{
		start = 0;
		high = 16;
		if (m_count <= 16)
			high = m_count - 1;
	}
	else
	{
		high = bucket + 8;
		if (high > m_count - 1)
		{
			high = m_count - 1;
			start = high - 16;
			if (start < 0)
				start = 0;
		}
	}
	int cursor = bucket;
	int forward = high - bucket;
	while (forward != 0)
	{
		--forward;
		++cursor;
		data = m_entries[cursor].m_data;
		if (data == 0)
			return 0;
		if (data != localEmptyString1285()
			&& matchEntry0089CA10(&m_entries[cursor], key))
			return &m_entries[cursor];
	}
	cursor = bucket;
	int backward = bucket - start;
	while (backward != 0)
	{
		--cursor;
		data = m_entries[cursor].m_data;
		--backward;
		if (data == 0)
			return 0;
		if (data != localEmptyString1285()
			&& matchEntry0089CA10(&m_entries[cursor], key))
			return &m_entries[cursor];
	}
	return 0;
}

// ?bfmeFind1024@BfmeTab1024@@QAEHH@Z (0x0089CEF0) inlines the same probe. Its
// first probe reads through a local snapshot of m_entries while the first-probe
// return re-reads the member; that reproduces retail's `lea ebx,[esi*8]` before
// the load (attempt_support/20261106-0089cef0-tab1024-find-entries-snapshot.md).
// ?findInline@BfmeStringMap0089CA10@@QAEPAUBfmeStringEntry0089CA10@@ABUBfmeStringKey0089CA10@@@Z absent-from-retail force-inlined into bfmeFind1024; no standalone body
__forceinline BfmeStringEntry0089CA10 *BfmeStringMap0089CA10::findInline(const BfmeStringKey0089CA10 &key)
{
	unsigned short keyHash = key.m_data->m_hash;
	BfmeStringEntry0089CA10 *entries = m_entries;
	int bucket = (m_count - 1) & keyHash;
	BfmeStringData0089CA10 *data = entries[bucket].m_data;
	if (data == 0)
		return 0;
	if (data != localEmptyString1285()
		&& matchEntry0089CA10(&entries[bucket], key))
		return &m_entries[bucket];
	int start = bucket - 8;
	int high;
	if (start < 0)
	{
		start = 0;
		high = 16;
		if (m_count <= 16)
			high = m_count - 1;
	}
	else
	{
		high = bucket + 8;
		if (high > m_count - 1)
		{
			high = m_count - 1;
			start = high - 16;
			if (start < 0)
				start = 0;
		}
	}
	int cursor = bucket;
	int forward = high - bucket;
	while (forward != 0)
	{
		--forward;
		++cursor;
		data = m_entries[cursor].m_data;
		if (data == 0)
			return 0;
		if (data != localEmptyString1285()
			&& matchEntry0089CA10(&m_entries[cursor], key))
			return &m_entries[cursor];
	}
	cursor = bucket;
	int backward = bucket - start;
	while (backward != 0)
	{
		--cursor;
		data = m_entries[cursor].m_data;
		--backward;
		if (data == 0)
			return 0;
		if (data != localEmptyString1285()
			&& matchEntry0089CA10(&m_entries[cursor], key))
			return &m_entries[cursor];
	}
	return 0;
}

class BfmeThing929G { public: void bfmeInit929G(); };
class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

int BfmeTab1024::bfmeFind1024(int keyArg)
{
	BfmeStringKey0089CA10 &key = *(BfmeStringKey0089CA10 *)keyArg;
	if (key.m_data->m_hash == 0)
		((BfmeThing929G *)&key)->bfmeInit929G();
	int id = key.m_data->m_hash;
	BfmeStringMap0089CA10 *map = (BfmeStringMap0089CA10 *)this;
	if (map->m_entries)
	{
		BfmeStringEntry0089CA10 *entry = map->findInline(key);
		if (entry)
			return (unsigned int)entry->m_value & ~1u;
	}
	if (id == 0x699)
	{
		if (_strcmpi(reinterpret_cast<const char *>(key.m_data) + 8, "prototype") == 0)
			return map->m_prototype0c & ~1u;
	}
	else if (id == 0x6bbd)
	{
		if (_strcmpi(reinterpret_cast<const char *>(key.m_data) + 8, "__proto__") == 0)
			return map->m_proto08 & ~1u;
	}
	return 0;
}

// ?bfmeErase1279@BfmeLookup1279@@QAEXAAUBfmeKey1279@@@Z (0x0089CC80, 617 B)
// erases a key through the same inlined probe: the slot's string is released
// and replaced by the shared empty string, and its tagged value released. For
// the reserved "prototype"/"__proto__" ids the tagged slot is assigned in the
// condition and masked in place, which keeps retail's single ECX
// test/and/call (attempt_support/20261106-0089cc80-erase1279-tagged-release.md).
struct BfmeStringPool3AF0 { void *m_alloc; void (__cdecl *m_free)(void *storage); };
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class Rva0089CC80Object
{
public:
	virtual void retain();
	virtual void release();
};
struct BfmeKey1279;
class BfmeLookup1279
{
public:
	void bfmeErase1279(BfmeKey1279 &key);
};

void BfmeLookup1279::bfmeErase1279(BfmeKey1279 &keyArg)
{
	BfmeStringKey0089CA10 &key = (BfmeStringKey0089CA10 &)keyArg;
	if (key.m_data == localEmptyString1285())
		return;
	if (key.m_data->m_hash == 0)
		((BfmeThing929G *)&key)->bfmeInit929G();
	int id = key.m_data->m_hash;
	BfmeStringMap0089CA10 *map = (BfmeStringMap0089CA10 *)this;
	if (map->m_entries)
	{
		BfmeStringEntry0089CA10 *entry = map->findInline(key);
		if (entry)
		{
			BfmeStringData0089CA10 *old = entry->m_data;
			if (--old->m_refCount == 0)
				g_rva01337A30AllocPair->m_free(old);
			entry->m_data = localEmptyString1285();
			++localEmptyString1285()->m_refCount;
			Rva0089CC80Object *value = (Rva0089CC80Object *)((unsigned int)entry->m_value & ~1u);
			value->release();
			entry->m_value = 0;
			return;
		}
	}
	if (id == 0x699)
	{
		Rva0089CC80Object *prototype;
		if (_strcmpi(reinterpret_cast<const char *>(key.m_data) + 8, "prototype") == 0
			&& (prototype = (Rva0089CC80Object *)map->m_prototype0c) != 0)
		{
			prototype = (Rva0089CC80Object *)((unsigned int)prototype & ~1u);
			prototype->release();
			map->m_prototype0c = 0;
		}
	}
	else if (id == 0x6bbd)
	{
		Rva0089CC80Object *proto;
		if (_strcmpi(reinterpret_cast<const char *>(key.m_data) + 8, "__proto__") == 0
			&& (proto = (Rva0089CC80Object *)map->m_proto08) != 0)
		{
			proto = (Rva0089CC80Object *)((unsigned int)proto & ~1u);
			proto->release();
			map->m_proto08 = 0;
		}
	}
}
