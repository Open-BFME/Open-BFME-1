// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /Ireference/shims/win32localfilesystem_wide /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "Common/GameMemory.h"
#include "PreRTS.h"
#include "Common/AsciiString.h"
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

typedef std::map<AsciiString, DetailedArchivedDirectoryInfo> DetailedArchivedDirectoryInfoMap;
typedef std::map<AsciiString, ArchivedFileInfo> ArchivedFileInfoMap;

class DetailedArchivedDirectoryInfo
{
public:
	void clear();

	AsciiString m_directoryName;
	DetailedArchivedDirectoryInfoMap m_directories;
	ArchivedFileInfoMap m_files;
};

void DetailedArchivedDirectoryInfo::clear()
{
	m_directoryName.clear();
	m_directories.clear();
	m_files.clear();
}
