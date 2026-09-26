// ?parseFontDefaultSettings@@YAXPAVINI@@@Z
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager

// The block registry names 0x00477320 as FontDefaultSettings. The FieldParse
// table at 0x010F76AC names its Antialiased field at offset 0x08.

#include "ascii_string.h"

typedef float Real;

struct FieldParse;

class INIException
{
public:
	INIException( int code, const char *format, ... );
	INIException( const INIException &other );

private:
	char *m_failureMessage;
	int m_argCount;
};

class INI
{
public:
	AsciiString getNextQuotedAsciiString();
	const char *getNextTokenOrNull( const char *separators = 0 );
	void initFromINI( void *instance, const FieldParse *parseTable );
};

extern "C" __declspec( dllimport ) double __cdecl atof( const char *text );

class FontLibrary;
extern FontLibrary *TheFontLibrary;

// ?BfmeZeroRange@@3MB, the shared 0.0f constant at 0x01075350.
extern const Real BfmeZeroRange;

class RefCounted
{
public:
	virtual void release( unsigned int count );

	int m_references;
};

class __declspec( novtable ) FontDefaultSettings : public RefCounted
{
	public:
	FontDefaultSettings()
	{
		m_references = 0;
		*(unsigned int *)this = 0x010F7624;
	}

	unsigned char m_antialiased;
};

extern void j_000067a8();
extern void j_0001ab6d();
extern void j_0002e622();

static __forceinline void releaseSettings( RefCounted *settings )
{
	if ( --settings->m_references <= 0 )
	{
		settings->release( 1 );
	}
}

class FontDefaultSettingsRef
{
public:
	FontDefaultSettingsRef( FontDefaultSettings *value ) : m_value( value )
	{
		if ( m_value != 0 )
			++m_value->m_references;
	}

	FontDefaultSettingsRef &operator=( const FontDefaultSettingsRef &other )
	{
		if ( this != &other )
		{
			FontDefaultSettings *value = other.m_value;
			if ( value != 0 )
				++value->m_references;
			if ( m_value != 0 )
				releaseSettings( m_value );
			m_value = 0;
			m_value = value;
		}
		return *this;
	}

	~FontDefaultSettingsRef()
	{
		if ( m_value != 0 )
			releaseSettings( m_value );
	}

	FontDefaultSettings *m_value;
};

// The retail destructor at 0x00476440 releases a ref-counted pointer at +0x08
// and an out-of-line member at +0x0C; operator new here asks for 0x18 bytes.
class Rva00476440 : public RefCounted
{
public:
	Rva00476440();

	FontDefaultSettingsRef m_ref08;
	char m_data[ 0x0C ];
};

class Rva00476440Ref
{
public:
	Rva00476440Ref( Rva00476440 *value ) : m_value( value )
	{
		if ( m_value != 0 )
			++m_value->m_references;
	}

	Rva00476440Ref &operator=( Rva00476440 *value )
	{
		if ( value != m_value )
		{
			if ( m_value != 0 )
			{
				releaseSettings( m_value );
				m_value = 0;
			}
			m_value = value;
			if ( m_value != 0 )
				++m_value->m_references;
		}
		return *this;
	}

	Rva00476440 *m_value;
};

class FontNameMapRoute
{
public:
	typedef Rva00476440Ref * (FontNameMapRoute::*Call)( const AsciiString & );
};

class FontSizeMapRoute
{
public:
	typedef FontDefaultSettingsRef * (FontSizeMapRoute::*Call)( const int & );
};

// ?parseFontDefaultSettings@@YAXPAVINI@@@Z
void __cdecl parseFontDefaultSettings( INI *ini )
{
	union { Real value; int slot; } pointSize;
	AsciiString name = ini->getNextQuotedAsciiString();
	pointSize.value = -1.0f;
	const char *token = ini->getNextTokenOrNull();
	if ( token != 0 )
	{
		pointSize.value = (Real)atof( token );
		if ( pointSize.value <= BfmeZeroRange )
			throw INIException( 3, "Invalid font point size specified: %f.  Must be greater than or equal to 1", pointSize.value );
	}

	FontDefaultSettingsRef settings( new FontDefaultSettings );
	settings.m_value->m_antialiased = 1;
	ini->initFromINI( settings.m_value, (const FieldParse *)0x010F76AC );

	union { void (*address)(); FontNameMapRoute::Call member; } findName =
		{ j_0002e622 };
	Rva00476440Ref *nameSlot =
		( ( (FontNameMapRoute *)((char *)TheFontLibrary + 0x10) )->*findName.member )( name );
	if ( nameSlot->m_value == 0 )
	{
		*nameSlot = new Rva00476440;
	}

	if ( pointSize.value >= BfmeZeroRange )
	{
		int size = (int)pointSize.value;
		Rva00476440 *table = nameSlot->m_value;
		union { void (*address)(); FontSizeMapRoute::Call member; } findSize =
			{ j_0001ab6d };
		FontDefaultSettingsRef *sizeSlot =
			( ( (FontSizeMapRoute *)((char *)table + 0x0C) )->*findSize.member )( size );
		*sizeSlot = settings;
	}
	else
	{
		nameSlot->m_value->m_ref08 = settings;
	}
}
