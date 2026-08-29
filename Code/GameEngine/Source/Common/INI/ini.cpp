// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Ireference/shims/ini /Ireference/shims/xfer /Ireference/shims/ini_parser /Ireference/shims/gameaudio /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?isEndOfBlock@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?isValidINIFilename@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?load@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAccelerationReal@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAndTranslateLabel@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAngularVelocityReal@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseArmorTemplate@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAsciiString@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAudioEventRTS@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseCoord2D@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseCoord3D@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseDamageFX@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseDamageTypeFlags@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseDeathTypeFlags@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseDurationReal@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseDurationUnsignedInt@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseDurationUnsignedShort@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseFXList@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseGameClientRandomVariable@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseICoord2D@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseMappedImage@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseParticleSystemTemplate@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseQuotedAsciiString@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseSpecialPowerTemplate@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseThingTemplate@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseUpgradeTemplate@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseVelocityReal@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseVeterancyLevelFlags@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseWeaponTemplate@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?readLine@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?unPrepFile@INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: INI.cpp //////////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   INI Reader
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#define DEFINE_DEATH_NAMES

#include "Common/INI.h"
#include "Common/INIException.h"

#include "Common/DamageFX.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameAudio.h"
#include "Common/Science.h"
#include "Common/SpecialPower.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/Xfer.h"
#include "Common/XferCRC.h"

#include "GameClient/Anim2D.h"
#include "GameClient/Color.h"
#include "GameClient/FXList.h"
#include "GameClient/GameText.h"
#include "GameClient/Image.h"
#include "GameClient/ParticleSys.h"
#include "GameLogic/Armor.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/FPUControl.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"

class BFMEThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

static Xfer *s_xfer = NULL;

//-------------------------------------------------------------------------------------------------
/** This is the table of data types we can have in INI files.  To add a new data type
	* block make a new entry in this table and add an appropriate parsing function */
//-------------------------------------------------------------------------------------------------
extern void parseReallyLowMHz( INI* ini);		// yeah, so sue me (srj)
// BFME turns Zero Hour's flat lookup table into a self-registering singly-linked
// list: each node's constructor runs at static-init time and pushes it onto a
// global head, and findBlockParse walks that list instead of indexing an array.
// The nodes are 12 bytes and contiguous in .data (0x012A7460, 0x012A746C, ...),
// so they are still consecutive file-scope objects.
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse );
};

// Head of the registration list -- 0x0130CE50. External linkage, not static:
// with internal linkage MSVC hoists the load of it above findBlockParse's
// prologue (the compiler can see every writer), and retail loads it after all
// four pushes. That is also what the list is for -- registrations outside this
// TU have to reach the same head.
BlockParse *theBlockParseList = NULL;

// ??0BlockParse@@QAE@PBDP6AXPAVINI@@@Z@Z
BlockParse::BlockParse( const char *token, INIBlockParse parse ) :
	next(theBlockParseList), token(token), parse(parse)
{
	theBlockParseList = this;
}

// Declared one at a time rather than as an array with an initializer list: MSVC
// 7.1 rejects that for a type with a user-declared constructor ("non-aggregates
// cannot be initialized with initializer list"), so retail cannot have written
// it that way either, and consecutive file-scope statics lay out the same.
#define REGISTER_BLOCK(tag, token, fn) static BlockParse theBlockParse_##tag( token, fn )
REGISTER_BLOCK( AIData, "AIData", INI::parseAIDataDefinition );
REGISTER_BLOCK( Animation, "Animation", INI::parseAnim2DDefinition );
REGISTER_BLOCK( Armor, "Armor", INI::parseArmorDefinition );
REGISTER_BLOCK( AudioEvent, "AudioEvent", INI::parseAudioEventDefinition );
REGISTER_BLOCK( AudioSettings, "AudioSettings", INI::parseAudioSettingsDefinition );
REGISTER_BLOCK( Bridge, "Bridge", INI::parseTerrainBridgeDefinition );
REGISTER_BLOCK( Campaign, "Campaign", INI::parseCampaignDefinition );
REGISTER_BLOCK( ChallengeGenerals, "ChallengeGenerals", INI::parseChallengeModeDefinition );
REGISTER_BLOCK( CommandButton, "CommandButton", INI::parseCommandButtonDefinition );
REGISTER_BLOCK( CommandMap, "CommandMap", INI::parseMetaMapDefinition );
REGISTER_BLOCK( CommandSet, "CommandSet", INI::parseCommandSetDefinition );
REGISTER_BLOCK( ControlBarScheme, "ControlBarScheme", INI::parseControlBarSchemeDefinition );
REGISTER_BLOCK( ControlBarResizer, "ControlBarResizer", INI::parseControlBarResizerDefinition );
REGISTER_BLOCK( CrateData, "CrateData", INI::parseCrateTemplateDefinition );
REGISTER_BLOCK( Credits, "Credits", INI::parseCredits );
REGISTER_BLOCK( WindowTransition, "WindowTransition", INI::parseWindowTransitions );
REGISTER_BLOCK( DamageFX, "DamageFX", INI::parseDamageFXDefinition );
REGISTER_BLOCK( DialogEvent, "DialogEvent", INI::parseDialogDefinition );
REGISTER_BLOCK( DrawGroupInfo, "DrawGroupInfo", INI::parseDrawGroupNumberDefinition );
REGISTER_BLOCK( EvaEvent, "EvaEvent", INI::parseEvaEvent );
REGISTER_BLOCK( FXList, "FXList", INI::parseFXListDefinition );
REGISTER_BLOCK( GameData, "GameData", INI::parseGameDataDefinition );
REGISTER_BLOCK( InGameUI, "InGameUI", INI::parseInGameUIDefinition );
REGISTER_BLOCK( Locomotor, "Locomotor", INI::parseLocomotorTemplateDefinition );
REGISTER_BLOCK( Language, "Language", INI::parseLanguageDefinition );
REGISTER_BLOCK( MapCache, "MapCache", INI::parseMapCacheDefinition );
REGISTER_BLOCK( MapData, "MapData", INI::parseMapDataDefinition );
REGISTER_BLOCK( MappedImage, "MappedImage", INI::parseMappedImageDefinition );
REGISTER_BLOCK( MiscAudio, "MiscAudio", INI::parseMiscAudio );
REGISTER_BLOCK( MiscEvaData, "MiscEvaData", INI::parseMiscEvaData );
REGISTER_BLOCK( Mouse, "Mouse", INI::parseMouseDefinition );
REGISTER_BLOCK( MouseCursor, "MouseCursor", INI::parseMouseCursorDefinition );
REGISTER_BLOCK( MultiplayerColor, "MultiplayerColor", INI::parseMultiplayerColorDefinition );
REGISTER_BLOCK( MultiplayerStartingMoneyChoice, "MultiplayerStartingMoneyChoice", INI::parseMultiplayerStartingMoneyChoiceDefinition );
REGISTER_BLOCK( OnlineChatColors, "OnlineChatColors", INI::parseOnlineChatColorDefinition );
REGISTER_BLOCK( MultiplayerSettings, "MultiplayerSettings", INI::parseMultiplayerSettingsDefinition );
REGISTER_BLOCK( MusicTrack, "MusicTrack", INI::parseMusicTrackDefinition );
REGISTER_BLOCK( Object, "Object", INI::parseObjectDefinition );
REGISTER_BLOCK( ObjectCreationList, "ObjectCreationList", INI::parseObjectCreationListDefinition );
REGISTER_BLOCK( ObjectReskin, "ObjectReskin", INI::parseObjectReskinDefinition );
REGISTER_BLOCK( ParticleSystem, "ParticleSystem", INI::parseParticleSystemDefinition );
REGISTER_BLOCK( PlayerTemplate, "PlayerTemplate", INI::parsePlayerTemplateDefinition );
REGISTER_BLOCK( Road, "Road", INI::parseTerrainRoadDefinition );
REGISTER_BLOCK( Science, "Science", INI::parseScienceDefinition );
REGISTER_BLOCK( Rank, "Rank", INI::parseRankDefinition );
REGISTER_BLOCK( SpecialPower, "SpecialPower", INI::parseSpecialPowerDefinition );
REGISTER_BLOCK( ShellMenuScheme, "ShellMenuScheme", INI::parseShellMenuSchemeDefinition );
REGISTER_BLOCK( Terrain, "Terrain", INI::parseTerrainDefinition );
REGISTER_BLOCK( Upgrade, "Upgrade", INI::parseUpgradeDefinition );
REGISTER_BLOCK( Video, "Video", INI::parseVideoDefinition );
REGISTER_BLOCK( WaterSet, "WaterSet", INI::parseWaterSettingDefinition );
REGISTER_BLOCK( WaterTransparency, "WaterTransparency", INI::parseWaterTransparencyDefinition );
REGISTER_BLOCK( Weather, "Weather", INI::parseWeatherDefinition );
REGISTER_BLOCK( Weapon, "Weapon", INI::parseWeaponTemplateDefinition );
REGISTER_BLOCK( WebpageURL, "WebpageURL", INI::parseWebpageURLDefinition );
REGISTER_BLOCK( HeaderTemplate, "HeaderTemplate", INI::parseHeaderTemplateDefinition );
REGISTER_BLOCK( StaticGameLOD, "StaticGameLOD", INI::parseStaticGameLODDefinition );
REGISTER_BLOCK( DynamicGameLOD, "DynamicGameLOD", INI::parseDynamicGameLODDefinition );
REGISTER_BLOCK( LODPreset, "LODPreset", INI::parseLODPreset );
REGISTER_BLOCK( BenchProfile, "BenchProfile", INI::parseBenchProfile );
REGISTER_BLOCK( ReallyLowMHz, "ReallyLowMHz", parseReallyLowMHz );
REGISTER_BLOCK( ScriptAction, "ScriptAction", ScriptEngine::parseScriptAction );
REGISTER_BLOCK( ScriptCondition, "ScriptCondition", ScriptEngine::parseScriptCondition );


///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
Bool INI::isValidINIFilename( const char *filename )
{
	if( filename == NULL )
		return FALSE;

	Int len = strlen( filename );
	if( len < 3 )
		return FALSE;

	if( filename[ len - 1 ] != 'I' && filename[ len - 1 ] != 'i' )
		return FALSE;

	if( filename[ len - 2 ] != 'N' && filename[ len - 2 ] != 'n' )
		return FALSE;

	if( filename[ len - 3 ] != 'I' && filename[ len - 3 ] != 'i' )
		return FALSE;

	return TRUE;

} 

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// INI::INI lives in ini_parsers.cpp (retail's other INI TU)
  // end INI

// INI::~INI lives in ini_parsers.cpp (retail's other INI TU)
  // end ~INI

//-------------------------------------------------------------------------------------------------
/** Load all INI files in the specified directory (and subdirectories if indicated).
	* If we are to load subdirectories, we will load them *after* we load all the
	* files in the current directory */
//-------------------------------------------------------------------------------------------------
// ?loadDirectory@INI@@QAEXVAsciiString@@_NW4INILoadType@@PAVXfer@@@Z
// Body in Code/masm_dumps/loadDirectory_INI_QAEXVAsciiString_NW4INILoadType_PAVXfer_Z_853F10.asm (exact 700B retail @ 0x00853F10).
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/INI/INIPrepFileThunk.cpp
// ?prepFile@INI@@IAEXVAsciiString@@W4INILoadType@@@Z present-unmatched
void INI::prepFile( AsciiString filename, INILoadType loadType )
{
	// if we have a file open already -- we can't do another one
	if( m_file != NULL )
	{

		DEBUG_CRASH(( "INI::load, cannot open file '%s', file already open\n", filename.str() ));
		throw INI_FILE_ALREADY_OPEN;

	}  // end if

	// open the file
	m_file = TheFileSystem->openFile(filename.str(), File::READ);
	if( m_file == NULL )
	{

		DEBUG_CRASH(( "INI::load, cannot open file '%s'\n", filename.str() ));
		throw INI_CANT_OPEN_FILE;

	}  // end if

	m_file = m_file->convertToRAMFile();

	// save our filename
	m_filename = filename;

	// save our load time
	m_loadType = loadType;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?unPrepFile@INI@@IAEXXZ
// BFME does not close a file here, because by this point there is not one open:
// load reads the whole thing into m_lines up front (see readLine), so tearing
// down means handing that array's storage back rather than closing a handle.
// Zero Hour's m_file->close() / m_file = NULL and its m_readBuffer bookkeeping
// are both absent from the 50 bytes at 0x00850E30.
inline void INI::unPrepFile()
{
	m_lines.clear();
	m_filename = "None";
	m_loadType = INI_LOAD_INVALID;
	m_lineNum = 0;
	m_endOfFile = FALSE;
	s_xfer = NULL;
}

//-------------------------------------------------------------------------------------------------
// ?findBlockParse@@YAP6AXPAVINI@@@ZPBD@Z
// Walks the registration list rather than Zero Hour's array, so the terminator
// is a null next pointer instead of a null token.
static INIBlockParse findBlockParse(const char* token)
{
	for (const BlockParse* parse = theBlockParseList; parse; parse = parse->next)
	{
		if (strcmp( parse->token, token ) == 0)
		{
			return parse->parse;
		}
	}
	return NULL;
}

// findFieldParse lives in ini_parsers.cpp (used by initFromINIMulti)


//-------------------------------------------------------------------------------------------------
/** Load and parse an INI file */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// 0x00851350, 362 bytes. BFME factors this out of load; Zero Hour writes it
// inline there. The name is ours -- there is nothing to take it from, since the
// function does not exist upstream.
//
// The error handling is BFME's own and is worth reading if you write INI: Zero
// Hour sprintfs into a 1KB stack buffer and throws a message-only exception,
// while BFME throws the variadic INIException at three distinct sites, each
// with its own text. Those texts are the ones a mod actually sees:
//
//   unknown keyword   "Unknown block '%s'.\n\nError parsing INI block '%s' in file '%s'."
//   parser threw      "%s\n\nError parsing INI block '%s' in file '%s'."
//   anything else     "Unknown error parsing INI block '%s' in file '%s'."
//
// The absence of that 1KB buffer is what the byte count turned on -- retail
// reserves 0x2c bytes of locals where the Zero Hour shape reserves 0x418.
//
// It also keeps findBlockParse alive: that function is file-static, so with the
// dispatch moved out of load and nothing else calling it, the compiler drops it
// and its matched row loses its definition.
void INI::parseLine( AsciiString filename )
{
	// the first word is the type of data we're processing
	const char *token = strtok( m_buffer, m_seps );
	if( token )
	{
		INIBlockParse parse = findBlockParse(token);
		if (parse)
		{
			strcpy(m_curBlockStart, m_buffer);
			try
			{
				(*parse)( this );
			}
			catch( INIException& e )
			{
				// The block parser already said what went wrong; this only adds
				// where. Note it reads m_filename rather than the filename
				// argument -- retail loads this+4 at all three throw sites, even
				// though it takes the name by value and destroys it on the way
				// out.
				throw INIException( e.m_argCount,
					"%s\n\nError parsing INI block '%s' in file '%s'.",
					e.mFailureMessage, token, m_filename.str() );
			}
			catch (...)
			{
				throw INIException( 8,
					"Unknown error parsing INI block '%s' in file '%s'.",
					token, m_filename.str() );
			}
			strcpy(m_curBlockStart, "NO_BLOCK");
		}
		else
		{
			throw INIException( 5,
				"Unknown block '%s'.\n\nError parsing INI block '%s' in file '%s'.",
				token, token, m_filename.str() );
		}
	}
}

// ?load@INI@@QAEXVAsciiString@@W4INILoadType@@PAVXfer@@@Z
// BFME's load is 0x00853A20, not the 0x00853610 the ledger used to point at --
// that one is prepFile. The shape is also different from Zero Hour's: the
// per-line work (strtok, findBlockParse, invoke) is factored out into the
// 362-byte function at 0x00851350 rather than written inline here, and the
// filename is passed down to it for the error message.
//
// Two things about this one resisted for a while, and both turned out to be the
// same fact rather than two MSVC register-allocation coin flips:
//
// Retail reserves eight more bytes of locals than a straight port does, and it
// materialises zero into ebx to serve the EH state store and the m_endOfFile
// compare where a straight port uses immediates and a byte test. The eight
// bytes are the INIException that the second catch below builds. Once that
// catch exists, the tail becomes cheap enough for MSVC to inline unPrepFile
// into it -- and the inlined tail stores zero five more times, which is what
// makes keeping zero in a register worth a register.
//
// So unPrepFile is marked inline. It still gets its own out-of-line body at
// 0x00850E30, because the catch(...) funclet below calls it rather than
// inlining it, which is exactly the pair retail has.
void INI::load( AsciiString filename, INILoadType loadType, Xfer *pXfer )
{
	setFPMode(); // so we have consistent Real values for GameLogic -MDC

	s_xfer = pXfer;
	prepFile(filename, loadType);

	try
	{
		while( m_endOfFile == FALSE )
		{
			readLine();
			parseLine( filename );
		}
	}
	catch( INIException& e )
	{
		// Rebuilt rather than rethrown, and notably without unPrepFile: parseLine
		// has already wrapped whatever the block parser threw into an INIException
		// carrying the file and line, so this hop only has to keep it alive across
		// the frame.
		throw INIException( e.m_argCount, e.mFailureMessage );
	}
	catch (...)
	{
		unPrepFile();

		// propagate the exception.
		throw;
	}

	unPrepFile();

}  // end load

//-------------------------------------------------------------------------------------------------
/** Read a line from the already open file.  Any comments will be remved and
	* therefore ignored from any given line */
//-------------------------------------------------------------------------------------------------
// ?readLine@INI@@IAEXXZ
// BFME does not stream the file. INI::load reads it in and splits it into
// m_lines, so this just copies the next entry into m_buffer -- there is no
// per-character loop, no comment stripping and no tab check here, because that
// work happened when the file was split.
//
// Both paths fall through to the xfer: every line the parser sees is hashed,
// including the empty one produced at end of file.
void INI::readLine( void )
{
	if( m_lineNum < (UnsignedInt)(m_lines.m_end - m_lines.m_begin) )
	{
		const char *line = m_lines.getText( m_lineNum++ );
		strncpy( m_buffer, line, INI_MAX_CHARS_PER_LINE - 1 );
		m_buffer[ INI_MAX_CHARS_PER_LINE - 1 ] = 0;
	}
	else
	{
		m_endOfFile = TRUE;
		m_buffer[0] = 0;
	}

	if (s_xfer)
	{
		s_xfer->xferUser( m_buffer, sizeof( char ) * strlen( m_buffer ) );
	}
}

//-------------------------------------------------------------------------------------------------
/** Parse UnsignedByte from buffer and assign at location 'store' */
// INI::parseUnsignedByte lives in ini_parsers.cpp (retail's other INI TU)
 

//-------------------------------------------------------------------------------------------------
/** Parse signed short from buffer and assign at location 'store' */
// INI::parseShort lives in ini_parsers.cpp (retail's other INI TU)
 

//-------------------------------------------------------------------------------------------------
/** Parse unsigned short from buffer and assign at location 'store' */
// INI::parseUnsignedShort lives in ini_parsers.cpp (retail's other INI TU)
 

//-------------------------------------------------------------------------------------------------
/** Parse integer from buffer and assign at location 'store' */
// INI::parseInt lives in ini_parsers.cpp (retail's other INI TU), as C++
 

//-------------------------------------------------------------------------------------------------
/** Parse unsigned integer from buffer and assign at location 'store' */
// INI::parseUnsignedInt lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/** Parse real from buffer and assign at location 'store' */
// INI::parseReal lives in ini_parsers.cpp (retail's other INI TU)
 

//-------------------------------------------------------------------------------------------------
/** Parse real from buffer and assign at location 'store' */
// INI::parsePositiveNonZeroReal lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/** Parse a degree value (0 to 360) and store the radian value of that degree
	* in a Real */
// INI::parseAngleReal lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/** Parse an angular velocity in degrees-per-sec and store the rads-per-frame value of that degree
	* in a Real */
//-------------------------------------------------------------------------------------------------
void INI::parseAngularVelocityReal( INI *ini, void * /*instance*/, 
																			void *store, const void *userData )
{
	const char *token = ini->getNextToken();

	// scan the int and convert to radian and store as a real
	*(Real *)store = ConvertAngularVelocityInDegreesPerSecToRadsPerFrame(scanReal( token ));

}

//-------------------------------------------------------------------------------------------------
/** Parse Bool from buffer and assign at location 'store'.  The buffer token must
	* be in the form of a string "Yes" or "No" (case is ignored) */
// INI::parseBool lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/** Parse Bool from buffer; if true, or in MASK, otherwise and out MASK. The buffer token must
	* be in the form of a string "Yes" or "No" (case is ignored) */
// INI::parseBitInInt32 lives in ini_parsers.cpp (retail's other INI TU)


// INI::scanBool lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/** Parse an *ASCII* string from buffer and assign at location 'store' */
//-------------------------------------------------------------------------------------------------
void INI::parseAsciiString( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	AsciiString* asciiString = (AsciiString *)store;
	*asciiString = ini->getNextAsciiString();
}

//-------------------------------------------------------------------------------------------------
/** Parse an *ASCII* string from buffer and assign at location 'store'. Has better support for quoted strings.
We don't really need this function, but parseString() is broken and we want to leave it broken to
maintain existing code.
 */
//-------------------------------------------------------------------------------------------------
void INI::parseQuotedAsciiString( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	AsciiString* asciiString = (AsciiString *)store;
	*asciiString = ini->getNextQuotedAsciiString();
}

// INI::parseAsciiStringVector lives in ini_parsers.cpp (retail's other INI TU)


// INI::parseAsciiStringVectorAppend lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/* static */void INI::parseScienceVector( INI *ini, void * /*instance*/, void *store, const void *userData )
{
	ScienceVec* asv = (ScienceVec*)store;
	asv->clear();
	for (const char *token = ini->getNextTokenOrNull(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (stricmp(token, "None") == 0)
		{
			asv->clear();
			return;
		}
		asv->push_back(INI::scanScience( token ));
	}
}

// INI::getNextQuotedAsciiString lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/INI_getNextAsciiString_Thunk.cpp
// ?getNextAsciiString@INI@@ present-unmatched
AsciiString INI::getNextAsciiString()
{
	AsciiString result;

	const char *token = getNextTokenOrNull();	// if null, just leave an empty string
	if (token != NULL)
	{
		if (token[0] != '\"') 
		{	
			// if token is simply "
			result.set( token );	// Start following the "
		}
		else
		{
			static char buff[INI_MAX_CHARS_PER_LINE];
			buff[0] = 0;
			if (strlen(token) > 1)
			{
				strcpy(buff, &token[1]);
			} 

			token = getNextTokenOrNull(getSepsQuote());
			if (token) {
				if (strlen(token) > 1 && token[1] != '\t')
				{
					strcat(buff, " ");
				}
				strcat(buff, token);
				result.set(buff);
			} else {
				Int len = strlen(buff);
				if (len && buff[len-1] == '"') { // strip off trailing quote jba. [2/12/2003]
					buff[len-1] = 0;
				}
				result.set(buff);
			}
		}
	}
	return result;
}

//-------------------------------------------------------------------------------------------------
/** Parse a string label, get the *translated* actual text from the label and store
	* into a *UNICODE* string. */
//-------------------------------------------------------------------------------------------------
void INI::parseAndTranslateLabel(INI *ini, void *, void *store, const void *)
{
	struct BFMEUnicodeData
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		WideChar text[1];
	};

	const char *token = ini->getNextToken();
	UnicodeString translated = TheGameText->fetch(token);
	BFMEUnicodeData *data = *(BFMEUnicodeData **)&translated;
	if (translated.isEmpty())
		throw INIException(3, "Label '%s' not found in game text", token);
	const WideChar *text = data->text;
	((StringBase<WideChar> *)store)->set(text, text ? (int)wcslen(text) : 0);
}

//-------------------------------------------------------------------------------------------------
/** Parse a string label assumed as an image as part of the image collection.  Translate
	* to an image pointer for storage */
//-------------------------------------------------------------------------------------------------
void INI::parseMappedImage( INI *ini, void * /*instance*/, void *store, const void *userData )
{
	const char *token = ini->getNextToken();

	if( TheMappedImageCollection )
	{
		typedef const Image* ConstImagePtr;
		*(ConstImagePtr*)store = TheMappedImageCollection->findImageByName( AsciiString( token ) );
	}
	
	//KM: If we are in the worldbuilder, we want to parse commandbuttons for informational purposes,
	//but we don't care about the images -- because we never access them. In RTS/GUIEdit, they always
	//exist -- and in those cases, it will never call this code anyways because it'll throw long before.
	//else
	//	throw INI_UNKNOWN_ERROR;

}  // end parseMappedImage

// ------------------------------------------------------------------------------------------------
/** Parse a string label assumed as a Anim2D template name.  Translate that name to an 
	* actual template pointer for storage */
// ------------------------------------------------------------------------------------------------
/*static*/ void INI::parseAnim2DTemplate( INI *ini, void *instance, void *store, const void *userData )
{
	const char *token = ini->getNextToken();

	if( TheAnim2DCollection )
	{
		Anim2DTemplate **anim2DTemplate = (Anim2DTemplate **)store;
		*anim2DTemplate = TheAnim2DCollection->findTemplate( AsciiString( token ) );
	}  // end if
	else
	{

		DEBUG_CRASH(( "INI::parseAnim2DTemplate - TheAnim2DCollection is NULL\n" ));
		throw INI_UNKNOWN_ERROR;

	}  // end else

}  // end parseAnim2DTemplate

//-------------------------------------------------------------------------------------------------
/** Parse a percent in int or real form such as "23%" or "95.4%" and assign
	* to location 'store' as a number from 0.0 to 1.0 */
// INI::parsePercentToReal lives in ini_parsers.cpp (retail's other INI TU)
  // end parsePercentToReal

//-------------------------------------------------------------------------------------------------
/** 'store' points to an 32 bit unsigned integer.  We will zero that integer, parse each token
	* in the buffer, if the token is in the userData table of strings, we will set the
	* according bit flag for it */
// INI::parseBitString8 lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/** 'store' points to an 32 bit unsigned integer.  We will zero that integer, parse each token
	* in the buffer, if the token is in the userData table of strings, we will set the
	* according bit flag for it */
// INI::parseBitString32 lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/** Parse a color in the form of
	*
	* RGB_COLOR = R:100 G:114 B:245
	* and store in "RGBColor" structure pointed to by 'store' */
// INI::parseRGBColor lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/** Parse a color in the form of
	*
	* RGB_COLOR = R:100 G:114 B:245 [A:233]
	* and store in "RGBAColorInt" structure pointed to by 'store' */
// INI::parseRGBAColorInt lives in ini_parsers.cpp (retail's other INI TU)
  // end parseRGBAColorInt

//-------------------------------------------------------------------------------------------------
/** Parse a color in the form of
	*
	* RGB_COLOR = R:100 G:114 B:245 [A:233]
	* and store in "Color" structure pointed to by 'store' */
// INI::parseColorInt lives in ini_parsers.cpp (retail's other INI TU)
  // end parseColorInt

//-------------------------------------------------------------------------------------------------
/** Parse a 3D coordinate of reals in the form of:
	* FIELD_NAME = X:400 Y:-214.3 Z:8.6 */
//-------------------------------------------------------------------------------------------------
void INI::parseCoord3D( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	Coord3D *theCoord = (Coord3D *)store;

	theCoord->x = scanReal(ini->getNextSubToken("X"));
	theCoord->y = scanReal(ini->getNextSubToken("Y"));
	theCoord->z = scanReal(ini->getNextSubToken("Z"));

}  // end parseCoord3D

//-------------------------------------------------------------------------------------------------
/** Parse a 2D coordinate of reals in the form of:
	* FIELD_NAME = X:400 Y:-214.3 */
//-------------------------------------------------------------------------------------------------
void INI::parseCoord2D( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	Coord2D *theCoord = (Coord2D *)store;

	theCoord->x = scanReal(ini->getNextSubToken("X"));
	theCoord->y = scanReal(ini->getNextSubToken("Y"));

}  // end parseCoord2D

//-------------------------------------------------------------------------------------------------
/** Parse a 2D coordinate of Ints in the form of:
	* FIELD_NAME = X:400 Y:-214 */
//-------------------------------------------------------------------------------------------------
void INI::parseICoord2D( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	ICoord2D *theCoord = (ICoord2D *)store;

	theCoord->x = scanInt(ini->getNextSubToken("X"));
	theCoord->y = scanInt(ini->getNextSubToken("Y"));

}  // end parseICoord2D

//-------------------------------------------------------------------------------------------------
/** Parse an audio event and assign to the 'AudioEventRTS*' at store */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/INIParseDynamicAudioEventRTSThunk.cpp
// ?parseDynamicAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z present-unmatched
void INI::parseDynamicAudioEventRTS( INI *ini, void * /*instance*/, void *store, const void* userData )
{
	const char *token = ini->getNextToken();
	DynamicAudioEventRTS** theSound = (DynamicAudioEventRTS**)store;
	
	// translate the string into a sound
	if (stricmp(token, "NoSound") == 0) 
	{
		if (*theSound)
		{
			(*theSound)->deleteInstance();
			*theSound = NULL;
		}
	}
	else
	{
		if (*theSound == NULL)
			*theSound = newInstance(DynamicAudioEventRTS);
		(*theSound)->m_event.setEventName(AsciiString(token));
	}
	
	if (*theSound)
		TheAudio->getInfoForAudioEvent(&(*theSound)->m_event);
}

//-------------------------------------------------------------------------------------------------
/** Parse an audio event and assign to the 'AudioEventRTS*' at store */
//-------------------------------------------------------------------------------------------------
// 0x000BBB60, 181 bytes -- the most-referenced field parser in the game, bound
// to 45 tokens across 5 INI blocks. Zero Hour's version ends at
// getInfoForAudioEvent; BFME adds the validation tail below, so an event the
// audio manager could not resolve is a hard error instead of silence.
// Matching it needed three things: a REL32 pin for AudioEventRTS::setEventName
// (retail calls thunk 0x25266), AsciiString::isEmpty inlined the way retail
// emits it, and reference/shims/gameaudio for the AudioManager vtable, whose
// slots BFME reordered -- getInfoForAudioEvent is at +0xac here against +0x68
// from the stock header, and isValidAudioEvent at +0x5c against +0x40.
void INI::parseAudioEventRTS( INI *ini, void * /*instance*/, void *store, const void* userData )
{
	const char *token = ini->getNextToken();

	AudioEventRTS *theSound = (AudioEventRTS*)store;
	
	// translate the string into a sound
	if (stricmp(token, "NoSound") != 0) {
		theSound->setEventName(AsciiString(token));
	}

	TheAudio->getInfoForAudioEvent(theSound);

	// BFME addition: a named event that the audio manager could not resolve is a
	// hard error rather than a silent miss. "NoSound" is exempt because it is the
	// sentinel for "deliberately nothing", and an empty name means the field was
	// never set.
	if (!theSound->getEventName().isEmpty() &&
			theSound->getEventName().compareNoCase("NoSound") != 0 &&
			!TheAudio->isValidAudioEvent(theSound))
	{
		throw INIException(3, "Invalid Sound '%s'", theSound->getEventName().str());
	}
}

//-------------------------------------------------------------------------------------------------
/** Parse an ThingTemplate and assign to the 'ThingTemplate *' at store */
//-------------------------------------------------------------------------------------------------
void INI::parseThingTemplate(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	if (!TheThingFactory)
		throw ERROR_BUG;
	if (stricmp(token, "None") == 0)
	{
		*(const ThingTemplate **)store = NULL;
	}
	else
	{
		const ThingTemplate *thing = ((BFMEThingFactory *)TheThingFactory)->findTemplate(AsciiString(token));
		*(const ThingTemplate **)store = thing;
	}
}

//-------------------------------------------------------------------------------------------------
/** Parse an ArmorTemplate and assign to the 'ArmorTemplate *' at store */
//-------------------------------------------------------------------------------------------------
void INI::parseArmorTemplate( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();

	typedef const ArmorTemplate *ConstArmorTemplatePtr;
	ConstArmorTemplatePtr* theArmorTemplate = (ConstArmorTemplatePtr*)store;		

	if (stricmp(token, "None") == 0)
	{
		*theArmorTemplate = NULL;
	}
	else
	{
		const ArmorTemplate *tt = TheArmorStore->findArmorTemplate(token);	// could be null!
		DEBUG_ASSERTCRASH(tt, ("ArmorTemplate %s not found!\n",token));
		// assign it, even if null!
		*theArmorTemplate = tt;
	}

} 

//-------------------------------------------------------------------------------------------------
/** Parse an WeaponTemplate and assign to the 'WeaponTemplate *' at store */
//-------------------------------------------------------------------------------------------------
void INI::parseWeaponTemplate( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();

	typedef const WeaponTemplate *ConstWeaponTemplatePtr;
	ConstWeaponTemplatePtr* theWeaponTemplate = (ConstWeaponTemplatePtr*)store;		

	const WeaponTemplate *tt = TheWeaponStore->findWeaponTemplate(token);	// could be null!
	DEBUG_ASSERTCRASH(tt || stricmp(token, "None") == 0, ("WeaponTemplate %s not found!\n",token));
	// assign it, even if null!
	*theWeaponTemplate = tt;

} 

//-------------------------------------------------------------------------------------------------
/** Parse an FXList and assign to the 'FXList *' at store */
//-------------------------------------------------------------------------------------------------
void INI::parseFXList(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	const FXList *fxl = TheFXListStore->findFXList(token);
	if (fxl == NULL && token != NULL && stricmp(token, "none") != 0)
		throw INIException(3, "iniParseFXList -- FXList %s not found! Either add the FXList or remove the reference to it.", token);
	*(const FXList **)store = fxl;
}

//-------------------------------------------------------------------------------------------------
/** Parse a particle system and assign to 'ParticleSystemTemplate *' at store */
//-------------------------------------------------------------------------------------------------
void INI::parseParticleSystemTemplate(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	const ParticleSystemTemplate *particle = TheParticleSystemManager->findTemplate(AsciiString(token));
	if (particle != NULL && stricmp(token, "None") != 0)
		*(const ParticleSystemTemplate **)store = particle;
	else
		*(const ParticleSystemTemplate **)store = NULL;
}

//-------------------------------------------------------------------------------------------------
/** Parse an DamageFX and assign to the 'DamageFX *' at store */
//-------------------------------------------------------------------------------------------------
void INI::parseDamageFX( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();

	typedef const DamageFX *ConstDamageFXPtr;
	ConstDamageFXPtr* theDamageFX = (ConstDamageFXPtr*)store;		

	if (stricmp(token, "None") == 0)
	{
		*theDamageFX = NULL;
	}
	else
	{
		const DamageFX *fxl = TheDamageFXStore->findDamageFX(token);	// could be null!
		DEBUG_ASSERTCRASH(fxl, ("DamageFX %s not found!\n",token));
		// assign it, even if null!
		*theDamageFX = fxl;
	}

} 

//-------------------------------------------------------------------------------------------------
/** Parse an ObjectCreationList and assign to the 'ObjectCreationList *' at store */
//-------------------------------------------------------------------------------------------------
void INI::parseObjectCreationList( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();

	typedef const ObjectCreationList *ConstObjectCreationListPtr;
	ConstObjectCreationListPtr* theObjectCreationList = (ConstObjectCreationListPtr*)store;		

	const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null!
	DEBUG_ASSERTCRASH(ocl || stricmp(token, "None") == 0, ("ObjectCreationList %s not found!\n",token));
	// assign it, even if null!
	*theObjectCreationList = ocl;

} 

//-------------------------------------------------------------------------------------------------
/** Parse a upgrade template string and store as template pointer */
//-------------------------------------------------------------------------------------------------
void INI::parseUpgradeTemplate(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	if (!TheUpgradeCenter)
		return;
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(AsciiString(token));
	*(const UpgradeTemplate **)store = upgrade;
}

//-------------------------------------------------------------------------------------------------
/** Parse a special power template string and store as template pointer */
//-------------------------------------------------------------------------------------------------
void INI::parseSpecialPowerTemplate( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();

	if (!TheSpecialPowerStore)
	{
		DEBUG_CRASH(("TheSpecialPowerStore not inited yet"));
		throw ERROR_BUG;
	}

	const SpecialPowerTemplate *sPowerT = TheSpecialPowerStore->findSpecialPowerTemplate( AsciiString( token ) );

	// Zero Hour follows the lookup with a DEBUG_CRASH guarded by
	// !sPowerT && stricmp(token, "None"). Retail has no trace of it -- not even
	// the stricmp, which a release build would still have had to call -- so the
	// check is not merely compiled out here, it is absent.

	typedef const SpecialPowerTemplate* ConstSpecialPowerTemplatePtr;
	ConstSpecialPowerTemplatePtr* theSpecialPowerTemplate = (ConstSpecialPowerTemplatePtr *)store;		
	*theSpecialPowerTemplate = sPowerT;
} 

//-------------------------------------------------------------------------------------------------
/** Parse a science string and store as science type */
//-------------------------------------------------------------------------------------------------
void INI::parseScience(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	if (!TheScienceStore)
		throw ERROR_BUG;
	*((ScienceType *)store) = TheScienceStore->friend_lookupScience(token);
}

//-------------------------------------------------------------------------------------------------
/** Parse a single string token, check for that token in the index list
	* of names provided and store the index into that list.
	*
	* NOTE: Is is assumed that we are going to store the index into
	*				a 4 byte integer.  This works well for INT and ENUM definitions */
// INI::parseIndexList lives in ini_parsers.cpp (retail's other INI TU)
 

//-------------------------------------------------------------------------------------------------
/** Parse a single string token, check for that token in the index list
	* of names provided and store the index into that list.
	*
	* NOTE: Is is assumed that we are going to store the index into
	*				a 4 byte integer.  This works well for INT and ENUM definitions */
// INI::parseByteSizedIndexList lives in ini_parsers.cpp (retail's other INI TU)
 

//-------------------------------------------------------------------------------------------------
/** Parse a single string token, check for that token in the index list
	* of names provided and store the associated value into that list.
	*
	* NOTE: Is is assumed that we are going to store the index into
	*				a 4 byte integer.  This works well for INT and ENUM definitions */
// INI::parseLookupList lives in ini_parsers.cpp (retail's other INI TU)


///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	
// MultiIniFieldParse::add lives in ini_parsers.cpp (retail's other INI TU)


// INI::initFromINI lives in ini_parsers.cpp (retail's other INI TU)


// INI::initFromINIMultiProc lives in ini_parsers.cpp (retail's other INI TU)


// INI::initFromINIMulti lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
// ?getNextToken@INI@@QAEPBDPBD@Z
// Not static: retail reads m_seps out of this at +0x414, which is what makes the
// separator set per-INI rather than global.
const char* INI::getNextToken(const char* seps)
{
	if (!seps) seps = m_seps;
	const char *token = ::strtok(NULL, seps);
	if (!token)
		throw INIException( 3, "Expected additional data after '%s'", seps );
	return token;
}

//-------------------------------------------------------------------------------------------------
// ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
const char* INI::getNextTokenOrNull(const char* seps)
{
	if (!seps) seps = m_seps;
	const char *token = ::strtok(NULL, seps);
	return token;
}

//-------------------------------------------------------------------------------------------------
/*static*/ ScienceType INI::scanScience(const char* token)
{
	return TheScienceStore->friend_lookupScience( token );
}

// INI::scanInt lives in ini_parsers.cpp (retail's other INI TU)


// INI::scanUnsignedInt lives in ini_parsers.cpp (retail's other INI TU)


// INI::scanReal lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/*static*/ Real INI::scanPercentToReal(const char* token)
{
	return scanReal(token) * 0.01f;
}

// INI::scanIndexList lives in ini_parsers.cpp (retail's other INI TU)

// INI::scanLookupList lives in ini_parsers.cpp (retail's other INI TU)


// INI::getNextSubToken lives in ini_parsers.cpp (retail's other INI TU)


//-------------------------------------------------------------------------------------------------
/**
 * Parse a "random variable".
 * The format is "FIELD = low high [distribution]".
 */
void INI::parseGameClientRandomVariable( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	GameClientRandomVariable *var = static_cast<GameClientRandomVariable *>(store);

	const char* token;

	token = ini->getNextToken();
	Real low = INI::scanReal(token);

	token = ini->getNextToken();
	Real high = INI::scanReal(token);

	// if omitted, assume uniform
	GameClientRandomVariable::DistributionType type = GameClientRandomVariable::UNIFORM;
	token = ini->getNextTokenOrNull();
	if (token)
		type = (GameClientRandomVariable::DistributionType)INI::scanIndexList(token, GameClientRandomVariable::DistributionTypeNames);

	// set the range of the random variable
	var->setRange( low, high, type );
}

//-------------------------------------------------------------------------------------------------
// parse a duration in msec and convert to duration in frames
void INI::parseDurationReal( INI *ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	Real val = scanReal(ini->getNextToken());
	*(Real *)store = ConvertDurationFromMsecsToFrames(val);
}

//-------------------------------------------------------------------------------------------------
// parse a duration in msec and convert to duration in integral number of frames, (unsignedint) rounding UP
void INI::parseDurationUnsignedInt( INI *ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	UnsignedInt val = scanUnsignedInt(ini->getNextToken());
	*(UnsignedInt *)store = (UnsignedInt)ceilf(ConvertDurationFromMsecsToFrames((Real)val));
}

// ------------------------------------------------------------------------------------------------
// parse a duration in msec and convert to duration in integral number of frames, (unsignedshort) rounding UP
void INI::parseDurationUnsignedShort( INI *ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	UnsignedInt val = scanUnsignedInt(ini->getNextToken());
	*(UnsignedShort *)store = (UnsignedShort)ceilf(ConvertDurationFromMsecsToFrames((Real)val));
}

//-------------------------------------------------------------------------------------------------
// parse acceleration in (dist/sec) and convert to (dist/frame)
void INI::parseVelocityReal( INI *ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();
	Real val = scanReal(token);
	*(Real *)store = ConvertVelocityInSecsToFrames(val);
}

//-------------------------------------------------------------------------------------------------
// parse acceleration in (dist/sec^2) and convert to (dist/frame^2)
void INI::parseAccelerationReal( INI *ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	const char *token = ini->getNextToken();
	Real val = scanReal(token);
	*(Real *)store = ConvertAccelerationInSecsToFrames(val);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void INI::parseVeterancyLevelFlags(INI *ini, void *, void *store, const void *)
{
	VeterancyLevelFlags flags = VETERANCY_LEVEL_FLAGS_ALL;
	for (const char *token = ini->getNextToken(); token; token = ini->getNextTokenOrNull())
	{
		if (stricmp(token, "ALL") == 0) { flags = VETERANCY_LEVEL_FLAGS_ALL; continue; }
		if (stricmp(token, "NONE") == 0) { flags = VETERANCY_LEVEL_FLAGS_NONE; continue; }
		if (token[0] == '+')
		{
			VeterancyLevel dt = (VeterancyLevel)INI::scanIndexList(token + 1, TheVeterancyNames);
			flags = setVeterancyLevelFlag(flags, dt);
			continue;
		}
		if (token[0] == '-')
		{
			VeterancyLevel dt = (VeterancyLevel)INI::scanIndexList(token + 1, TheVeterancyNames);
			flags = clearVeterancyLevelFlag(flags, dt);
			continue;
		}
		throw INIException(5, "ALL, NONE, + or - expected");
	}
	*(VeterancyLevelFlags *)store = flags;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/INIParseSoundsListThunk.cpp
// ?parseSoundsList@INI@@SAXPAV1@PAX1PBX@Z present-unmatched
void INI::parseSoundsList( INI* ini, void *instance, void *store, const void* /*userData*/ )
{
	std::vector<AsciiString> *vec = (std::vector<AsciiString>*) store;
	vec->clear();

	const char* SEPS = " \t,=";
	const char *c = ini->getNextTokenOrNull(SEPS);
	while ( c )
	{
		vec->push_back( c );
		c = ini->getNextTokenOrNull(SEPS);
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void INI::parseDamageTypeFlags(INI *ini, void *, void *store, const void *)
{
	UnsignedInt flags = 0xFFFFFFFF;
	for (const char *token = ini->getNextToken(); token; token = ini->getNextTokenOrNull())
	{
		if (stricmp(token, "ALL") == 0) { flags = 0xFFFFFFFF; continue; }
		if (stricmp(token, "NONE") == 0) { flags = 0; continue; }
		if (token[0] == '+')
		{
			Int dt = INI::scanIndexList(token + 1, DamageTypeFlags::getBitNames());
			flags |= 1 << (dt - 1);
			continue;
		}
		if (token[0] == '-')
		{
			Int dt = INI::scanIndexList(token + 1, DamageTypeFlags::getBitNames());
			flags &= ~(1 << (dt - 1));
			continue;
		}
		throw INIException(5, "ALL, NONE, + or - expected");
	}
	*(UnsignedInt *)store = flags;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void INI::parseDeathTypeFlags(INI *ini, void *, void *store, const void *)
{
	DeathTypeFlags flags = DEATH_TYPE_FLAGS_ALL;
	for (const char *token = ini->getNextToken(); token; token = ini->getNextTokenOrNull())
	{
		if (stricmp(token, "ALL") == 0) { flags = DEATH_TYPE_FLAGS_ALL; continue; }
		if (stricmp(token, "NONE") == 0) { flags = DEATH_TYPE_FLAGS_NONE; continue; }
		if (token[0] == '+')
		{
			DeathType dt = (DeathType)INI::scanIndexList(token + 1, TheDeathNames);
			flags = setDeathTypeFlag(flags, dt);
			continue;
		}
		if (token[0] == '-')
		{
			DeathType dt = (DeathType)INI::scanIndexList(token + 1, TheDeathNames);
			flags = clearDeathTypeFlag(flags, dt);
			continue;
		}
		throw INIException(5, "ALL, NONE, +, or - expected");
	}
	*(DeathTypeFlags *)store = flags;
}

//-------------------------------------------------------------------------------------------------
// parse the line and return whether the given line is a Block declaration of the form
// [whitespace] blockType [whitespace] blockName [EOL]
// both blockType and blockName are case insensitive
// ?isDeclarationOfType@INI@@SA_NVAsciiString@@0PAD@Z present-unmatched
Bool INI::isDeclarationOfType( AsciiString blockType, AsciiString blockName, char *bufferToCheck )
{
	Bool retVal = true;
	if (!bufferToCheck || blockType.isEmpty() || blockName.isEmpty()) {
		return false;
	}
	// DO NOT RETURN EARLY FROM THIS FUNCTION. (beyond this point)
	// we have to restore the bufferToCheck to its previous state before returning, so 
	// it is important to get through all the checks.
	
	char restoreChar;
	char *tempBuff = bufferToCheck;
	int blockTypeLength = blockType.getLength();
	int blockNameLength = blockName.getLength();

	while (isspace(*tempBuff)) {
		++tempBuff;
	}
	
	if (strlen(tempBuff) > blockTypeLength) {
		restoreChar = tempBuff[blockTypeLength];
		tempBuff[blockTypeLength] = 0;
		
		if (stricmp(blockType.str(), tempBuff) != 0) {
			retVal = false;
		}

		tempBuff[blockTypeLength] = restoreChar;
		tempBuff = tempBuff + blockTypeLength;
	} else {
		retVal = false;
	}

	while (isspace(*tempBuff)) {
		++tempBuff;
	}

	if (strlen(tempBuff) > blockNameLength) {
		restoreChar = tempBuff[blockNameLength];
		tempBuff[blockNameLength] = 0;
		
		if (stricmp(blockName.str(), tempBuff) != 0) {
			retVal = false;
		}

		tempBuff[blockNameLength] = restoreChar;
		tempBuff = tempBuff + blockNameLength;
	} else {
		retVal = false;
	}

	while (strlen(tempBuff)) {
		retVal = retVal && isspace(tempBuff[0]);
		++tempBuff;
	}

	return retVal;
}

//-------------------------------------------------------------------------------------------------
// parse the line and return whether the given line is a Block declaration of the form
// [whitespace] end [EOL]
Bool INI::isEndOfBlock( char *bufferToCheck )
{
	Bool retVal = true;
	if (!bufferToCheck) {
		return false;
	}

	// DO NOT RETURN EARLY FROM THIS FUNCTION (beyond this point)
	// we have to restore the bufferToCheck to its previous state before returning, so 
	// it is important to get through all the checks.
	
	static const char* endString = "End";
	int endStringLength = strlen(endString);
	char restoreChar;
	char *tempBuff = bufferToCheck;
	

	while (isspace(*tempBuff)) {
		++tempBuff;
	}
	
	if (strlen(tempBuff) > endStringLength) {
		restoreChar = tempBuff[endStringLength];
		tempBuff[endStringLength] = 0;
		
		if (stricmp(endString, tempBuff) != 0) {
			retVal = false;
		}

		tempBuff[endStringLength] = restoreChar;
		tempBuff = tempBuff + endStringLength;
	} else {
		retVal = false;
	}

	while (strlen(tempBuff)) {
		retVal = retVal && isspace(tempBuff[0]);
		++tempBuff;
	}

	return retVal;
}
