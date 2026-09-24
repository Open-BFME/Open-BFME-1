// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x009EEF10. reverse/symbols.csv pins this name here because the
// matched Rva009EBDC0 calls it; the name is kept as pinned.
//
// The layout is the registry's, as the landed constructor
// ??0Gen_dtor_009eb9e0@@QAE@XZ size-checks it: the critical section at +0x2C,
// the hash_map<int, Gen_t_009f14c0_p12cd> at +0x44 and the iterator into it
// at +0x58 that the constructor sets to begin(). The AssetReference model is
// Find_Asset.cpp's: the raw-pointer constructor bumps the sixteen-bit count
// at +4 without a null test.
//
// What the body does: under the lock it walks the persistent +0x58 cursor,
// taking each entry's asset and advancing the cursor (the STLport bucket skip
// is inlined), and returns the first asset whose virtual slot +0x34 equals
// the filter at +0x1E8, or any asset when that filter is zero; an exhausted
// cursor returns an empty reference.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
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

class CountedAsset
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual int slot34();

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

struct Gen_t_009f14c0_p12cd
{
	CountedAsset *m_asset;
	int a[2];
	Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd(const Gen_t_009f14c0_p12cd &);
	~Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd &operator=(const Gen_t_009f14c0_p12cd &);
};

typedef _STL::hash_map<int, Gen_t_009f14c0_p12cd> GenAssetHash;

class AssetRegistry
{
public:
	AssetReference Get_Current_Asset();

private:
	unsigned char m_unmodelled_000[0x2c];
	CRITICAL_SECTION m_lock;
	GenAssetHash m_map44;
	GenAssetHash::iterator m_iterator58;
	unsigned char m_unmodelled_060[0x188];
	int m_filter1e8;
};

AssetReference AssetRegistry::Get_Current_Asset()
{
	CriticalSectionLock lock(&m_lock);
	while (m_iterator58 != m_map44.end())
	{
		CountedAsset *asset = (*m_iterator58).second.m_asset;
		++m_iterator58;
		if (m_filter1e8 == 0 || m_filter1e8 == asset->slot34())
			return AssetReference(asset);
	}
	return AssetReference();
}
