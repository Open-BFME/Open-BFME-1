// ??A?$map@VAsciiString@@VArchivedFileInfo@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@VArchivedFileInfo@@@_STL@@@4@@_STL@@QAEAAVArchivedFileInfo@@ABVAsciiString@@@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// Open-BFME7: fuzzy twin of ArchivedDirectoryInfoMapOperator.cpp
// (0x009CAB10, 233 B): std::map<AsciiString, T>::operator[] with
// T = ArchivedFileInfo instead of ArchivedDirectoryInfo, retail 0x009D0C50,
// 236 bytes. ArchivedFileInfo's already-matched ctor/copy-ctor
// (ArchivedFileInfoCopyConstructorThunk.cpp) are the identity evidence: its
// default ctor call folds (ICF) with ??0GameSpyGroupRoom@@QAE@ABV0@@Z at
// 0x00887B60 in this body, same as the twin's own AsciiString-clear fold.

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

#include "Common/GameMemory.h"
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "Common/STLTypedefs.h"

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
