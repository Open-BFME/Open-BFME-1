// cl: /DNDEBUG /MD /EHs-c- /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/iniexception
// stlport
//
// The FieldParse table at VA 0x010813F8 owns AudioEventInfo's
// VolumeSliderMultiplier parser and writes its eight-byte entries at +0x8C.
// The retail table therefore proves the parser's class and field identity.

#define _STLP_NO_EXCEPTIONS
#include <vector>

typedef int Int;
typedef float Real;

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps );
	const char *getNextToken( const char *seps );
	const char *getSepsColon() const { return m_sepsColon; }
	static Int scanIndexList( const char *token, const char *const *nameList );
	static Real scanPercentToReal( const char *token );

private:
	char m_unreconstructed[0x41c];
	const char *m_sepsColon;
};

typedef int (__cdecl *LookupFn)( const char *, const char * );
extern "C" LookupFn g_lookup;

#include "Common/INIException.h"
extern const char *const g_012A8280[];

struct Gen_t_000b0910_p8pod
{
	Int m_slider;
	Real m_multiplier;
};

class AudioEventInfo
{
private:
	static void parseVolumeSliderMultiplier( INI *ini, void *instance, void *store,
		const void *userData );
};

// ?parseVolumeSliderMultiplier@AudioEventInfo@@CAXPAVINI@@PAX1PBX@Z
void AudioEventInfo::parseVolumeSliderMultiplier( INI *ini, void *, void *store,
	const void * )
{
	register LookupFn compare;
	Gen_t_000b0910_p8pod entry;
	entry.m_slider = -1;
	entry.m_multiplier = 1.0f;
	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 )
		goto slider_error;

	compare = g_lookup;
	if ( compare( token, "Slider" ) == 0 )
	{
		const char *slider = ini->getNextToken( ini->getSepsColon() );
		entry.m_slider = INI::scanIndexList( slider, g_012A8280 );
		token = ini->getNextTokenOrNull( ini->getSepsColon() );
		if ( token != 0 && compare( token, "Multiplier" ) == 0 )
		{
			entry.m_multiplier = INI::scanPercentToReal(
				ini->getNextToken( ini->getSepsColon() ) );
			((_STL::vector<Gen_t_000b0910_p8pod> *)store)->push_back( entry );
			return;
		}
		goto multiplier_error;
	}
	goto slider_error;

slider_error:
	{
		throw INIException( 3, "Slider:slidername expected after VolumeSliderMultiplier" );
	}

multiplier_error:
	{
		throw INIException( 3, "Multiplier:number expected after VolumeSliderMultiplier = Slider:slidername" );
	}
}
