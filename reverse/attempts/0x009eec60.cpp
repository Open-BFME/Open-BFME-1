// ?Find_Asset@AssetRegistry@@QAE?AVAssetReference@@PBD@Z
// partial score=0.78 date=2026-09-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: AssetRegistry::Find_Asset, retail 0x009EEC60 (185 bytes).

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToLowercaseKey( const char *name );
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

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection( void *lock );
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection( void *lock );

class CriticalSectionGuard
{
public:
	CriticalSectionGuard( void *lock ) : m_lock( lock )
	{
		EnterCriticalSection( m_lock );
	}
	~CriticalSectionGuard()
	{
		LeaveCriticalSection( m_lock );
	}

private:
	void *m_lock;
};

class AssetRegistry
{
public:
	AssetReference Find_Asset( const char *name );

private:
	unsigned char m_unmodelled_000[0x2C];
	unsigned char m_lock[0x1C];
	AssetRegistryNode **m_buckets;
	AssetRegistryNode **m_bucketsEnd;
	unsigned char m_unmodelled_050[0x1A0];
	NameKeyGenerator *m_nameKeyGenerator;
};

AssetReference AssetRegistry::Find_Asset( const char *name )
{
	AssetReference result;
	CriticalSectionGuard lock( m_lock );

	NameKeyType key = m_nameKeyGenerator->nameToLowercaseKey( name );
	unsigned int bucketCount = (unsigned int)( m_bucketsEnd - m_buckets );
	AssetRegistryNode *node = m_buckets[key % bucketCount];
	while ( node && node->m_key != key )
		node = node->m_next;

	if ( node )
	{
		result.m_object = node->m_asset;
		++*(unsigned short *)((char *)node->m_asset + 4);
	}
	else
	{
		result.m_object = 0;
	}

	return result;
}
