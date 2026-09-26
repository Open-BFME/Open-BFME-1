// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Both constructors used to live in ShellMenuSchemeCtor.cpp purely for the
// STLport link mode: retail calls __new_alloc::allocate directly and without
// /D_STLP_USE_STATIC_LIB the header declares it dllimport, so the node
// allocation comes out as `call [__imp_...]` instead of `call`. Adding the
// define here re-verified all 24 rows this file already had, which is what the
// split was avoiding.
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

// FILE: ShellMenuScheme.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Jul 2002
//
//	Filename: 	ShellMenuScheme.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "GameClient/ShellMenuScheme.h"
#include "GameClient/Shell.h"
#include "GameClient/Display.h"
//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

const FieldParse ShellMenuSchemeManager::m_shellMenuSchemeFieldParseTable[] = 
{

	{ "ImagePart",						ShellMenuSchemeManager::parseImagePart,			NULL, NULL },
	{ "LinePart",							ShellMenuSchemeManager::parseLinePart,	NULL, NULL },
	{ NULL,										NULL,													NULL, 0 }  // keep this last

};

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z
// Body is MASM exact-byte dump (game/masm_dumps/INI_parseShellMenuSchemeDefinition_581790.asm).
// Retail @ 0x581790; C++ blocked on AsciiString::set vs StringBase::set(s,len) shape.

ShellMenuSchemeLine::ShellMenuSchemeLine( void )
{
	m_startPos.x = m_startPos.y = 0;
	m_endPos.x = m_endPos.y = 0;
	m_color = GAME_COLOR_UNDEFINED;
	m_width = 1;
}
// ??1ShellMenuSchemeLine@@QAE@XZ present-unmatched
ShellMenuSchemeLine::~ShellMenuSchemeLine( void )
{
}

// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/Shell/ShellMenuSchemeImageConstructor.cpp
// ??0ShellMenuSchemeImage@@QAE@XZ present-unmatched
ShellMenuSchemeImage::ShellMenuSchemeImage( void )
{
	m_name.clear();
	m_position.x = m_position.y = 0;
	m_size.x = m_size.x = 0;
	m_image = NULL;
}

// ??1ShellMenuSchemeImage@@QAE@XZ present-unmatched
ShellMenuSchemeImage::~ShellMenuSchemeImage( void )
{
	m_image = NULL;
}

ShellMenuScheme::ShellMenuScheme( void )
{
	
}

// byte-exact reconstruction: game/GameEngine/Source/Common/ShellMenuSchemeDestructor.cpp
// ??1ShellMenuScheme@@QAE@XZ present-unmatched
ShellMenuScheme::~ShellMenuScheme( void )
{
	ShellMenuSchemeImageListIt it = m_imageList.begin();
	while(it != m_imageList.end())
	{
		ShellMenuSchemeImage *image = *it;
		it = m_imageList.erase( it );
		if(image)
			delete image;
	}

	ShellMenuSchemeLineListIt lineIt = m_lineList.begin();
	while(lineIt != m_lineList.end())
	{
		ShellMenuSchemeLine *line = *lineIt;
		lineIt = m_lineList.erase( lineIt );
		if(line)
			delete line;
	}

	
}

// ?addLine@ShellMenuScheme@@QAEXPAVShellMenuSchemeLine@@@Z present-unmatched
void ShellMenuScheme::addLine( ShellMenuSchemeLine* schemeLine )
{
	if(!schemeLine)
		return;

	m_lineList.push_back( schemeLine );
}


// ?addImage@ShellMenuScheme@@QAEXPAVShellMenuSchemeImage@@@Z present-unmatched
void ShellMenuScheme::addImage( ShellMenuSchemeImage* schemeImage )
{
	if(!schemeImage)
		return;

	m_imageList.push_back( schemeImage );
}

// Display as ShellMenuScheme::draw reaches it: slot +0xB0 opens and +0xDC
// closes a precise-draw bracket around the Real-coordinate image (+0xD4) and
// line (+0xB8) calls; the inline wrappers take Real coordinates, so the Int
// fields are converted at the call site in right-to-left argument order.
// Address-derived; never treat as an identity.
class Rva00580BD0Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void beginRva00580BD0( void ); // +0xB0
	virtual void slotB4();
	virtual void drawLineRva00580BD0( Real startX, Real startY, Real endX, Real endY,
		Real lineWidth, UnsignedInt lineColor ); // +0xB8
	virtual void slotBC(); virtual void slotC0(); virtual void slotC4();
	virtual void slotC8(); virtual void slotCC(); virtual void slotD0();
	virtual void drawImageRva00580BD0( const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode ); // +0xD4
	virtual void slotD8();
	virtual void endRva00580BD0( void ); // +0xDC

	void drawImage( const Image *image, Real startX, Real startY, Real endX, Real endY,
		Color color = 0xFFFFFFFF, Int mode = 2 )
	{
		beginRva00580BD0();
		drawImageRva00580BD0( image, startX, startY, endX, endY, color, mode );
		endRva00580BD0();
	}

	void drawLine( Real startX, Real startY, Real endX, Real endY, Real lineWidth,
		UnsignedInt lineColor )
	{
		beginRva00580BD0();
		drawLineRva00580BD0( startX, startY, endX, endY, lineWidth, lineColor );
		endRva00580BD0();
	}
};

void ShellMenuScheme::draw( void )
{

	ShellMenuSchemeImageListIt imageIt = m_imageList.begin();
	while(imageIt != m_imageList.end())
	{
		ShellMenuSchemeImage *image = *imageIt;
		if(image && image->m_image)
		{
			((Rva00580BD0Display *)TheDisplay)->drawImage(image->m_image, image->m_position.x, image->m_position.y,
														image->m_position.x + image->m_size.x , image->m_position.y + image->m_size.y);
		}
		++imageIt;
	}

	ShellMenuSchemeLineListIt it = m_lineList.begin();
	while(it != m_lineList.end())
	{
		ShellMenuSchemeLine *line = *it;
		
		if(line)
		{
			((Rva00580BD0Display *)TheDisplay)->drawLine(line->m_startPos.x, line->m_startPos.y, line->m_endPos.x,
														line->m_endPos.y,line->m_width, line->m_color);
		}
		++it;
	}


}

ShellMenuSchemeManager::ShellMenuSchemeManager( void )
{
	m_currentScheme = NULL;
}

ShellMenuSchemeManager::~ShellMenuSchemeManager( void )
{
	m_currentScheme = NULL;


	ShellMenuSchemeListIt it = m_schemeList.begin();
	while(it != m_schemeList.end())
	{
		ShellMenuScheme *scheme = *it;
		it = m_schemeList.erase( it );
		if(scheme)
			delete scheme;
	}
	
}

// byte-exact reconstruction: game/GameEngine/Source/Common/ShellMenuSchemeManager_parseImagePart_Thunk.cpp
// ?parseImagePart@ShellMenuSchemeManager@@ present-unmatched
void ShellMenuSchemeManager::parseImagePart(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
{
	static const FieldParse myFieldParse[] = 
		{
			{ "Position",				INI::parseICoord2D,				NULL, offsetof( ShellMenuSchemeImage, m_position ) },
			{ "Size",						INI::parseICoord2D,				NULL, offsetof( ShellMenuSchemeImage, m_size ) },
      { "ImageName",			INI::parseMappedImage,		NULL, offsetof( ShellMenuSchemeImage, m_image ) },
			{ NULL,							NULL,											NULL, 0 }  // keep this last
		};

	ShellMenuSchemeImage *schemeImage = NEW ShellMenuSchemeImage;
	ini->initFromINI(schemeImage, myFieldParse);
	((ShellMenuScheme*)instance)->addImage(schemeImage);

}

// byte-exact reconstruction: game/GameEngine/Source/Common/ShellMenuSchemeManager_parseLinePart_Thunk.cpp
// ?parseLinePart@ShellMenuSchemeManager@@ present-unmatched
void ShellMenuSchemeManager::parseLinePart(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
{
	static const FieldParse myFieldParse[] = 
		{
			{ "StartPosition",		INI::parseICoord2D,				NULL, offsetof( ShellMenuSchemeLine, m_startPos ) },
			{ "EndPosition",			INI::parseICoord2D,				NULL, offsetof( ShellMenuSchemeLine, m_endPos ) },
      { "Color",						INI::parseColorInt,				NULL, offsetof( ShellMenuSchemeLine, m_color ) },
			{ "Width",						INI::parseInt,						NULL, offsetof( ShellMenuSchemeLine, m_width ) },
			
			{ NULL,								NULL,											NULL, 0 }  // keep this last
		};

	ShellMenuSchemeLine *schemeLine = NEW ShellMenuSchemeLine;
	ini->initFromINI(schemeLine, myFieldParse);
	((ShellMenuScheme*)instance)->addLine(schemeLine);

}

// byte-exact reconstruction: game/GameEngine/Source/Common/ShellMenuSchemeManager_newShellMenuScheme_Thunk.cpp
// ?newShellMenuScheme@ShellMenuSchemeManager@@QAEPAVShellMenuScheme@@VAsciiString@@@Z present-unmatched
ShellMenuScheme *ShellMenuSchemeManager::newShellMenuScheme(AsciiString name)
{
	ShellMenuSchemeListIt it;
	it = m_schemeList.begin();
	name.toLower();
	while(it != m_schemeList.end())
	{
		ShellMenuScheme *scheme = *it;
		if(scheme->m_name.compare(name) == 0)
		{
			m_schemeList.erase( it );
			delete scheme;
			break;
		}
		else
			++it;
	}
	ShellMenuScheme *newScheme = NEW ShellMenuScheme;
	newScheme->m_name.set(name);
	m_schemeList.push_back(newScheme);
	return newScheme;
}

void ShellMenuSchemeManager::init( void )
{
}

// byte-exact reconstruction: game/GameEngine/Source/GameClient/ShellMenuScheme_set.cpp
// ?setShellMenuScheme@ShellMenuSchemeManager@@QAEXVAsciiString@@@Z present-unmatched
void ShellMenuSchemeManager::setShellMenuScheme( AsciiString name )
{
	if(name.isEmpty())
	{
		m_currentScheme = NULL;
		return;
	}

	ShellMenuSchemeListIt it;
	it = m_schemeList.begin();
	name.toLower();
	while(it != m_schemeList.end())
	{
		ShellMenuScheme *scheme = *it;
		if(scheme->m_name.compare(name) == 0)
		{
			m_currentScheme = scheme;
			break;
		}
		++it;
	}
}

void ShellMenuSchemeManager::draw( void )
{
	if(m_currentScheme)
		m_currentScheme->draw();
}

void ShellMenuSchemeManager::update( void )
{

}
//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
