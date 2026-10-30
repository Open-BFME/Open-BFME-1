// ?rva003CB640@LivingWorldRegionManager@@QAEXXZ
// partial score=0.1573 date=2026-10-30
// cl: /DNDEBUG /MD
// Retail 0x003CB640.  The owner is established by the 0x003C8880
// constructor's 0x010EE010 vtable and the 0x003CB790 caller (see
// LivingWorldRegionManager_Rva003C8B90.cpp); the method name is unknown.
// Body: clear three totals, then sum three counters of every region whose
// +0xB4 key passes the obfuscated hook wrapper Rva003C92A0
// (BigObfHookWrappers.cpp), which retail inlines here.

typedef int (__cdecl *BigObfHook)( void *, void *, __int64 );

struct BigObfSlot
{
	BigObfHook  m_hook;
	BigObfHook  m_alt;
	char        m_pad[ 0x80 ];
	void       *m_a;
	void       *m_b;
};

extern BigObfSlot g_Slot012BE394;

class Obf003C87A0
{
public:
	Obf003C87A0( int *a, int *b );
	unsigned int m_bits[ 8 ];
};

int __cdecl Gen003C78B0( int a, int b );

inline int __cdecl Rva003C92A0( int a, int b )
{
	BigObfHook hook = g_Slot012BE394.m_hook;
	if ( hook )
		goto hot;
	if ( g_Slot012BE394.m_alt )
	{
hot:
		void *pa = g_Slot012BE394.m_a;
		void *pb = g_Slot012BE394.m_b;
		Obf003C87A0 o( &a, &b );
		return hook( pa, pb, (__int64)(int)&o );
	}
	return Gen003C78B0( a, b );
}

class LivingWorldRegion
{
public:
	char m_unmodelled00[0x78];
	int m_count78;
	int m_count7C;
	int m_count80;
	char m_pad84[0x30];
	int m_key;
};

struct LivingWorldRegionVector
{
	LivingWorldRegion **m_begin;
	LivingWorldRegion **m_end;
	LivingWorldRegion **m_capacity;

	unsigned int size() const { return m_end - m_begin; }
	LivingWorldRegion *operator[]( unsigned int i ) const { return m_begin[i]; }
};

class Rva003CB640Campaign
{
public:
	char m_unmodelled00[0x30];
	LivingWorldRegionVector m_regions;
};

class LivingWorldRegionManager
{
public:
	virtual ~LivingWorldRegionManager();

	void rva003CB640();

private:
	Rva003CB640Campaign *m_campaign;
	char m_unmodelled08[0x2C];
	int m_total34;
	int m_total38;
	int m_total3C;
};

void LivingWorldRegionManager::rva003CB640()
{
	m_total34 = 0;
	m_total38 = 0;
	m_total3C = 0;
	LivingWorldRegionVector &regions = m_campaign->m_regions;
	for ( unsigned int i = 0; i < regions.size(); ++i )
	{
		LivingWorldRegion *region = regions[i];
		int a = region->m_key;
		int b = a;
		int result;
		BigObfHook hook = g_Slot012BE394.m_hook;
		if ( hook )
			goto hot;
		if ( g_Slot012BE394.m_alt )
		{
hot:
			void *pa = g_Slot012BE394.m_a;
			void *pb = g_Slot012BE394.m_b;
			Obf003C87A0 o( &a, &b );
			result = hook( pa, pb, (__int64)(int)&o );
		}
		else
			result = Gen003C78B0( a, b );
		if ( result == 1 )
		{
			m_total34 += region->m_count7C;
			m_total38 += region->m_count78;
			m_total3C += region->m_count80;
		}
	}
}
