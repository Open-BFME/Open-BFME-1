// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include "../../../Common/System/xfer.h"
#include <vector>

template <typename T> class StringBase
{
	friend class AsciiString;

	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );

	unsigned char m_unreconstructed[ 0x1C ];
};

struct AttributeModifierEntry
{
	unsigned int m_nameKey;
	AsciiString m_name;
	unsigned int m_expirationFrame;
	unsigned int m_unknown;

	AttributeModifierEntry( const AsciiString &name )
		: m_nameKey( 0 ), m_name( name ), m_expirationFrame( 0 ), m_unknown( 0 )
	{
	}
};

class AttributeModifierPoolUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );

private:
	_STL::vector<AttributeModifierEntry> m_modifiers;
	unsigned int m_maxFrame;
	unsigned int m_activationFrames[ 7 ];
	unsigned int m_values[ 7 ];
};

void AttributeModifierPoolUpdate::xfer( Xfer *xfer )
{
	Xfer::Version version;
	version.data[ 0 ] = 1;
	version.data[ 1 ] = 3;
	*xfer == version;

	if ( xfer->IsLoading() )
	{
		m_modifiers.erase( m_modifiers.begin(), m_modifiers.end() );

		int count = 0;
		*xfer == count;
		for ( int index = 0; index < count; ++index )
		{
			AsciiString empty( "" );
			AttributeModifierEntry entry( empty );

			*xfer == entry.m_nameKey;
			if ( version.data[ 1 ] >= 3 )
				*xfer == entry.m_name;
			*xfer == entry.m_expirationFrame;
			*xfer == entry.m_unknown;
			m_modifiers.push_back( entry );
		}
	}
	else
	{
		int count = static_cast<int>( m_modifiers.size() );
		*xfer == count;
		for ( AttributeModifierEntry *source = m_modifiers.begin();
			source != m_modifiers.end(); ++source )
		{
			AttributeModifierEntry entry = *source;

			*xfer == entry.m_nameKey;
			if ( version.data[ 1 ] >= 3 )
				*xfer == entry.m_name;
			*xfer == entry.m_expirationFrame;
			*xfer == entry.m_unknown;
		}
	}

	if ( version.data[ 0 ] >= 2 )
	{
		for ( int index = 0; index < 7; ++index )
		{
			*xfer == m_activationFrames[ index ];
			*xfer == m_values[ index ];
		}
	}

	UpdateModule::xfer( xfer );
}
