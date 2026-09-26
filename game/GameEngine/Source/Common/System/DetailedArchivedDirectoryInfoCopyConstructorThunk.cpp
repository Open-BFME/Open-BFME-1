// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/archivefilesystem_nosubsystem /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

// SHIM: the copy constructor is declared here rather than in
// inputs/reference/shims/archivefilesystem_nosubsystem/Common/ArchiveFileSystem.h on
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
class ArchivedFileInfo
{
public:
	AsciiString m_filename;
	AsciiString m_archiveFilename;
	UnsignedInt m_offset;
	UnsignedInt m_size;
};

typedef std::map<AsciiString, DetailedArchivedDirectoryInfo> DetailedArchivedDirectoryInfoMap;
typedef std::map<AsciiString, ArchivedFileInfo> ArchivedFileInfoMap;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
class DetailedArchivedDirectoryInfo
{
public:
	DetailedArchivedDirectoryInfo(const DetailedArchivedDirectoryInfo &);
	AsciiString												m_directoryName;
	DetailedArchivedDirectoryInfoMap	m_directories;
	ArchivedFileInfoMap								m_files;
};


DetailedArchivedDirectoryInfo::DetailedArchivedDirectoryInfo(const DetailedArchivedDirectoryInfo &that) :
	m_directoryName(that.m_directoryName),
	m_directories(that.m_directories),
	m_files(that.m_files)
{
}
