// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The WeatherData block -- BFME-only, and distinct from the "Weather" block in
// Snow.cpp. This one names one of five weather types and configures it, so the
// keyword takes an argument where most single-instance blocks take none.
//
// The five names come from the retail table at 0x010EBC18, and the entries are
// eight bytes apiece -- a sound and a lightning flag -- which is why the parser
// indexes with esi*8 rather than by a WeatherSetting stride.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

struct WeatherData
{
	Int m_weatherSound;			// 0x00  WeatherSound, through a custom parse proc
	Bool m_hasLightning;		// 0x04  HasLightning

	static const FieldParse m_fieldParseTable[];
};

// TheGlobalWeatherSystem is named by GameEngine::init's string literal at
// 0x012F0FE0; its class is BFME-only and unnamed, so it is reached through a
// local view.
struct RetailGlobalWeatherSystem
{
	char m_unknown00[ 0x28 ];
	WeatherData m_weather[ 5 ];		// 0x28
};

extern RetailGlobalWeatherSystem *TheGlobalWeatherSystem;

static const char *TheWeatherNames[] =
{
	"NONE", "CLOUDY", "RAINY", "CLOUDYRAINY", "SUNNY"
};

void parseWeatherData( INI *ini )
{
	if( retailLoadType( ini ) != INI_LOAD_OVERWRITE )
		throw INIException( 3, "Cannot define WeatherData in map.ini" );

	const char *token = ini->getNextToken();

	Int which;
	for( which = 0; which < 5; which++ )
		if( _strcmpi( TheWeatherNames[ which ], token ) == 0 )
			break;

	if( which == 5 )
		throw INIException( 3, "Unknown weather type %s", token );

	ini->initFromINI( &TheGlobalWeatherSystem->m_weather[ which ],
										WeatherData::m_fieldParseTable );
}
