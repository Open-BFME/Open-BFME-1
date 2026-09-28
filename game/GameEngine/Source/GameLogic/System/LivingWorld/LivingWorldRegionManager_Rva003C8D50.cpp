// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x003C8D50. The receiver is LivingWorldRegionManager: the landed
// 0x003C8A50 and 0x003C8C60 bodies prove the +0x04 campaign, its +0x30 vector
// of LivingWorldRegion pointers and the region name at +0x04, and the
// manager's own transfer body at 0x003CA0E0 calls this one with its Xfer.
// The stack parameter is that Xfer: slot +0x04 isLoading, +0x28 xferVersion,
// +0x68 xferAsciiString and +0x78 xferInt agree with the landed Xfer shims in
// LargeGroupAudioKeyMapXfer.cpp and Rva003A5A10Xfer.cpp. Each region is
// handed the Xfer through its vtable 0x01117258 slot 3, whose body at
// 0x0061B170 transfers the region's own fields. The method name is not
// recovered, so it stays address-derived.

#include "ascii_string.h"

typedef bool Bool;
typedef unsigned char UnsignedByte;

// Retail sorts this record among the four-byte locals, so it fills a whole
// dword slot (as in XferListAsciiStringUINT.cpp); the upper half is unused.
struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	unsigned short m_padding;
};

class Xfer
{
public:
	virtual void _pad00();
	virtual Bool isLoading();
	virtual void _pad02(); virtual void _pad03(); virtual void _pad04();
	virtual void _pad05(); virtual void _pad06(); virtual void _pad07();
	virtual void _pad08(); virtual void _pad09();
	virtual void xferVersion( XferVersion *version );
	virtual void _pad0b(); virtual void _pad0c(); virtual void _pad0d();
	virtual void _pad0e(); virtual void _pad0f(); virtual void _pad10();
	virtual void _pad11(); virtual void _pad12(); virtual void _pad13();
	virtual void _pad14(); virtual void _pad15(); virtual void _pad16();
	virtual void _pad17(); virtual void _pad18(); virtual void _pad19();
	virtual void xferAsciiString( AsciiString *value );
	virtual void _pad1b(); virtual void _pad1c(); virtual void _pad1d();
	virtual void xferInt( int *value );
};

class LivingWorldRegion
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual void xfer( Xfer *xfer );

	AsciiString m_name;
};

// STLport vector shape: operator[] goes through begin(), which is what
// gives retail its register choice in the save loop.
struct LivingWorldRegionVector
{
	LivingWorldRegion **begin() { return m_begin; }
	unsigned int size() const { return (unsigned int)( m_end - m_begin ); }
	LivingWorldRegion *&operator[]( unsigned int index ) { return *( begin() + index ); }

	LivingWorldRegion **m_begin;
	LivingWorldRegion **m_end;
	LivingWorldRegion **m_capacity;
};

class LivingWorldRegionCampaign
{
public:
	unsigned char m_unmodelled00[0x30];
	LivingWorldRegionVector m_regions;
};

class LivingWorldRegionManager
{
public:
	void rva003C8D50( Xfer *xfer );
	LivingWorldRegion *rva003C8A50( const AsciiString &regionName );

private:
	void *m_vtable;
	LivingWorldRegionCampaign *m_currentCampaign;
};

void LivingWorldRegionManager::rva003C8D50( Xfer *xfer )
{
	{
		XferVersion version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		xfer->xferVersion( &version );
	}

	LivingWorldRegionVector *regions = &m_currentCampaign->m_regions;

	if( xfer->isLoading() )
	{
		int count;
		xfer->xferInt( &count );

		for( int i = 0; i < count; ++i )
		{
			AsciiString name;
			xfer->xferAsciiString( &name );

			LivingWorldRegion *region = rva003C8A50( name );
			if( region != 0 )
				region->xfer( xfer );
		}
	}
	else
	{
		int count = regions->size();
		xfer->xferInt( &count );

		for( int i = 0; i < count; ++i )
		{
			AsciiString name( ( *regions )[ i ]->m_name );
			xfer->xferAsciiString( &name );

			( *regions )[ i ]->xfer( xfer );
		}
	}
}
