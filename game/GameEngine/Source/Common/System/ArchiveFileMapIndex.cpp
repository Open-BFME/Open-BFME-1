// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// ArchiveFileSystem uses this pointer map at retail RVA 0x00063960.
// openFile dereferences the returned mapped reference as ArchiveFile*.
// The full 169-byte body includes both returns and one temporary-key cleanup.

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <map>

class ArchiveFile;

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const
	{
		return left.compare( right ) < 0;
	}
};
}

typedef _STL::map<AsciiString, ArchiveFile *, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, ArchiveFile *> > >
	Rva00063960ArchiveFileMap;

// Canonical ArchiveFileMap specialization:
// ??A?$map@VAsciiString@@PAVArchiveFile@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@PAVArchiveFile@@@_STL@@@4@@_STL@@QAEAAPAVArchiveFile@@ABVAsciiString@@@Z
// Natural instantiation of the complete body at RVA 0x00063960.
template ArchiveFile *&Rva00063960ArchiveFileMap::operator[](
	const AsciiString &key );
