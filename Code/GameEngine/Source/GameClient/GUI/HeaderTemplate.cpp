// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: HeaderTemplate.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Aug 2002
//
//	Filename: 	HeaderTemplate.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	The header template system is used to maintain a unified look across
//						windows.  It also allows Localization to customize the looks based
//						on language fonts.
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"

#include "Common/INI.h"
#include "Common/Filesystem.h"
#include "Common/Registry.h"
#include "GameClient/HeaderTemplate.h"
#include "GameClient/GameFont.h"
#include "GameClient/GlobalLanguage.h"

// The shared headers above describe the ZH object sizes.  HeaderTemplate's
// loader is one of the BFME TUs that still carries the compact INI ABI, so its
// two automatic strings and INI are declared locally.  These are declarations
// only: the retail StringBase/INI bodies remain the shared engine bodies.
template <typename T> class HeaderTemplateStringBase
{
friend class HeaderTemplateString;
private:
	HeaderTemplateStringBase( void );
	HeaderTemplateStringBase( const HeaderTemplateStringBase<T> &that );
	HeaderTemplateStringBase( const T *text );
	void releaseBuffer( void );
	void set( const HeaderTemplateStringBase<T> &that );
};

class HeaderTemplateString
{
public:
	HeaderTemplateString( void ) : m_text( 0 ) {}
	HeaderTemplateString( const HeaderTemplateString &that )
	{
		((HeaderTemplateStringBase<char> *)this)->HeaderTemplateStringBase<char>::HeaderTemplateStringBase(
			*(const HeaderTemplateStringBase<char> *)&that);
	}
	HeaderTemplateString( const char *text )
	{
		((HeaderTemplateStringBase<char> *)this)->HeaderTemplateStringBase<char>::HeaderTemplateStringBase( text );
	}
	~HeaderTemplateString( void );

	void format( HeaderTemplateString fmt, ... );
	const char *str( void ) const
	{
		return m_text ? m_text + 8 : "";
	}
	HeaderTemplateString &operator=( const HeaderTemplateString &that )
	{
		((HeaderTemplateStringBase<char> *)this)->set(
			*(const HeaderTemplateStringBase<char> *)&that);
		return *this;
	}

private:
	char *m_text;
};

// Return type is deliberately TU-local: the ABI is the same two-word value
// used by GetRegistryLanguage, while its body is the retail global language
// accessor (pinned by the conversion ledger when this row is landed).
HeaderTemplateString HeaderTemplateGetRegistryLanguage( void );

enum HeaderTemplateINILoadType
{
	HEADER_TEMPLATE_INI_LOAD_OVERWRITE = 1
};

class HeaderTemplateINI
{
public:
	HeaderTemplateINI( void );
	~HeaderTemplateINI( void );
	void load( HeaderTemplateString filename,
		HeaderTemplateINILoadType loadType, Xfer *xfer );

private:
	char m_unported[0x848];
};

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif
//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
const FieldParse HeaderTemplateManager::m_headerFieldParseTable[] =
{
	{ "Font",								INI::parseQuotedAsciiString,						NULL, offsetof( HeaderTemplate, m_fontName ) },
	{ "Point",							INI::parseInt,										NULL, offsetof( HeaderTemplate, m_point) },
	{ "Bold",								INI::parseBool,										NULL, offsetof( HeaderTemplate, m_bold ) },
	{ NULL, NULL, NULL, 0 },
};

HeaderTemplateManager *TheHeaderTemplateManager = NULL;
//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ?parseHeaderTemplateDefinition@INI@@SAXPAV1@@Z body in
// Code/masm_dumps/INI_parseHeaderTemplateDefinition_48CBD0.asm (0x0048CBD0/195).
// Queue 0x009A15AF was prior-fn epilogue+pad; C++ blocked by ZH vs BFME AsciiString.

// ??0HeaderTemplate@@QAE@XZ present-unmatched
HeaderTemplate::HeaderTemplate( void ) :
m_font(NULL),
m_point(0),
m_bold(FALSE)
{
	//Added By Sadullah Nader
	//Initializations missing and needed 
	m_fontName.clear();
	m_name.clear();
}

// ??1HeaderTemplate@@QAE@XZ present-unmatched
HeaderTemplate::~HeaderTemplate( void ){}

// ??0HeaderTemplateManager@@QAE@XZ present-unmatched
HeaderTemplateManager::HeaderTemplateManager( void )
{}

// ??1HeaderTemplateManager@@QAE@XZ present-unmatched
HeaderTemplateManager::~HeaderTemplateManager( void )
{
	HeaderTemplateListIt it = m_headerTemplateList.begin();
	while(it != m_headerTemplateList.end())
	{
		HeaderTemplate *hTemplate = *it;
		if(hTemplate)
		{
			hTemplate->m_font = NULL;
			delete hTemplate;
		}
		it = m_headerTemplateList.erase(it);

	}
}

// ?init@HeaderTemplateManager@@QAEXXZ — BFME compact INI/string ABI shim below
void HeaderTemplateManager::init( void )
{
	HeaderTemplateINI ini;
	HeaderTemplateString fname;
	fname.format("Lang\\%s\\HeaderTemplate.ini", HeaderTemplateGetRegistryLanguage().str());
	OSVERSIONINFO	osvi;
	osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osvi))
	{	//check if we're running Win9x variant since they may need different fonts
		if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
		{	HeaderTemplateString tempName;

			tempName.format("Lang\\%s\\HeaderTemplate9x.ini", HeaderTemplateGetRegistryLanguage().str());
			if (TheFileSystem->doesFileExist(tempName.str()))
				fname = tempName;
		}
	}
	ini.load( fname, HEADER_TEMPLATE_INI_LOAD_OVERWRITE, NULL );
	populateGameFonts();
}

// ?findHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z present-unmatched
HeaderTemplate *HeaderTemplateManager::findHeaderTemplate( AsciiString name )
{
	HeaderTemplateListIt it = m_headerTemplateList.begin();
	while(it != m_headerTemplateList.end())
	{
		HeaderTemplate *hTemplate = *it;
		if(hTemplate->m_name.compare(name) == 0)
			return hTemplate;
		++it;
	}
	return NULL;
}

// ?newHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z body in
// Code/masm_dumps/HeaderTemplateManager_newHeaderTemplate_48CAD0.asm (0x0048CAD0/204).
// Queue 0x00B026CE was INSIDE scalar-deleting dtor @ 0xB026C0; true body via
// parseHeaderTemplateDefinition call ILT 0x470E6. C++ blocked by STL push_front shape.

// ?getFontFromTemplate@HeaderTemplateManager@@QAEPAVGameFont@@VAsciiString@@@Z present-unmatched
GameFont *HeaderTemplateManager::getFontFromTemplate( AsciiString name )
{
	HeaderTemplate *ht = findHeaderTemplate( name );
	if(!ht)
	{
		//DEBUG_LOG(("HeaderTemplateManager::getFontFromTemplate - Could not find header %s\n", name.str()));
		return NULL;
	}
	
	return ht->m_font;
}

HeaderTemplate *HeaderTemplateManager::getFirstHeader( void )
{
	HeaderTemplateListIt it = m_headerTemplateList.begin();
	if( it == m_headerTemplateList.end())
		return NULL;

	return *it;
}

HeaderTemplate *HeaderTemplateManager::getNextHeader( HeaderTemplate *ht )
{
	HeaderTemplateListIt it = m_headerTemplateList.begin();
	while(it != m_headerTemplateList.end())
	{
		if(*it == ht)
		{
			++it;
			if( it == m_headerTemplateList.end())
				return NULL;
			return *it;
		}
		++it;
	}
	return NULL;

}

// ?headerNotifyResolutionChange@HeaderTemplateManager@@QAEXXZ present-unmatched
void HeaderTemplateManager::headerNotifyResolutionChange( void )
{
	populateGameFonts();
}
//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

// byte-exact reconstruction: Code/GameEngine/Source/GameClient/GUI/HeaderTemplateManagerPopulateGameFontsThunk.cpp
// ?populateGameFonts@HeaderTemplateManager@@AAEXXZ present-unmatched
void HeaderTemplateManager::populateGameFonts( void )
{
	HeaderTemplateListIt it = m_headerTemplateList.begin();
	while(it != m_headerTemplateList.end())
	{
		HeaderTemplate *hTemplate = *it;
		Real pointSize = TheGlobalLanguageData->adjustFontSize(hTemplate->m_point);
		GameFont *font = TheFontLibrary->getFont(hTemplate->m_fontName, pointSize,hTemplate->m_bold);
		DEBUG_ASSERTCRASH(font,("HeaderTemplateManager::populateGameFonts - Could not find font %s %d",hTemplate->m_fontName, hTemplate->m_point));

		hTemplate->m_font = font;
		
		++it;
	}
}
