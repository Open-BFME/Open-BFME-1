// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Open-BFME5: the wrapper and its AssetRegistry lookup implementation.

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

class NameKeyGenerator
{
public:
	unsigned int nameToLowercaseKey(const char *name);
};

struct AssetRegistryEntry
{
	AssetRegistryEntry *m_next;
	unsigned int m_key;
};

class AssetRegistry
{
public:
	bool Render_Obj_Exists_Impl(const char *name);

private:
	unsigned char m_unmodelled_000[0x2c];
	CRITICAL_SECTION m_lock;
	AssetRegistryEntry **m_buckets_begin;
	AssetRegistryEntry **m_buckets_end;
	unsigned char m_unmodelled_050[0x1a0];
	NameKeyGenerator *m_hash_context;
};

extern AssetRegistry *g_theAssetRegistry;

// ?Render_Obj_Exists_Impl@AssetRegistry@@QAE_NPBD@Z
bool AssetRegistry::Render_Obj_Exists_Impl(const char *name)
{
	register AssetRegistry *self = this;
	register CRITICAL_SECTION *critical = &self->m_lock;
	CriticalSectionLock lock(critical);
	unsigned int key = self->m_hash_context->nameToLowercaseKey(name);
	AssetRegistryEntry *entry = 0;
	if (key != 0)
	{
		entry = self->m_buckets_begin[
			key % (unsigned int)(self->m_buckets_end - self->m_buckets_begin)];
		while (entry != 0 && entry->m_key != key)
			entry = entry->m_next;
	}
	return entry != 0;
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
