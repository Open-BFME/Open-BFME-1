// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/archivefilesystem_nosubsystem /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib

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

class ArchivedDirectoryInfo;
typedef std::map<AsciiString, ArchivedDirectoryInfo> ArchivedDirectoryInfoMap;
typedef std::map<AsciiString, AsciiString> ArchivedFileLocationMap;

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

class ArchivedDirectoryInfo
{
public:
	ArchivedDirectoryInfo();
	ArchivedDirectoryInfo(const ArchivedDirectoryInfo &);
	AsciiString m_directoryName;
	ArchivedDirectoryInfoMap m_directories;
	ArchivedFileLocationMap m_files;
};

template ArchivedDirectoryInfo &ArchivedDirectoryInfoMap::operator[](const AsciiString &key);
