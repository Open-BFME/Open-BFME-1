// ?Find_Asset@AssetRegistry@@QAE?AVAssetReference@@PBD@Z
// partial score=0.85 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AssetRegistry::Find_Asset, retail 0x009EEC60 (185 bytes).
// TEA-locked NameKeyGenerator bucket lookup; reuses the bfmeEnterTEA/
// bfmeLeaveTEA imports already pinned by Rva00886F10TeaLock.cpp.

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

extern "C" __declspec(dllimport) void __stdcall bfmeEnterTEA(BfmeLockTEA* lock);
extern "C" __declspec(dllimport) void __stdcall bfmeLeaveTEA(BfmeLockTEA* lock);

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
	NameKeyType m_key;
	void *m_asset;
};

class AssetRegistry
{
public:
	AssetReference Find_Asset( const char *name );

private:
	unsigned char m_unmodelled_000[0x2C];
	BfmeLockTEA m_lock;
	AssetRegistryNode **m_buckets;
	AssetRegistryNode **m_bucketsEnd;
	unsigned char m_unmodelled_050[0x1A0];
	NameKeyGenerator *m_nameKeyGenerator;
};

AssetReference AssetRegistry::Find_Asset( const char *name )
{
	AssetReference result;
	TEAGuard lock( &m_lock );

	NameKeyType key = m_nameKeyGenerator->nameToLowercaseKey( name );
	if ( key != NAMEKEY_INVALID )
	{
		unsigned int bucketCount = (unsigned int)( m_bucketsEnd - m_buckets );
		AssetRegistryNode *node = m_buckets[(unsigned int)key % bucketCount];
		while ( node && node->m_key != key )
			node = node->m_next;

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
