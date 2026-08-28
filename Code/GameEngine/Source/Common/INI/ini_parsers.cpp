// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Ireference/shims/ini_inline /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ??0DamDieModuleData@@: Code/GameEngine/Source/GameLogic/Object/Die/DamDie.cpp
// readable body of ??0EjectPilotDieModuleData@@: Code/GameEngine/Source/GameLogic/Object/Die/EjectPilotDie.cpp
// readable body of ??0HiveStructureBodyModuleData@@: Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp
// readable body of ??0JetAIUpdateModuleData@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/JetAIUpdate.cpp
// readable body of ??0MinefieldBehaviorModuleData@@: Code/GameEngine/Source/GameLogic/Object/Behavior/MinefieldBehavior.cpp
// readable body of ??0RailedTransportDockUpdateModuleData@@QAE@XZ: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate.cpp
// readable body of ??0RebuildHoleExposeDieModuleData@@: Code/GameEngine/Source/GameLogic/Object/Die/RebuildHoleExposeDie.cpp
// readable body of ??0W3DModelDrawModuleData@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp
// readable body of ??0W3DOverlordAircraftDrawModuleData@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DOverlordAircraftDraw.cpp
// readable body of ?getNextSubToken@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?initFromINI@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?initFromINIMultiProc@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAngleReal@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAsciiStringVector@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAsciiStringVectorAppend@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseBitInInt32@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseBool@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseByteSizedIndexList@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseColorInt@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseIndexList@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseInt@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseLookupList@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parsePercentToReal@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parsePositiveNonZeroReal@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseRGBAColorInt@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseRGBColor@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseReal@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseShort@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseUnsignedByte@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseUnsignedInt@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseUnsignedShort@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
//
// The other half of retail's INI reader. BFME compiles INI's field parsers in
// two translation units and the split is visible in the binary: these eleven sit
// at 0x00851050..0x00852E60 and INLINE INI::getNextToken (each carries its own
// "Expected additional data after '%s'" throw), while the template/store parsers
// -- parseScience, parseThingTemplate, parseFXList and friends -- sit in a
// different arena at 0x000B8E80..0x000BB040 and CALL it out of line. A single TU
// cannot produce both, so ini.cpp keeps that group and this file takes this one.
//
// The include path puts reference/shims/ini_inline first: its Common/INI.h is
// the same header with getNextToken inline and BFME's member layout (m_seps at
// +0x414, with no 8K m_readBuffer ahead of m_buffer).
#include "PreRTS.h"
#include "Common/INI.h"

//-------------------------------------------------------------------------------------------------
void INI::parseIndexList( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	ConstCharPtrArray nameList = (ConstCharPtrArray)userData;
	*(Int *)store = scanIndexList(ini->getNextToken(), nameList);
}

//-------------------------------------------------------------------------------------------------
void INI::parseByteSizedIndexList( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	ConstCharPtrArray nameList = (ConstCharPtrArray)userData;
	Int value = scanIndexList(ini->getNextToken(), nameList);
	if (value < 0 || value > 255)
	{
		DEBUG_CRASH(("Bad index list INI::parseByteSizedIndexList"));
		// retail throws a plain int 1 here, not ERROR_BUG: the ThrowInfo these sites
		// push (0x012454C0) describes ".H" (int), and ERROR_BUG really is 0xdead0001
		// in BFME -- ini.cpp's matched parseScience carries that immediate.
		throw 1;
	}
	*(Byte *)store = (Byte)value;
}

//-------------------------------------------------------------------------------------------------
void INI::parseLookupList( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	ConstLookupListRecArray lookupList = (ConstLookupListRecArray)userData;
	*(Int *)store = scanLookupList(ini->getNextToken(), lookupList);
}

//-------------------------------------------------------------------------------------------------
void INI::parseUnsignedByte( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();
	Int value = scanInt(token);
	if (value < 0 || value > 255)
	{
		DEBUG_CRASH(("Bad value INI::parseUnsignedByte"));
		// retail throws a plain int 1 here, not ERROR_BUG: the ThrowInfo these sites
		// push (0x012454C0) describes ".H" (int), and ERROR_BUG really is 0xdead0001
		// in BFME -- ini.cpp's matched parseScience carries that immediate.
		throw 1;
	}
	*(Byte *)store = (Byte)value;
}

//-------------------------------------------------------------------------------------------------
void INI::parseShort( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();
	Int value = scanInt(token);
	if (value < -32768 || value > 32767)
	{
		DEBUG_CRASH(("Bad value INI::parseShort"));
		// retail throws a plain int 1 here, not ERROR_BUG: the ThrowInfo these sites
		// push (0x012454C0) describes ".H" (int), and ERROR_BUG really is 0xdead0001
		// in BFME -- ini.cpp's matched parseScience carries that immediate.
		throw 1;
	}
	*(Short *)store = (Short)value;
}

//-------------------------------------------------------------------------------------------------
void INI::parseUnsignedShort( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();
	Int value = scanInt(token);
	if (value < 0 || value > 65535)
	{
		DEBUG_CRASH(("Bad value INI::parseUnsignedShort"));
		// retail throws a plain int 1 here, not ERROR_BUG: the ThrowInfo these sites
		// push (0x012454C0) describes ".H" (int), and ERROR_BUG really is 0xdead0001
		// in BFME -- ini.cpp's matched parseScience carries that immediate.
		throw 1;
	}
	*(UnsignedShort *)store = (UnsignedShort)value;
}

//-------------------------------------------------------------------------------------------------
void INI::parseUnsignedInt( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();
	*(UnsignedInt *)store = scanUnsignedInt(token);

}

//-------------------------------------------------------------------------------------------------
void INI::parseReal( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();
	*(Real *)store = scanReal(token);

}

//-------------------------------------------------------------------------------------------------
void INI::parseAngleReal( INI *ini, void * /*instance*/, 
																			void *store, const void *userData )
{
	const char *token = ini->getNextToken();

	const Real RADS_PER_DEGREE = PI / 180.0f;
	*(Real *)store = scanReal( token ) * RADS_PER_DEGREE;

}

//-------------------------------------------------------------------------------------------------
void INI::parseBool( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	*(Bool*)store = INI::scanBool(ini->getNextToken());
}

//-------------------------------------------------------------------------------------------------
void INI::parseBitInInt32( INI *ini, void *instance, void *store, const void* userData )
{
	UnsignedInt* s = (UnsignedInt*)store;
	UnsignedInt mask = (UnsignedInt)userData;

	if (INI::scanBool(ini->getNextToken()))
		*s |= mask;
	else
		*s &= ~mask;
}

//-------------------------------------------------------------------------------------------------
void INI::parsePercentToReal( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken(ini->getSepsPercent());
	Real *theReal = (Real *)store;
	*theReal = scanPercentToReal(token);

}

//-------------------------------------------------------------------------------------------------
void INI::parsePositiveNonZeroReal( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();
	*(Real *)store = scanReal(token);
	if (*(Real *)store <= 0.0f)
		throw INIException(3, "invalid Real value %1.7f -- expected > 0", *(Real *)store);

}

//-------------------------------------------------------------------------------------------------
const char* INI::getNextSubToken(const char* expected)
{
	const char* token = getNextToken(getSepsColon());
	if (stricmp(token, expected) != 0)
		throw INIException(3, "Expected '%s' but found '%s'", expected, token);
	return getNextToken(getSepsColon());
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/INI_parseBitString32_Thunk.cpp
// ?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z present-unmatched
void INI::parseBitString32( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	ConstCharPtrArray flagList = (ConstCharPtrArray)userData;
	UnsignedInt *bits = (UnsignedInt *)store;

	if( flagList == NULL || flagList[ 0 ] == NULL)
	{
		DEBUG_ASSERTCRASH( flagList, ("INTERNAL ERROR! parseBitString32: No flag list provided!\n") );
		throw INI_INVALID_NAME_LIST;
	}

	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	// loop through all tokens
	for (const char *token = ini->getNextTokenOrNull(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (stricmp(token, "NONE") == 0)
		{
			if (foundNormal || foundAddOrSub)
			{
				DEBUG_CRASH(("you may not mix normal and +- ops in bitstring lists"));
				throw INI_INVALID_NAME_LIST;
			}
			*bits = 0;
			break;
		}

		if (token[0] == '+')
		{
			if (foundNormal)
			{
				DEBUG_CRASH(("you may not mix normal and +- ops in bitstring lists"));
				throw INI_INVALID_NAME_LIST;
			}
			Int bitIndex = INI::scanIndexList(token+1, flagList);	// this throws if the token is not found
			*bits |= (1 << bitIndex);
			foundAddOrSub = true;
		}
		else if (token[0] == '-')
		{
			if (foundNormal)
			{
				DEBUG_CRASH(("you may not mix normal and +- ops in bitstring lists"));
				throw INI_INVALID_NAME_LIST;
			}
			Int bitIndex = INI::scanIndexList(token+1, flagList);	// this throws if the token is not found
			*bits &= ~(1 << bitIndex);
			foundAddOrSub = true;
		}
		else
		{
			if (foundAddOrSub)
			{
				DEBUG_CRASH(("you may not mix normal and +- ops in bitstring lists"));
				throw INI_INVALID_NAME_LIST;
			}

			if (!foundNormal)
				*bits = 0;

			Int bitIndex = INI::scanIndexList(token, flagList);	// this throws if the token is not found
			*bits |= (1 << bitIndex);
			foundNormal = true;
		}
	}
}

//-------------------------------------------------------------------------------------------------
void INI::parseRGBColor( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char* names[3] = { "R", "G", "B" };
	Int colors[3];
	for( Int i = 0; i < 3; i++ )
	{
		colors[i] = scanInt(ini->getNextSubToken(names[i]));
		if( colors[ i ] < 0 || colors[ i ] > 255 )
			throw INIException(3, "color value %s=%i out of range (0..255)", names[i], colors[i]);
	}

	// Retail multiplies by the 1/255 constant at 0x0107C64C rather than dividing.
	RGBColor *theColor = (RGBColor *)store;
	theColor->red		= (Real)colors[ 0 ] * (1.0f / 255.0f);
	theColor->green = (Real)colors[ 1 ] * (1.0f / 255.0f);
	theColor->blue	= (Real)colors[ 2 ] * (1.0f / 255.0f);

}

//-------------------------------------------------------------------------------------------------
void INI::parseRGBAColorInt( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char* names[4] = { "R", "G", "B", "A" };
	Int colors[4];
	for( Int i = 0; i < 4; i++ )
	{
		const char* token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (token == NULL)
		{
			if (i < 3)
				throw INIException(3, "can't omit value for color %s", names[i]);
			else
			{
				// it's ok for A to be omitted.
				colors[i] = 255;
			}
		}
		else
		{
			// if present, the token must match.
			if (stricmp(token, names[i]) != 0)
				throw INIException(3, "expected '%s'", names[i]);
			colors[i] = scanInt(ini->getNextToken(ini->getSepsColon()));
		}
		if( colors[ i ] < 0 || colors[ i ] > 255 )
			throw INIException(3, "color value %s=%i out of range (0..255)", names[i], colors[i]);
	}

	//
	// assign the color components to the "RGBColorInt" pointer at 'store', keep
	// the numbers as between 0 and 255
	//
	RGBAColorInt *theColor = (RGBAColorInt *)store;
	theColor->red		= colors[ 0 ];
	theColor->green = colors[ 1 ];
	theColor->blue	= colors[ 2 ];
	theColor->alpha = colors[ 3 ];

}

//-------------------------------------------------------------------------------------------------
void INI::parseColorInt( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char* names[4] = { "R", "G", "B", "A" };
	Int colors[4];
	for( Int i = 0; i < 4; i++ )
	{
		const char* token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (token == NULL)
		{
			if (i < 3)
				throw INIException(3, "can't omit value for color %s", names[i]);
			else
			{
				// it's ok for A to be omitted.
				colors[i] = 255;
			}
		}
		else
		{
			// if present, the token must match.
			if (stricmp(token, names[i]) != 0)
				throw INIException(3, "expected '%s'", names[i]);
			colors[i] = scanInt(ini->getNextToken(ini->getSepsColon()));
		}
		if( colors[ i ] < 0 || colors[ i ] > 255 )
			throw INIException(3, "color value %s=%i out of range (0..255)", names[i], colors[i]);
	}

	//
	// assign the color components to the "Color" pointer at 'store', keep
	// the numbers as between 0 and 255
	//
	Color *theColor = (Color *)store;
	*theColor = GameMakeColor(colors[0], colors[1], colors[2], colors[3]);

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/INI_getNextQuotedAsciiString_Thunk.cpp
// ?getNextQuotedAsciiString@INI@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString INI::getNextQuotedAsciiString()
{
	AsciiString result;
	char buff[INI_MAX_CHARS_PER_LINE];

	const char *token = getNextTokenOrNull();	// if null, just leave an empty string
	if (token != NULL)
	{
		if (token[0] != '\"') 
		{	
			// if token is simply "
			result.set( token );	// Start following the "
		}
		else
		{	int strLen=0;
			Bool done=FALSE;
			if ((strLen=strlen(token)) > 1)
			{
				strcpy(buff, &token[1]);	//skip the starting quote
				//Check for end of quoted string.  Checking here fixes cases where quoted string on same line with other data.
				if (buff[strLen-2]=='"')	//skip ending quote if present
				{	buff[strLen-2]='\0';
					done=TRUE;
				}
			}

			if (!done)
			{
				token = getNextToken(getSepsQuote());
				
				if (strlen(token) > 1 && token[1] != '\t')
				{
					strcat(buff, " ");
					strcat(buff, token);
				}
				else
				{	Int buflen=strlen(buff);
					if (buff[buflen-1]=='\"')
						buff[buflen-1]='\0';
				}
			}
			result.set(buff);
		}
	}
	return result;
}

//-------------------------------------------------------------------------------------------------
void INI::initFromINI( void *what, const FieldParse* parseTable )
{
	MultiIniFieldParse p;
	p.add(parseTable);
	initFromINIMulti(what, p);
}

//-------------------------------------------------------------------------------------------------
static INIFieldParseProc findFieldParse(const FieldParse* parseTable, const char* token, int& offset, const void*& userData)
{
	for (const FieldParse* parse = parseTable; parse->token; ++parse)
	{
		if (strcmp( parse->token, token ) == 0)
		{
			offset = parse->offset;
			userData = parse->userData;
			return parse->parse;
		}
	}

	if (!parse->token && parse->parse) 
	{
		offset = parse->offset;
		userData = token;
		return parse->parse;
	}
	else
	{
		return NULL;
	}
}

//-------------------------------------------------------------------------------------------------
void INI::initFromINIMultiProc( void *what, BuildMultiIniFieldProc proc )
{
	MultiIniFieldParse p;
	(*proc)(p);
	initFromINIMulti(what, p);
}

//-------------------------------------------------------------------------------------------------
void INI::parseBitString8( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	UnsignedInt tmp;
	INI::parseBitString32(ini, NULL, &tmp, userData);
	if (tmp & 0xffffff00)
	{
		DEBUG_CRASH(("Bad bitstring list INI::parseBitString8"));
	// Retail throws a plain int 1 here, not ZH's ERROR_BUG. Both are proven, not
	// assumed: the ThrowInfo this site pushes (0x012454C0) has one catchable type
	// whose TypeDescriptor spells ".H" (int), and every one of the 19 sites that
	// use it image-wide throws the value 1; meanwhile ERROR_BUG really is
	// 0xdead0001 in BFME -- INI::parseScience and INI::parseThingTemplate are
	// matched from this file carrying that immediate. So this is a distinct BFME
	// code; its name in BFME's source is not recoverable from the binary.
	throw 1;
	}
	*(Byte*)store = (Byte)tmp;
}

//-------------------------------------------------------------------------------------------------
/*static*/ Int INI::scanIndexList(const char* token, ConstCharPtrArray nameList)
{
	if( nameList == NULL || nameList[ 0 ] == NULL )
		throw INIException(2, "INTERNAL ERROR! scanIndexList: No name list provided!");

	// search for matching name
	Int count = 0;
	for(ConstCharPtrArray name = nameList; *name; name++, count++ )
	{
		if( stricmp( *name, token ) == 0 )
		{
			return count;
		}
	}

	throw INIException(3, "Token '%s' is not a valid member of the index list", token);
}

//-------------------------------------------------------------------------------------------------
// BFME reports both failures as INIException with a formatted message rather
// than ZH's bare error codes; the two message strings below are transcribed
// from retail (0x011303E0 and 0x01130418), and the leading count is the
// argument count the varargs ctor takes.
/*static*/ Int INI::scanLookupList(const char* token, ConstLookupListRecArray lookupList)
{
	if( lookupList == NULL || lookupList[ 0 ].name == NULL )
		throw INIException(2, "INTERNAL ERROR! scanLookupList: No name list provided!");

	// search for matching name
	for( const LookupListRec* lookup = &lookupList[0]; lookup->name; lookup++ )
	{
		if( stricmp( lookup->name, token ) == 0 )
			return lookup->value;
	}

	throw INIException(3, "Token '%s' is not a valid member of the lookup list", token);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void INI::parseAsciiStringVector( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	// Empty the vector, then reuse the append parser rather than re-reading the
	// tokens here: retail calls vector<AsciiString>::erase(begin, end) and then
	// tail-calls parseAsciiStringVectorAppend with the same four arguments.
	std::vector<AsciiString>* asv = (std::vector<AsciiString>*)store;
	asv->erase(asv->begin(), asv->end());
	INI::parseAsciiStringVectorAppend(ini, NULL, store, NULL);
}

//-------------------------------------------------------------------------------------------------
// MultiIniFieldParse::add is inline in this TU's Common/INI.h; force the
// out-of-line COMDAT retail keeps at 0x00850920.
#pragma auto_inline(off)
void bfme_force_multi_ini_field_parse_add_emission(MultiIniFieldParse &p, const FieldParse *f, UnsignedInt e)
{
	p.add(f, e);
}
#pragma auto_inline(on)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/System/INIDefaultConstructorThunk.cpp
// ??0INI@@QAE@XZ present-unmatched
INI::INI( void )
{

	m_file							= NULL;
  m_readBufferNext=m_readBufferUsed=0;
	m_filename					= "None";
	m_loadType					= INI_LOAD_INVALID;
	m_lineNum						= 0;
	m_seps							= " \n\r\t=";			///< make sure you update m_sepsPercent/m_sepsColon as well
	m_sepsPercent				= " \n\r\t=%%";
	m_sepsColon					= " \n\r\t=:";
	m_sepsQuote					= "\"\n=";				///< stop at " = EOL
	m_blockEndToken			= "END";
	m_endOfFile					= FALSE;
	m_buffer[0]					= 0;
#if defined(_DEBUG) || defined(_INTERNAL)
	m_curBlockStart[0]	= 0;
#endif

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/INIDestructorThunk.cpp
// ??1INI@@QAE@XZ present-unmatched
INI::~INI( void )
{

}

//-------------------------------------------------------------------------------------------------
// Was a __declspec(naked) byte dump in ini.cpp. Retail inlines getNextToken here
// (the body carries m_seps at +0x414 and getNextToken's own "Expected additional
// data after '%s'" throw) but calls scanInt out of line at 0x00852620, which is
// exactly what this TU's header gives.
void INI::parseInt( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	*(Int *)store = scanInt(ini->getNextToken());
}

//-------------------------------------------------------------------------------------------------
// Every integer INI field lands here. BFME first runs the token through the
// macro table (see INI::preprocessMacro) and reports the SUBSTITUTED text in the
// error, not the original token.
#pragma auto_inline(off)
Int bfme_force_ini_scan_int_emission(const char *token) { return INI::scanInt(token); }
#pragma auto_inline(on)

//-------------------------------------------------------------------------------------------------
/*static*/ Real INI::scanReal(const char* token)
{
	Real value;
	const char *text = preprocessMacro(token);
	if (sscanf(text, "%f", &value) != 1)
		throw INIException(3, "Expected floating point value or predefined macro, but found '%s'", text);
	return value;
}

//-------------------------------------------------------------------------------------------------
/*static*/ UnsignedInt INI::scanUnsignedInt(const char* token)
{
	UnsignedInt value;
	const char *text = preprocessMacro(token);
	if (sscanf(text, "%u", &value) != 1)
		throw INIException(3, "Expected unsigned integer value or predefined macro, but found '%s'", text);
	return value;
}

//-------------------------------------------------------------------------------------------------
// Note the error reports the ORIGINAL token, not the macro-substituted text --
// retail pushes the incoming argument here where scanInt/scanReal push the
// substituted string.
/*static*/ Bool INI::scanBool(const char* token)
{
	const char *text = preprocessMacro(token);
	if (stricmp(text, "yes") == 0)
		return TRUE;
	if (stricmp(text, "no") == 0)
		return FALSE;
	throw INIException(3, "invalid boolean token %s -- expected Yes or No", token);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void INI::parseAsciiStringVectorAppend( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	std::vector<AsciiString>* asv = (std::vector<AsciiString>*)store;
	// nope, don't clear. duh.
	// asv->clear();
	for (const char *token = ini->getNextTokenOrNull(); token != NULL; token = ini->getNextTokenOrNull())
	{
		asv->push_back(token);
	}
}

//-------------------------------------------------------------------------------------------------
// ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z present-unmatched
void INI::initFromINIMulti( void *what, const MultiIniFieldParse& parseTableList )
{
	Bool done = FALSE;

	if( what == NULL )
	{
		DEBUG_ASSERTCRASH( 0, ("INI::initFromINI - Invalid parameters supplied!\n") );
		throw INI_INVALID_PARAMS;
	}

	// read each of the data fields
	while( !done )
	{

		// read next line
		readLine();

		// check for end token
		const char* field = strtok( m_buffer, INI::getSeps() );
		if( field )
		{

			if( stricmp( field, m_blockEndToken ) == 0 )
			{
				done = TRUE;
			}
			else
			{
				Bool found = false;
				for (int ptIdx = 0; ptIdx < parseTableList.getCount(); ++ptIdx)
				{
					int offset = 0;
					void* userData = 0;
					INIFieldParseProc parse = findFieldParse(parseTableList.getNthFieldParse(ptIdx), field, offset, userData);
					if (parse)
					{
						// parse this block and check for parse errors
						try {

						(*parse)( this, what, (char *)what + offset + parseTableList.getNthExtraOffset(ptIdx), userData );

						} catch (...) {
							DEBUG_CRASH( ("[LINE: %d - FILE: '%s'] Error reading field '%s' of block '%s'\n",
																 INI::getLineNum(), INI::getFilename().str(), field, m_curBlockStart) );


							char buff[1024];
							sprintf(buff, "[LINE: %d - FILE: '%s'] Error reading field '%s'\n", INI::getLineNum(), INI::getFilename().str(), field);
							throw INIException(buff);
						}
						
						found = true;
						break;
						
					}
				}

				if (!found)
				{
					DEBUG_ASSERTCRASH( 0, ("[LINE: %d - FILE: '%s'] Unknown field '%s' in block '%s'\n",
														 INI::getLineNum(), INI::getFilename().str(), field, m_curBlockStart) );
					throw INI_UNKNOWN_TOKEN;
				}

			}  // end else

		}  // end if

		// sanity check for reaching end of file with no closing end token
		if( done == FALSE && INI::isEOF() == TRUE )
		{

			done = TRUE;
			DEBUG_ASSERTCRASH( 0, ("Error parsing block '%s', in INI file '%s'.  Missing '%s' token\n",
												 m_curBlockStart, getFilename().str(), m_blockEndToken) );
			throw INI_MISSING_END_TOKEN;

		}  // end if

	}  // end while

}
