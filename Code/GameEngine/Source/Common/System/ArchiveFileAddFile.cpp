// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring8outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "Common/GameMemory.h"
#include "PreRTS.h"
#include "Common/ArchiveFile.h"
#include "Common/ArchiveFileSystem.h"
#include "Common/File.h"

class ArchiveToken : public AsciiString
{
public:
	int getLength() const
	{
		const unsigned int data = *(const unsigned int *)this;
		return data ? *(const unsigned short *)(data + 4) : 0;
	}
};

void ArchiveFile::addFile(const AsciiString &path, const ArchivedFileInfo *fileInfo)
{
	AsciiString temp;
	temp = path;
	temp.toLower();
	ArchiveToken token;
	AsciiString debugpath;

	DetailedArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	temp.nextToken(&token, "\\/");

	while (token.getLength() > 0) {
		if (dirInfo->m_directories.find(token) == dirInfo->m_directories.end()) {
			dirInfo->m_directories[token].clear();
			dirInfo->m_directories[token].m_directoryName = token;
		}

		dirInfo = &(dirInfo->m_directories[token]);
		temp.nextToken(&token, "\\/");
	}

	dirInfo->m_files[fileInfo->m_filename] = *fileInfo;
}
