// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
