// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
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

// FILE: W3DDisplayStringManager.cpp //////////////////////////////////////////////////////////////
// Created: Colin Day, July 2001
// Desc:    Display string Manager for W3D
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>

#include "Common/Debug.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/DisplayString.h"
#include "GameClient/DrawGroupInfo.h"
#include "GameClient/GlobalLanguage.h"
// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "W3DDevice/GameClient/W3DDisplayStringManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS 
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
W3DDisplayStringManager::W3DDisplayStringManager( void )
{
	for (Int i = 0; i < MAX_GROUPS; ++i) 
	{
		m_groupNumeralStrings[i] = NULL;
	}

	m_formationLetterDisplayString = NULL;

}

//-------------------------------------------------------------------------------------------------
W3DDisplayStringManager::~W3DDisplayStringManager( void )
{
	for (Int i = 0; i < MAX_GROUPS; ++i) 
	{
		if (m_groupNumeralStrings[i])
			freeDisplayString(m_groupNumeralStrings[i]);
		m_groupNumeralStrings[i] = NULL;
	}

	if (m_formationLetterDisplayString)
		freeDisplayString( m_formationLetterDisplayString );
	m_formationLetterDisplayString = NULL;


}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/W3DDisplayStringManager_postProcessLoadMethodThunk.cpp
// ?postProcessLoad@W3DDisplayStringManager@@UAEXXZ present-unmatched
void W3DDisplayStringManager::postProcessLoad( void )
{
	// Get the font.
	GameFont *font = TheFontLibrary->getFont(
		TheDrawGroupInfo->m_fontName,
		TheDrawGroupInfo->m_fontSize,
		TheDrawGroupInfo->m_fontIsBold );
	
	for (Int i = 0; i < MAX_GROUPS; ++i) 
	{
		m_groupNumeralStrings[i] = newDisplayString();
		m_groupNumeralStrings[i]->setFont(font);

#ifdef KRIS_BRUTAL_HACK_FOR_AIRCRAFT_CARRIER_DEBUGGING
		UnicodeString displayNumber;
		displayNumber.format( L"%d", i);
		m_groupNumeralStrings[i]->setText( displayNumber );
#else
 		AsciiString displayNumber;
 		displayNumber.format("NUMBER:%d", i);
 		m_groupNumeralStrings[i]->setText(TheGameText->fetch(displayNumber));
#endif
	}

	m_formationLetterDisplayString = newDisplayString();
	m_formationLetterDisplayString->setFont(font);
	AsciiString displayLetter;
	displayLetter.format("LABEL:FORMATION");
	m_formationLetterDisplayString->setText(TheGameText->fetch(displayLetter));


}

//-------------------------------------------------------------------------------------------------
/** Allocate a new display string and tie it to the master list so we
	* can keep track of it */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/Libraries/Source/WWVegas/WW3D2/W3DDisplayStringManagerNewDisplayStringThunk.cpp
// ?newDisplayString@W3DDisplayStringManager@@UAEPAVDisplayString@@XZ present-unmatched
DisplayString *W3DDisplayStringManager::newDisplayString( void )
{
	DisplayString *newString = newInstance(W3DDisplayString);

	// sanity
	if( newString == NULL )
	{

		DEBUG_LOG(( "newDisplayString: Could not allcoate new W3D display string\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// assign a default font
	if (TheGlobalLanguageData && TheGlobalLanguageData->m_defaultDisplayStringFont.name.isNotEmpty())
	{
		newString->setFont(TheFontLibrary->getFont(
			TheGlobalLanguageData->m_defaultDisplayStringFont.name,
			TheGlobalLanguageData->m_defaultDisplayStringFont.size,
			TheGlobalLanguageData->m_defaultDisplayStringFont.bold) );
	}
	else
		newString->setFont( TheFontLibrary->getFont( AsciiString("Times New Roman"), 12, FALSE ) );

	// link string to list
	link( newString );

	// return our new string
	return newString;

}  // end newDisplayString

//-------------------------------------------------------------------------------------------------
/** Remove a display string from the master list and delete the data */
//-------------------------------------------------------------------------------------------------
class BfmeDeletableDisplayString
{
public:
	virtual ~BfmeDeletableDisplayString();
};

void W3DDisplayStringManager::freeDisplayString( DisplayString *string )
{

	// sanity
	if( string == NULL )
		return;
			
	// unlink
	unLink( string );

	// if the string happens to fall where our current checkpoint was, set the checkpoint to null
	if ( m_currentCheckpoint == string) {
		m_currentCheckpoint = NULL;
	}

	// BFME deletes it rather than returning it to the pool: retail is the scalar
	// deleting destructor, vtable slot 0 with the flag pushed as 1, where
	// deleteInstance() compiles to the two-call memory-pool teardown. The cast is
	// only there because the real DisplayString keeps its destructor protected, as
	// every memory-pool class does; the dispatch is through slot 0 either way.
	delete (BfmeDeletableDisplayString *)string;

}  // end freeDisplayString

//-------------------------------------------------------------------------------------------------
/** Update method for our display string Manager ... if it's been too
	* long since the last time a string has been rendered, we will free
	* the rendering resources of the string, if it needs to render again
	* the DisplayString will have to rebuild the rendering data before
	* the draw will work */
//-------------------------------------------------------------------------------------------------
class BFMEUpdateRenderSentence
{
public:
	virtual void Reset( void );
};

struct BFMEUpdateDisplayString
{
	unsigned char m_unreconstructed_00[0x0C];
	BFMEUpdateDisplayString *m_next;
	unsigned char m_unreconstructed_10[0x14 - 0x10];
	BFMEUpdateRenderSentence m_textRenderer;
	unsigned char m_unreconstructed_18[0xE0 - 0x18];
	BFMEUpdateRenderSentence m_textRendererHotKey;
	unsigned char m_unreconstructed_E4[0x1AC - 0xE4];
	unsigned char m_textChanged;
	unsigned char m_unreconstructed_1AD[0x208 - 0x1AD];
	UnsignedInt m_lastResourceFrame;

};

struct BFMEUpdateManagerFields
{
	unsigned char m_unreconstructed_00[0x08];
	BFMEUpdateDisplayString *m_stringList;
	BFMEUpdateDisplayString *m_currentCheckpoint;
};
void W3DDisplayStringManager::update( void )
{
	BFMEUpdateManagerFields *fields = reinterpret_cast<BFMEUpdateManagerFields *>(this);
	BFMEUpdateDisplayString *string = fields->m_stringList;
	if (fields->m_currentCheckpoint)
		string = fields->m_currentCheckpoint;

	UnsignedInt currFrame = TheGameClient->getFrame();
	const UnsignedInt w3dCleanupTime = 60;  /** any string not rendered after
																					this many frames will have its
																					render resources freed */

	int numStrings = 10;
	// looping through all the strings eats up a lot of ambient time. Instead, 
	// loop through 10 (arbitrarily chosen) or till the end is hit.
	while ( numStrings-- && string)
	{

		//
		// has this string "expired" in terms of using resources, a string
		// with a resource frame of zero isn't using any resources at all
		//
		if( string->m_lastResourceFrame != 0 &&
				currFrame - string->m_lastResourceFrame > w3dCleanupTime )
		{

			// free the resources
			string->m_textRenderer.Reset();
			string->m_textRendererHotKey.Reset();
			//
			// mark data in the string as changed so that if it needs to
			// be drawn again it will know to reconstruct the render data
			//
			string->m_textChanged = TRUE;

			//
			// set the last resource frame to zero, this allows us to ignore it
			// in future cleanup passes of this update routine
			//
			string->m_lastResourceFrame = 0;
			
		}  // end if

		// move to next string
		string = reinterpret_cast<BFMEUpdateDisplayString *>(
			reinterpret_cast<DisplayString *>(string)->next());

	}  // end while
	
	// reset the starting point for our next search
	fields->m_currentCheckpoint = string;
}  // end update

//-------------------------------------------------------------------------------------------------
DisplayString *W3DDisplayStringManager::getGroupNumeralString( Int numeral )
{
	if (numeral < 0 || numeral > MAX_GROUPS - 1 ) 
	{
		DEBUG_CRASH(("Numeral '%d' out of range.\n", numeral));
		return m_groupNumeralStrings[0];
	}

	return m_groupNumeralStrings[numeral];
}
