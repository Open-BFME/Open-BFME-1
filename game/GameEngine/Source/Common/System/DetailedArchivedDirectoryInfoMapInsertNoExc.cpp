// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/archivefilesystem_nosubsystem /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME7: the hinted insert_unique of DetailedArchivedDirectoryInfoMap as a
// second TU compiled with STLport exceptions off (retail 0x000633E0, 629 bytes)
// -- a byte twin of the map-subscript tree insertion at 0x009CFD20 once
// _STLP_NO_EXCEPTIONS lets MSVC inline _M_create_node.  The comparator tag
// only gives the copy its own decorated name.
#define _STLP_NO_EXCEPTIONS 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

#include "Common/GameMemory.h"
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "Common/STLTypedefs.h"

class DetailedArchivedDirectoryInfo;

class ArchivedFileInfo
{
public:
	AsciiString m_filename;
	AsciiString m_archiveFilename;
	UnsignedInt m_offset;
	UnsignedInt m_size;
};

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};
}

typedef std::map<AsciiString, DetailedArchivedDirectoryInfo> DetailedArchivedDirectoryInfoMap;
typedef std::map<AsciiString, ArchivedFileInfo> ArchivedFileInfoMap;

class DetailedArchivedDirectoryInfo
{
public:
	DetailedArchivedDirectoryInfo();
	DetailedArchivedDirectoryInfo(const DetailedArchivedDirectoryInfo &);

	AsciiString m_directoryName;
	DetailedArchivedDirectoryInfoMap m_directories;
	ArchivedFileInfoMap m_files;
};


struct Rva000633E0Less : public std::less<AsciiString> {};

typedef std::pair<const AsciiString, DetailedArchivedDirectoryInfo> Rva000633E0Pair;
typedef std::_Rb_tree<AsciiString, Rva000633E0Pair, std::_Select1st<Rva000633E0Pair>, Rva000633E0Less,
	std::allocator<Rva000633E0Pair> > Rva000633E0Tree;

template Rva000633E0Tree::iterator Rva000633E0Tree::insert_unique(Rva000633E0Tree::iterator, const Rva000633E0Pair &);
