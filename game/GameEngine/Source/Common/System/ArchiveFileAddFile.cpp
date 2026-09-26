// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/archivefilesystem_nosubsystem /Iinputs/reference/shims/asciistring8outofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
