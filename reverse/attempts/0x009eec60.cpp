// ?Find_Asset@AssetRegistry@@QAE?AVAssetReference@@PBD@Z
// partial score=0.9 date=2026-09-19
// cl: /DNDEBUG /MD /EHsc

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToLowercaseKey( const char *name );
};

struct BfmeLockTEA
{
	char m_pad[0x18];
	bool m_armed;
};

extern "C" __declspec(dllimport) void __stdcall bfmeEnterTEA( BfmeLockTEA *lock );
extern "C" __declspec(dllimport) void __stdcall bfmeLeaveTEA( BfmeLockTEA *lock );

class TEAGuard
{
public:
	TEAGuard( BfmeLockTEA *lock ) : m_lock( lock )
	{
		bfmeEnterTEA( m_lock );
	}
	~TEAGuard()
	{
		bfmeLeaveTEA( m_lock );
	}

private:
	BfmeLockTEA *m_lock;
};

class AssetReference
{
public:
	void *m_object;
};

struct AssetRegistryNode
{
	AssetRegistryNode *m_next;
	volatile NameKeyType m_key;
	void *m_asset;
};

class AssetRegistryBuckets
{
public:
	AssetRegistryNode **begin()
	{
		return m_begin;
	}

	unsigned int size() const
	{
		return (unsigned int)( m_end - m_begin );
	}

private:
	AssetRegistryNode **m_begin;
	AssetRegistryNode **m_end;
	AssetRegistryNode **m_capacity;
};

class AssetRegistry
{
public:
	AssetReference Find_Asset( const char *name );

private:
	char m_pad_000[0x2c];
	BfmeLockTEA m_lock;
	AssetRegistryBuckets m_buckets;
	char m_pad_054[0x19c];
	NameKeyGenerator *m_nameKeyGenerator;
};

AssetReference AssetRegistry::Find_Asset( const char *name )
{
	volatile int state = 0;
	AssetReference result;
	TEAGuard lock( &m_lock );
	NameKeyType key = NAMEKEY_INVALID;

	key = m_nameKeyGenerator->nameToLowercaseKey( name );
	if ( key != NAMEKEY_INVALID )
	{
		unsigned int bucketCount = m_buckets.size();
		AssetRegistryNode *node = m_buckets.begin()[(unsigned int)key % bucketCount];
		while ( node )
		{
			if ( node->m_key == key )
				goto found;
			node = node->m_next;
		}

	found:
		if ( node )
		{
			result.m_object = node->m_asset;
			++*(unsigned short *)((char *)node->m_asset + 4);
			return result;
		}
	}
	result.m_object = 0;
	return result;
}
