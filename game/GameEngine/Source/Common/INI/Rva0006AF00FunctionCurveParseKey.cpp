// cl: /Iinputs/reference/shims/iniexception /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef float Real;
typedef int Int;

#include "Common/INIException.h"

class INI
{
public:
	const char *getNextSubToken( const char *expected );
	const char *getNextToken( const char *separators );
	const char *getNextTokenOrNull( const char *separators );
	const char *getSeps( void ) const { return m_seps; }
	static Real scanReal( const char *token );

private:
	char m_padding[ 0x41c ];
	const char *m_seps;
};

class Rva0006AB90FunctionCurve
{
public:
	void addKey( Real time, Real value, const Real *inTangent,
		const Real *outTangent );
};

extern void j_0000fcc2();
typedef Real (__cdecl *ScanReal)( const char *token );

class Rva0006AF00FunctionCurve
{
public:
	static void parseKey( INI *ini, void *instance, void *store,
		const void *userData );
};

// ?parseKey@Rva0006AF00FunctionCurve@@SAXPAVINI@@PAX1PBX@Z
void Rva0006AF00FunctionCurve::parseKey( INI *ini, void *, void *,
	const void *userData )
{
	Real time = INI::scanReal( ini->getNextSubToken( "T" ) );
	Real value = INI::scanReal( ini->getNextSubToken( "V" ) );
	const Real *inTangent = 0;
	const Real *outTangent = 0;
	Real inValue;
	Real outValue;
	Int count = 0;

	for ( count = 0; count < 2; ++count )
	{
		const char *token = ini->getNextTokenOrNull( ini->getSeps() );
		if ( token == 0 )
			break;

		if ( inTangent == 0 && token[ 0 ] == 'I' && token[ 1 ] == 0 )
		{
			inValue = ((ScanReal)j_0000fcc2)( ini->getNextToken( ini->getSeps() ) );
			inTangent = &inValue;
		}
		else if ( outTangent == 0 && token[ 0 ] == 'O' && token[ 1 ] == 0 )
		{
			outValue = ((ScanReal)j_0000fcc2)( ini->getNextToken( ini->getSeps() ) );
			outTangent = &outValue;
		}
		else
			throw INIException( 3, "'I' or 'O' expected, and only one of them" );

	}

	((Rva0006AB90FunctionCurve *)userData)->addKey( time, value,
		inTangent, outTangent );
}
