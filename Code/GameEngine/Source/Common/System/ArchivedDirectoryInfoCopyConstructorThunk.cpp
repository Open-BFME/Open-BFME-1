// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

// SHIM: the copy constructor is declared here rather than in
// reference/shims/archivefilesystem_nosubsystem/Common/ArchiveFileSystem.h on
// purpose. Declaring it in the shared header suppresses the implicit default
// constructor that the directory maps need, which stops ArchiveFileSystem.cpp
// compiling at all, and it also stops MSVC inlining pair's copy constructor
// there, which breaks that TU's _Construct row. Spelling the class locally
// keeps both effects inside this translation unit.
#define __ARCHIVEFILESYSTEM_H_
#include "Common/SubsystemInterface.h"
#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "Common/STLTypedefs.h"

class ArchivedDirectoryInfo;
typedef std::map<AsciiString, ArchivedDirectoryInfo> ArchivedDirectoryInfoMap;
typedef std::map<AsciiString, AsciiString> ArchivedFileLocationMap;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
class ArchivedDirectoryInfo
{
public:
	ArchivedDirectoryInfo(const ArchivedDirectoryInfo &);
	AsciiString								m_directoryName;
	ArchivedDirectoryInfoMap	m_directories;
	ArchivedFileLocationMap		m_files;
};


ArchivedDirectoryInfo::ArchivedDirectoryInfo(const ArchivedDirectoryInfo &that) :
	m_directoryName(that.m_directoryName),
	m_directories(that.m_directories),
	m_files(that.m_files)
{
}
