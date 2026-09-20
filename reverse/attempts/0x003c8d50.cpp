// ?rva003C8D50@LivingWorldRegionManager@@QAEXPAVRegionVisitor@@@Z
// partial score=0.93 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x003C8D50. Receiver is LivingWorldRegionManager (proven by the
// manager vtable and the campaign vector already established in
// LivingWorldRegionManager_Rva003C8A50.cpp: m_currentCampaign at +4, its
// +0x30 vector<LivingWorldRegion*>, LivingWorldRegion's m_name at +4). The
// stack parameter is an opaque region-visitor interface (identity
// unrecovered; caller d_003ca0e0.asm is itself an unmatched dump) with
// four used vtable slots: +0x04 selects between a named-filter walk and a
// full-campaign walk, +0x28 is an init call, +0x68 exchanges an
// AsciiString with the visitor (output in the named-filter branch, input
// in the full walk), and +0x78 both reads and reports a region count.
// Each visited LivingWorldRegion is itself polymorphic and is handed the
// visitor through its own vtable slot 3 (+0xC) -- an accept()-style call.

#include "ascii_string.h"

typedef bool Bool;

class LivingWorldRegion
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual void accept( void *visitor );

	AsciiString m_name;
};

// Opaque region-visitor interface; only the four slots this body calls are
// named, the rest are address-derived padding to keep the vtable shape.
class RegionVisitor
{
public:
	virtual void _pad00();
	virtual Bool hasNamedFilter();
	virtual void _pad02(); virtual void _pad03(); virtual void _pad04();
	virtual void _pad05(); virtual void _pad06(); virtual void _pad07();
	virtual void _pad08(); virtual void _pad09();
	virtual void initFilter( void *state );
	virtual void _pad0b(); virtual void _pad0c(); virtual void _pad0d();
	virtual void _pad0e(); virtual void _pad0f(); virtual void _pad10();
	virtual void _pad11(); virtual void _pad12(); virtual void _pad13();
	virtual void _pad14(); virtual void _pad15(); virtual void _pad16();
	virtual void _pad17(); virtual void _pad18(); virtual void _pad19();
	virtual void exchangeName( AsciiString *name );
	virtual void _pad1b(); virtual void _pad1c(); virtual void _pad1d();
	virtual void getOrReportCount( int *count );
};

struct LivingWorldRegionCampaign
{
	LivingWorldRegion **m_begin;
	LivingWorldRegion **m_end;
};

class LivingWorldRegionManager
{
public:
	void rva003C8D50( RegionVisitor *visitor );
	LivingWorldRegion *rva003C8A50( const AsciiString &regionName );

private:
	void *m_vtable;
	char *m_currentCampaign;
};

void LivingWorldRegionManager::rva003C8D50( RegionVisitor *visitor )
{
#pragma pack( push, 1 )
	struct FilterState
	{
		int m_field0;
		unsigned char m_a;
		unsigned char m_b;
	};
#pragma pack( pop )
	{
		FilterState filterState;
		filterState.m_a = 1;
		filterState.m_b = 1;
		visitor->initFilter( &filterState );
	}

	LivingWorldRegionCampaign *campaign =
		( LivingWorldRegionCampaign * )( m_currentCampaign + 0x30 );

	if( visitor->hasNamedFilter() )
	{
		int count;
		visitor->getOrReportCount( &count );

		for( int i = 0; i < count; ++i )
		{
			AsciiString name;
			visitor->exchangeName( &name );

			LivingWorldRegion *region = rva003C8A50( name );
			if( region != 0 )
				region->accept( visitor );
		}
	}
	else
	{
		int count = static_cast<int>( campaign->m_end - campaign->m_begin );
		visitor->getOrReportCount( &count );

		for( int i = 0; i < count; ++i )
		{
			AsciiString name( campaign->m_begin[ i ]->m_name );
			visitor->exchangeName( &name );

			campaign->m_begin[ i ]->accept( visitor );
		}
	}
}
