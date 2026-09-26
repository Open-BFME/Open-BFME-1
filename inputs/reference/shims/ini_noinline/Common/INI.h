// BFME INI layout, WITHOUT the getNextToken/getNextTokenOrNull inlining that
// reference/shims/ini_inline applies. Same class layout, same everything else;
// the only difference is that those two are declarations here, so a TU that
// calls the out-of-line copy at 0x00850970 compiles to a call instead of an
// inlined body. Keep the two in sync if the layout is ever corrected.
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

// FILE: INI.h ////////////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   INI Reader
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string.h>
#include "Common/INIException.h"

#ifndef __INI_H_
#define __INI_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include <stddef.h>	// for offsetof, which we don't use but everyone who includes us does
#include "Common/STLTypedefs.h"
#include "Common/AsciiString.h"
#include "Common/GameCommon.h"

//-------------------------------------------------------------------------------------------------
class INI;
class Xfer;
class File;
enum ScienceType;

//-------------------------------------------------------------------------------------------------
/** These control the behavior of loading the INI data into items */
//-------------------------------------------------------------------------------------------------
enum INILoadType
{	
	INI_LOAD_INVALID,						///< invalid load type
	INI_LOAD_OVERWRITE,					///< create new or load *over* existing data instance
	INI_LOAD_CREATE_OVERRIDES,	///< create new or load into *new* override data instance
	INI_LOAD_MULTIFILE					///< create new or continue loading into existing data instance.
};

//-------------------------------------------------------------------------------------------------
/** INI constant defines */
//-------------------------------------------------------------------------------------------------
enum
{
	INI_MAX_CHARS_PER_LINE = 1028,			///< max characters per line entry in any ini file
};

//-------------------------------------------------------------------------------------------------
/** Status return codes for the INI reader */
//-------------------------------------------------------------------------------------------------
enum
{
	// we map all of these to the same "real" error code, because
	// we generally don't care why it failed; but since the code distinguishes,
	// I didn't want to wipe out that intelligence. if we ever need to distinguish
	// failure modes at runtime, just put in real values for these.
	INI_CANT_SEARCH_DIR		= ERROR_BAD_INI,
	INI_INVALID_DIRECTORY = ERROR_BAD_INI,
	INI_INVALID_PARAMS		= ERROR_BAD_INI,
	INI_INVALID_NAME_LIST = ERROR_BAD_INI,
	INI_INVALID_DATA			= ERROR_BAD_INI,
	INI_MISSING_END_TOKEN = ERROR_BAD_INI,
	INI_UNKNOWN_TOKEN			= ERROR_BAD_INI,
	INI_BUFFER_TOO_SMALL  = ERROR_BAD_INI,
	INI_FILE_NOT_OPEN			= ERROR_BAD_INI,
	INI_FILE_ALREADY_OPEN = ERROR_BAD_INI,
	INI_CANT_OPEN_FILE		= ERROR_BAD_INI,
	INI_UNKNOWN_ERROR			= ERROR_BAD_INI,
	INI_END_OF_FILE				= ERROR_BAD_INI
};

//-------------------------------------------------------------------------------------------------
/** Function typedef for parsing data block fields.
	*
	* buffer - the character buffer of the line from INI that we are reading and parsing
	* instance - instance of what we're loading (for example a thingtemplate instance)
	* store - where to store the data parsed, this is a field in the *instance* 'instance'
	*/
//-------------------------------------------------------------------------------------------------
typedef void (*INIFieldParseProc)( INI *ini, void *instance, void *store, const void* userData );

//-------------------------------------------------------------------------------------------------
typedef const char* ConstCharPtr;
typedef const ConstCharPtr* ConstCharPtrArray;

//-------------------------------------------------------------------------------------------------
struct LookupListRec
{
	const char* name;
	Int value;
};
typedef const LookupListRec *ConstLookupListRecArray;

//-------------------------------------------------------------------------------------------------
/** Parse tables for all fields of each data block are created using these */
//-------------------------------------------------------------------------------------------------
struct FieldParse
{
	const char*					token;						///< token of the field
	INIFieldParseProc		parse;						///< the parse function
	const void*					userData;					///< field-specific data
	Int									offset;						///< offset to data field

	inline void set(const char* t, INIFieldParseProc p, const void* u, Int o)
	{
		token = t;
		parse = p;
		userData = u;
		offset = o;
	}
};

//-------------------------------------------------------------------------------------------------
class MultiIniFieldParse
{
private:
	enum { MAX_MULTI_FIELDS = 16 };

	const FieldParse* m_fieldParse[MAX_MULTI_FIELDS];
	UnsignedInt				m_extraOffset[MAX_MULTI_FIELDS];
	Int								m_count;

public:
	// BFME zeroes BOTH arrays in one loop, where ZH only clears m_extraOffset:
	// retail's INI::initFromINI (0x008520A0) emits a 16-iteration loop storing
	// zero to [esp+eax*4+4] and [esp+eax*4+0x44], not an unrolled run of stores.
	MultiIniFieldParse() : m_count(0)
	{
		for(Int i = 0; i < MAX_MULTI_FIELDS; i++)
		{
			m_extraOffset[i] = 0;
			m_fieldParse[i] = 0;
		}
	}

	// Inline here (retail inlines it into initFromINI) while keeping its
	// out-of-line COMDAT at 0x00850920; ini_parsers.cpp forces that copy.
	void add(const FieldParse* f, UnsignedInt e = 0)
	{
		if (m_count < MAX_MULTI_FIELDS)
		{
			m_fieldParse[m_count] = f;
			m_extraOffset[m_count] = e;
			++m_count;
		}
		else
		{
			// retail throws a plain int 1 here; see INI::parseBitString8
			throw 1;
		}
	}

	inline Int getCount() const { return m_count; }
	inline const FieldParse* getNthFieldParse(Int i) const { return m_fieldParse[i]; }
	inline UnsignedInt getNthExtraOffset(Int i) const { return m_extraOffset[i]; }
};

//-------------------------------------------------------------------------------------------------
/** Function typedef for parsing INI types blocks */
//-------------------------------------------------------------------------------------------------
typedef void (*INIBlockParse)( INI *ini );
typedef void (*BuildMultiIniFieldProc)(MultiIniFieldParse& p);

//-------------------------------------------------------------------------------------------------
/** INI Reader interface */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// One line of an INI file, as BFME's loader stores them: the text and the line
// number it came from. Eight bytes, which is the stride readLine divides by.
struct INILine
{
	const char *m_text;
	Int m_number;
};

// The array INI::load fills and readLine walks. Both accessors are bounds-checked
// and return 0 past the end.
class INILineBuffer
{
public:
	// Inline: readLine computes the count from the two pointers in line
	// ((end - begin) >> 3) rather than calling anything.
	Int count( void ) const { return m_end - m_begin; }

	const char *getText( Int index ) const;		// 0x009CBC60
	Int getNumber( Int index ) const;			// 0x009CBC90

	// Public because readLine subtracts them in line rather than going through
	// count(), which is how retail reads them -- straight off the INI, with no
	// address of the buffer taken.
	void *m_unknown0;			// +0x00
	void *m_unknown4;			// +0x04
	INILine *m_begin;			// +0x08
	INILine *m_end;				// +0x0c
};

class INI
{
  INI(const INI&);
  INI& operator=(const INI&);

public:

	INI();
	~INI();

	void loadDirectory( AsciiString dirName, Bool subdirs, INILoadType loadType, Xfer *pXfer );  ///< load directory of INI files
	void load( AsciiString filename, INILoadType loadType, Xfer *pXfer );		///< load INI file

	// Provisional names, pinned in reverse/symbols.csv. loadFile (0x00853A20) is
	// the entry point GameEngine::init uses six times and the legend path uses
	// for every InitFile; it drives the block loop itself, calling parseBlock
	// (0x00851350, which strtoks the line, looks the block keyword up and records
	// m_curBlockStart) once per block until m_endOfFile.
	void loadFile( AsciiString filename, INILoadType loadType, Xfer *pXfer );
	void parseBlock( AsciiString filename );

	static Bool isDeclarationOfType( AsciiString blockType, AsciiString blockName, char *bufferToCheck );
	static Bool isEndOfBlock( char *bufferToCheck );

	// data type parsing (the highest level of what type of thing we're parsing)
	static void parseObjectDefinition( INI *ini );
	// BFME's shared body takes three names, not Zero Hour's two: the block
	// prints both "ObjectReskin must come after the original Object" and
	// "ChildObject must come after the original Object", so reskinFrom and
	// childOf are separate arguments.
	static void parseObjectDefinition( INI *ini, const AsciiString &name,
									   const AsciiString &reskinFrom,
									   const AsciiString &childOf );
	static void parseObjectReskinDefinition( INI *ini );
	static void parseChildObjectDefinition( INI *ini );   // BFME-only block
	static void parseWeaponTemplateDefinition( INI *ini );
	static void parseScienceDefinition( INI *ini );
	static void parseRankDefinition( INI *ini );
	static void parseCrateTemplateDefinition( INI *ini );
	static void parseLocomotorTemplateDefinition( INI *ini );
	static void parseLanguageDefinition( INI *ini );
	static void parsePlayerTemplateDefinition( INI *ini );
	static void parseGameDataDefinition( INI *ini );
	static void parseMapDataDefinition( INI *ini );
	static void parseAnim2DDefinition( INI *ini );
	static void parseAudioEventDefinition( INI *ini );
	static void parseDialogDefinition( INI *ini );
	static void parseMusicTrackDefinition( INI *ini );
	static void parseWebpageURLDefinition( INI *ini );
	static void parseHeaderTemplateDefinition( INI *ini );
	static void parseParticleSystemDefinition( INI *ini );
	static void parseWaterSettingDefinition( INI *ini );
	static void parseWaterTransparencyDefinition( INI *ini );
	static void parseWeatherDefinition( INI *ini );
	static void parseMappedImageDefinition( INI *ini );
	static void parseArmorDefinition( INI *ini );
	static void parseDamageFXDefinition( INI *ini );
	static void parseDrawGroupNumberDefinition( INI *ini );
	static void parseTerrainDefinition( INI *ini );
	static void parseTerrainRoadDefinition( INI *ini );
	static void parseTerrainBridgeDefinition( INI *ini );
	static void parseMetaMapDefinition( INI *ini );
	static void parseFXListDefinition( INI *ini );
	static void parseObjectCreationListDefinition( INI* ini );
	static void parseMultiplayerSettingsDefinition( INI* ini );
	static void parseMultiplayerColorDefinition( INI* ini );
  static void parseMultiplayerStartingMoneyChoiceDefinition( INI* ini );
	static void parseOnlineChatColorDefinition( INI* ini );
	static void parseMapCacheDefinition( INI* ini );
	static void parseVideoDefinition( INI* ini );
	static void parseCommandButtonDefinition( INI *ini );
	static void parseCommandSetDefinition( INI *ini );
	static void parseUpgradeDefinition( INI *ini );
	static void parseMouseDefinition( INI* ini );
	static void parseMouseCursorDefinition( INI* ini );
	static void parseAIDataDefinition( INI *ini );
	static void parseSpecialPowerDefinition( INI *ini );
	static void parseInGameUIDefinition( INI *ini );
	static void parseControlBarSchemeDefinition( INI *ini );
	static void parseControlBarResizerDefinition( INI *ini );
	static void parseShellMenuSchemeDefinition( INI *ini );
	static void parseCampaignDefinition( INI *ini );
	static void parseAudioSettingsDefinition( INI *ini );
	static void parseMiscAudio( INI *ini );
	static void parseMiscEvaData( INI *ini );   // BFME-only block
	static void parseStaticGameLODDefinition( INI *ini);
	static void parseDynamicGameLODDefinition( INI *ini);
	// BFME-only block; Zero Hour has no audio LOD level at all.
	static void parseAudioLODDefinition( INI *ini);
	static void parseStaticGameLODLevel( INI* ini, void * , void *store, const void*);
	static void parseDynamicGameLODLevel( INI* ini, void * , void *store, const void*);
	static void parseLODPreset( INI* ini);
	static void parseBenchProfile( INI* ini);
	static void parseEvaEvent( INI* ini );
	static void parseCredits( INI* ini );
	static void parseWindowTransitions( INI* ini );
	static void parseChallengeModeDefinition( INI* ini );

	inline AsciiString getFilename( void ) const { return m_filename; }
	inline INILoadType getLoadType( void ) const { return m_loadType; }
	inline UnsignedInt getLineNum( void ) const { return m_lineNum; }
	inline const char *getSeps( void ) const { return m_seps; }
	inline const char *getSepsPercent( void ) const { return m_sepsPercent; }
	inline const char *getSepsColon( void ) const { return m_sepsColon; }
	inline const char *getSepsQuote( void ) { return m_sepsQuote; }
	inline Bool isEOF( void ) const { return m_endOfFile; }

	void initFromINI( void *what, const FieldParse* parseTable );
	void initFromINIMulti( void *what, const MultiIniFieldParse& parseTableList );
	void initFromINIMultiProc( void *what, BuildMultiIniFieldProc proc );
	
	static void parseUnsignedByte( INI *ini, void *instance, void *store, const void* userData );
	static void parseShort( INI *ini, void *instance, void *store, const void* userData );
	static void parseUnsignedShort( INI *ini, void *instance, void *store, const void* userData );
	static void parseInt( INI *ini, void *instance, void *store, const void* userData );
	static void parseUnsignedInt( INI *ini, void *instance, void *store, const void* userData );
	static void parseReal( INI *ini, void *instance, void *store, const void* userData );
	static void parsePositiveNonZeroReal( INI *ini, void *instance, void *store, const void* userData );
	static void parseBool( INI *ini, void *instance, void *store, const void* userData );
	static void parseBitInInt32( INI *ini, void *instance, void *store, const void* userData );
	static void parseAsciiString( INI *ini, void *instance, void *store, const void* userData );
	static void parseQuotedAsciiString( INI *ini, void *instance, void *store, const void* userData );
	static void parseAsciiStringVector( INI *ini, void *instance, void *store, const void* userData );
	static void parseAsciiStringVectorAppend( INI *ini, void *instance, void *store, const void* userData );
	static void parseAndTranslateLabel( INI *ini, void *instance, void *store, const void* userData );
	static void parseMappedImage( INI *ini, void *instance, void *store, const void *userData );
	static void parseAnim2DTemplate( INI *ini, void *instance, void *store, const void *userData );
	static void parsePercentToReal( INI *ini, void *instance, void *store, const void* userData );
	static void parseRGBColor( INI *ini, void *instance, void *store, const void* userData );
	static void parseRGBAColorInt( INI *ini, void *instance, void *store, const void* userData );
	static void parseColorInt( INI *ini, void *instance, void *store, const void* userData );
	static void parseCoord3D( INI *ini, void *instance, void *store, const void* userData );
	static void parseCoord2D( INI *ini, void *instance, void *store, const void *userData );
	static void parseICoord2D( INI *ini, void *instance, void *store, const void *userData );
	static void parseDynamicAudioEventRTS( INI *ini, void *instance, void *store, const void* userData );
	static void parseAudioEventRTS( INI *ini, void *instance, void *store, const void* userData );
	static void parseFXList( INI *ini, void *instance, void *store, const void* userData );
	static void parseParticleSystemTemplate( INI *ini, void *instance, void *store, const void *userData );
	static void parseObjectCreationList( INI *ini, void *instance, void *store, const void* userData );
	static void parseSpecialPowerTemplate( INI *ini, void *instance, void *store, const void *userData );
	static void parseUpgradeTemplate( INI *ini, void *instance, void *store, const void *userData );
	static void parseScience( INI *ini, void *instance, void *store, const void *userData );
	static void parseScienceVector( INI *ini, void *instance, void *store, const void *userData );
	static void parseGameClientRandomVariable( INI* ini, void *instance, void *store, const void* userData );
	static void parseBitString8( INI *ini, void *instance, void *store, const void* userData );
	static void parseBitString32( INI *ini, void *instance, void *store, const void* userData );
	static void parseByteSizedIndexList( INI *ini, void *instance, void *store, const void* userData );
	static void parseIndexList( INI *ini, void *instance, void *store, const void* userData );
	static void parseLookupList( INI *ini, void *instance, void *store, const void* userData );
	static void parseThingTemplate( INI *ini, void *instance, void *store, const void* userData );
	static void parseArmorTemplate( INI *ini, void *instance, void *store, const void* userData );
	static void parseDamageFX( INI *ini, void *instance, void *store, const void* userData );
	static void parseWeaponTemplate( INI *ini, void *instance, void *store, const void* userData );
	// parse a duration in msec and convert to duration in frames
	static void parseDurationReal( INI *ini, void *instance, void *store, const void* userData );
	// parse a duration in msec and convert to duration in integral number of frames, (unsignedint) rounding UP
	static void parseDurationUnsignedInt( INI *ini, void *instance, void *store, const void* userData );
	static void parseDurationUnsignedShort( INI *ini, void *instance, void *store, const void *userData );
	// parse acceleration in (dist/sec) and convert to (dist/frame)
	static void parseVelocityReal( INI *ini, void *instance, void *store, const void* userData );
	// parse acceleration in (dist/sec^2) and convert to (dist/frame^2)
	static void parseAccelerationReal( INI *ini, void *instance, void *store, const void* userData );
	// parse angle in degrees and convert to radians
	static void parseAngleReal( INI *ini, void *instance, void *store, const void *userData );
	// note that this parses in degrees/sec, and converts to rads/frame!
	static void parseAngularVelocityReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseDamageTypeFlags(INI* ini, void* instance, void* store, const void* userData);
	static void parseDeathTypeFlags(INI* ini, void* instance, void* store, const void* userData);
	static void parseVeterancyLevelFlags(INI* ini, void* instance, void* store, const void* userData);
	static void parseSoundsList( INI* ini, void *instance, void *store, const void* /*userData*/ );
	
	
	/**
		return the next token. if seps is null (or omitted), the standard seps are used.
		
		this will *never* return null; if there are no more tokens, an exception will be thrown.
	*/
	// Declared, not defined: this is the half of the ini_inline shim for the
	// callers that reach the out-of-line copy at 0x00850970 instead of inlining
	// it. ScienceStore::friend_parseScienceDefinition is one -- it opens with a
	// call there, so a TU that inlines getNextToken cannot reproduce it.
	const char* getNextToken(const char* seps = NULL);

	/**
		just like getNextToken(), except that null is returned if no more tokens are present
		(rather than throwing an exception). usually you should call getNextToken(),
		but for some cases this is handier (ie, parsing a variable-length number of tokens).
	*/
	const char* getNextTokenOrNull(const char* seps = NULL);

	/**
		This is called when the next thing you expect is something like:
			
			Tag:value

		pass "Tag" (without the colon) for 'expected', and you will have the 'value'
		token returned.

		If "Tag" is not the next token, an error is thrown.
	*/
	const char* getNextSubToken(const char* expected);

	/**
		return the next ascii string. this is usually the same the result of getNextToken(),
		except that it allows for quote-delimited strings (eg, "foo bar"), so you can
		get strings with spaces, and/or empty strings.
	*/
	AsciiString getNextAsciiString();
	AsciiString getNextQuotedAsciiString();	//fixed version of above.  We can't fix the regular one for fear of breaking existing code. :-(

	/**
		utility routine that does a sscanf() on the string to get the Science, and throws
		an exception if not of the right form.
	*/
	static ScienceType scanScience(const char* token);

	/**
		utility routine that does a sscanf() on the string to get the int, and throws
		an exception if not of the right form.
	*/
	// BFME-only, and the name is provisional (pinned in reverse/symbols.csv):
	// 0x008524B0 takes a token, and if it does not start with a digit or '-'
	// hashes it and looks it up in the macro table at 0x0130CE5C, returning the
	// substituted text. That is the "or predefined macro" half of scanInt's
	// error message; ZH has no such feature.
	static const char *preprocessMacro(const char *token);

	static Int scanInt(const char* token)
	{
		Int value;
		const char *text = preprocessMacro(token);
		if (sscanf(text, "%d", &value) != 1)
			throw INIException(3, "Expected signed integer value or predefined macro, but found '%s'", text);
		return value;
	}

	/**
		utility routine that does a sscanf() on the string to get the unsigned int, and throws
		an exception if not of the right form.
	*/
	static UnsignedInt scanUnsignedInt(const char* token);

	/**
		utility routine that does a sscanf() on the string to get the real, and throws
		an exception if not of the right form.
	*/
	static Real scanReal(const char* token);
	// Inline in this TU: retail's parsePercentToReal (0x00852EE0) calls scanReal
	// and then multiplies by the 0.01f constant at 0x01076C24 in line, rather
	// than calling out to scanPercentToReal.
	static Real scanPercentToReal(const char* token) { return scanReal(token) * 0.01f; }

	static Int scanIndexList(const char* token, ConstCharPtrArray nameList);
	static Int scanLookupList(const char* token, ConstLookupListRecArray lookupList);

	static Bool scanBool(const char* token);

protected:

	static Bool isValidINIFilename( const char *filename ); ///< is this a valid .ini filename		

	void prepFile( AsciiString filename, INILoadType loadType );
	void unPrepFile();

	// BFME factors the per-line block dispatch out of load: strtok the buffer,
	// findBlockParse the first token, copy the line into m_curBlockStart and
	// invoke. The filename comes along for the error message. 0x00851350, and the
	// name is ours -- Zero Hour writes this inline in load, so there is nothing to
	// take it from.
	void parseLine( AsciiString filename );

	void readLine( void );

	File *m_file;															///< file pointer of file currently loading

	AsciiString m_filename;										///< filename of file currently loading
	INILoadType m_loadType;										///< load time for current file
	UnsignedInt m_lineNum;										///< current line number that's been read
	// BFME's line buffer is INI_MAX_CHARS_PER_LINE with no +1, and the 8K
	// m_readBuffer ZH puts ahead of it does not sit here -- both are forced by
	// m_seps landing at +0x414 in retail (every field parser loads it from
	// there). The read-buffer trio is parked at the end of the class so readLine
	// still compiles; only the offsets up to m_seps are load-bearing.
	//
	// INI::INI (0x00851230) writes the whole prefix and confirms it field by
	// field: m_file at +0x00, m_filename at +0x04 (constructed from "None"),
	// +0x08 and +0x0c zeroed, and a byte store at +0x10 -- that byte is
	// m_buffer[0], which is what puts m_seps at +0x414. It then fills
	//   +0x414 m_seps          " \n\r\t="
	//   +0x418 m_sepsPercent   " \n\r\t=%%"
	//   +0x41c m_sepsColon     " \n\r\t=:"
	//   +0x420 m_sepsQuote     "\"\n="
	//   +0x424 m_blockEndToken "END"
	//   +0x428 <unnamed>       "ENDSCRIPT"   <-- BFME-only, ZH has m_endOfFile here
	//   +0x42c                 m_endOfFile (Bool)
	//   +0x42d                 m_curBlockStart, a char array -- initFromINIMulti
	//                          takes its ADDRESS (lea eax,[edi+0x42d]), so this
	//                          is not a second Bool
	//   +0x834                 an object with its own ctor/dtor (0x009CBDC0 /
	//                          0x009CBFE0, both still unidentified)
	// Those separator sets are the tokenizer every INI file is read with, and
	// the extra "ENDSCRIPT" terminator has no ZH counterpart.
	char m_buffer[ INI_MAX_CHARS_PER_LINE ];  ///< buffer to read file contents into
	const char *m_seps;												///< for strtok parsing
	const char *m_sepsPercent;								///< m_seps with percent delimiter as well
	const char *m_sepsColon;									///< m_seps with colon delimiter as well
	const char *m_sepsQuote;									///< token to represent a quoted ascii string
	const char *m_blockEndToken;							///< token to represent end of data block
	// The "ENDSCRIPT" terminator, BFME-only. It was documented in the layout note
	// above but never declared, which left everything after it four bytes low --
	// m_endOfFile in particular, which readLine sets and retail reads at +0x42c.
	const char *m_endScriptToken;							///< second block terminator, "ENDSCRIPT"
	Bool m_endOfFile;													///< TRUE when we've hit EOF
	// NOT #if _DEBUG here, unlike ZH: retail's release build carries this. Its
	// address is taken at +0x42d by initFromINIMulti (lea eax,[edi+0x42d]) and
	// the 4-arg INI::load copies the block keyword into it before invoking the
	// per-block callback, then resets it to "NO_BLOCK".
	char m_curBlockStart[ INI_MAX_CHARS_PER_LINE ];	///< first line of cur block

	// +0x834. BFME does not stream the file a line at a time the way Zero Hour
	// does; INI::load reads it in and splits it here, and readLine just copies the
	// next entry into m_buffer. Elements are eight bytes -- a pointer to the line
	// text and the line's own number -- with begin at +8 and end at +0xc of the
	// object, so the two accessors bounds-check with (end - begin) >> 3.
	//
	// The class and accessor names are ours; nothing in the binary names them.
	// What is proven is the layout, the element size, and that both accessors are
	// out-of-line calls that return 0 when the index is past the end.
	INILineBuffer m_lines;

  enum
  {
    INI_READ_BUFFER = 8192                  ///< size of internal read buffer
  };
  char m_readBuffer[INI_READ_BUFFER];       ///< internal read buffer
  unsigned m_readBufferNext;                ///< next char in read buffer
  unsigned m_readBufferUsed;                ///< number of bytes in read buffer
};

#endif // __INI_H_

