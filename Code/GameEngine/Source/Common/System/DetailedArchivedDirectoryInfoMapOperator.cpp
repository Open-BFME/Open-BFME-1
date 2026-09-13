// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

#include "Common/GameMemory.h"
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "Common/STLTypedefs.h"

// Retail's AsciiString is a StringBase<char> with no members of its own, so its
// copy ctor at 0x0005EE50 only forwards to the base body at 0x00887B60 -- and
// retail inlines that forwarder here, encoding the base call directly. The
// asciistring_thin shim leaves the copy ctor undefined; defining it in this TU
// puts the delegation in front of the use without changing the shared header.
#include "string_base.h"

inline AsciiString::AsciiString(const AsciiString &stringSrc)
{
	((StringBase<char> *)this)->StringBase<char>::StringBase(
		*(const StringBase<char> *)&stringSrc);
}

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

template DetailedArchivedDirectoryInfo &DetailedArchivedDirectoryInfoMap::operator[](const AsciiString &key);
