// cl: /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/scriptenginelayout /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include
// stlport
//
// INI::loadDirectory (0x00853F10, 700 bytes; the catch(...) funclet that
// rethrows follows at 0x008541CC). Identity: the matched callers
// SubsystemInterface::loadIniFilesFromLegend (0x009A1A50) and
// SubsystemInterfaceList::initSubsystem (0x009A20B0) call it through
// Common/INI/INI.h as loadDirectory(dir, true, INI_LOAD_OVERWRITE, xfer, 0), and
// the body is Zero Hour's INI::loadDirectory (reference INI.cpp:217): "*.ini"
// listed through TheFileSystem, top-level files first, subdirectory files second.
// ret 0x14 is the fifth dword argument, which the body never reads. BFME adds
// the endsWith guard before the separator concat and only runs the second pass
// when subdirs is set; the throw became an INIException (0x00850600).
#define ASCIISTRING_H
#define __INI_H_		// Zero Hour's INI.h, pulled in by PreRTS.h; BFME's INI.h replaces it
#include "Common/INI/INI.h"
#include "PreRTS.h"
#include "Common/FileSystem.h"
#include "Common/INIException.h"

// Retail inlines these StringBase<char> accessors at every use in this body.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
inline AsciiString &AsciiString::operator=(const char *s) { ((StringBase<char> *)this)->set(s); return *this; }
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template<> inline int StringBase<char>::getLength() const { return m_data ? m_data->length : 0; }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline void StringBase<char>::set(const char *s) { set(s, s ? strlen(s) : 0); }
template<> inline void StringBase<char>::concat(char c) { concat(&c, 1); }
template<> inline bool StringBase<char>::endsWith(const char *s) const { return endsWith(s, strlen(s)); }
template<> inline const char *StringBase<char>::find(char c) const
{
	const char *p = str();
	const char *end = p + getLength();
	for( ; p != end; ++p )
		if( *p == c )
			return p;
	return NULL;
}

//-------------------------------------------------------------------------------------------------
/** Load all INI files in the specified directory (and subdirectories if indicated).
	* If we are to load subdirectories, we will load them *after* we load all the
	* files in the current directory */
//-------------------------------------------------------------------------------------------------
void INI::loadDirectory( AsciiString dirName, bool subdirs, INILoadType loadType, Xfer *pXfer, int )
{
	// sanity
	if( dirName.isEmpty() )
		throw INIException( 0, NULL );

	try
	{
		FilenameList filenameList;
		if( !dirName.endsWith( "\\" ) )
			dirName.concat( '\\' );
		TheFileSystem->getFileListInDirectory( dirName, AsciiString( "*.ini" ), filenameList, TRUE );

		// Load the INI files in the dir now, in a sorted order.  This keeps things the same between machines
		// in a network game.
		AsciiString tempname;
		FilenameList::const_iterator it = filenameList.begin();
		while( it != filenameList.end() )
		{
			tempname = (*it).str() + dirName.getLength();
			if( tempname.find( '\\' ) == NULL && tempname.find( '/' ) == NULL )
			{
				// this file doesn't reside in a subdirectory, load it first.
				// INI.h's loadFile is the ledger's INI::load at 0x00853A20.
				loadFile( *it, loadType, pXfer );
			}
			++it;
		}

		if( subdirs )
		{
			it = filenameList.begin();
			while( it != filenameList.end() )
			{
				tempname = (*it).str() + dirName.getLength();
				if( tempname.find( '\\' ) != NULL || tempname.find( '/' ) != NULL )
					loadFile( *it, loadType, pXfer );
				++it;
			}
		}
	}
	catch( ... )
	{
		// propagate the exception
		throw;
	}
}  // end loadDirectory
