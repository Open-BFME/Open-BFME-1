// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

// FILE: INIAudioEventInfo.cpp ////////////////////////////////////////////////
//
// The two field parsers the AudioEvent block table points at that are not
// INI:: statics: parseDelay at 0x000AFF40 and parsePitchShift at 0x000AFFF0,
// both file-scope in Zero Hour's INIAudioEventInfo.cpp and both named here by
// the string each pushes into its INIException.
//
// Retail keeps the DEBUG_ASSERTCRASH that Zero Hour writes: it throws
// INIException with the three-argument form, which is how the rest of this
// directory spells a failed INI check.
//
// AudioEventInfo's BFME layout is not otherwise known, so it is described here
// by the two offsets these bodies actually touch - m_audioName at +8 and the
// delay/pitch pair - rather than reconstructed whole.
//
///////////////////////////////////////////////////////////////////////////////

#include "Common/INIException.h"

typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	static Int scanInt( const char *token );
	static Real scanReal( const char *token );
};

struct BfmeAudioEventInfo
{
	char m_pad0[8];
	char *m_audioName;          // +0x08, a StringBase-backed AsciiString
	char m_pad1[0x10];
	Real m_pitchShiftMin;       // +0x1C
	Real m_pitchShiftMax;       // +0x20
	char m_pad2[4];
	Int m_delayMin;             // +0x28
	Int m_delayMax;             // +0x2C
};

// AsciiString::str() inlined: the characters sit past the eight-byte
// StringBase header, and an empty string reads as the shared "".
static const char *bfmeStr( const char *text )
{
	return text ? text + 8 : "";
}

// ?parseDelay@@YAXPAVINI@@PAX0PBX@Z
void parseDelay( INI *ini, void *instance, void *store, const void * /*userData*/ )
{
	BfmeAudioEventInfo *attribs = (BfmeAudioEventInfo *)store;

	Int min = INI::scanInt( ini->getNextToken() );
	Int max = INI::scanInt( ini->getNextToken() );

	if( min < 0 || min > max )
		throw INIException( 3, "Bad delay values for audio event %s", bfmeStr( attribs->m_audioName ) );

	attribs->m_delayMin = min;
	attribs->m_delayMax = max;
}

// ?parsePitchShift@@YAXPAVINI@@PAX1PBX@Z
void parsePitchShift( INI *ini, void *instance, void *store, const void * /*userData*/ )
{
	BfmeAudioEventInfo *attribs = (BfmeAudioEventInfo *)store;

	Real min = INI::scanReal( ini->getNextToken() );
	Real max = INI::scanReal( ini->getNextToken() );

	if( !(min < -100) && !(min > max) )
	{
		attribs->m_pitchShiftMin = 1.0f + min/100;
		attribs->m_pitchShiftMax = 1.0f + max/100;
		return;
	}

	throw INIException( 3, "Bad pitch shift values for audio event %s", bfmeStr( attribs->m_audioName ) );
}
