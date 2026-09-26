// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/archivefilesystem_nosubsystem /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// Open-BFME7: fuzzy twin of ArchivedDirectoryInfoMapOperator.cpp
// (0x009CAB10, 233 B): std::map<AsciiString, T>::operator[] with
// T = ArchivedFileInfo instead of ArchivedDirectoryInfo, retail 0x009D0C50,
// 236 bytes. ArchivedFileInfoCopyConstructorThunk.cpp supplies the mapped
// type identity. The key copy calls StringBase<char> at 887B60 after the
// AsciiString forwarding copy constructor is inlined.

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

#include "Common/GameMemory.h"
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "Common/STLTypedefs.h"
#include "string_base.h"

// Retail 5EE50 is the 19-byte AsciiString forwarding constructor;
// this call site inlines it and calls the distinct StringBase copy at 887B60.
inline AsciiString::AsciiString(const AsciiString &that)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
}

typedef unsigned int UnsignedInt;

class ArchivedFileInfo;
typedef std::map<AsciiString, ArchivedFileInfo> ArchivedFileInfoMap;
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

class ArchivedFileInfo
{
public:
	ArchivedFileInfo();
	ArchivedFileInfo(const ArchivedFileInfo &that);

	AsciiString m_filename;
	AsciiString m_archiveFilename;
	UnsignedInt m_offset;
	UnsignedInt m_size;
};

template ArchivedFileInfo &ArchivedFileInfoMap::operator[](const AsciiString &key);
template AsciiString &ArchivedFileLocationMap::operator[](const AsciiString &key);
