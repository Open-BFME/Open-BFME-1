// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/STLTypedefs.h"

typedef unsigned int UnsignedInt;

// The callers' local declarations and both object signatures identify this as
// a struct in the BFME translation unit (PBU in the decorated name). The
// shipped ZH header says class, which would emit PBV and is a different symbol.
struct ArchivedFileInfo
{
	AsciiString m_filename;
	AsciiString m_archiveFilename;
	UnsignedInt m_offset;
	UnsignedInt m_size;
};

class DetailedArchivedDirectoryInfo;
typedef std::map<AsciiString, DetailedArchivedDirectoryInfo> DetailedArchivedDirectoryInfoMap;
typedef std::map<AsciiString, ArchivedFileInfo> ArchivedFileInfoMap;

class DetailedArchivedDirectoryInfo
{
public:
	AsciiString m_directoryName;
	DetailedArchivedDirectoryInfoMap m_directories;
	ArchivedFileInfoMap m_files;
};

class ArchiveFile
{
public:
	virtual ~ArchiveFile();

protected:
	const ArchivedFileInfo *getArchivedFileInfo(const AsciiString &filename) const;

	void *m_file;
	DetailedArchivedDirectoryInfo m_rootDirectory;
};

// BFME's find(char) scans the StringBase buffer directly. The ZH AsciiString
// wrapper delegates this operation, which introduces a call and loses the
// target's bounded scan shape.
static inline const char *bfmeFind(const AsciiString &s, char c)
{
	const char *d = *(const char * const *)&s;
	const char *p = d ? d + 8 : "";
	const char *end = p + (d ? *(const unsigned short *)(d + 4) : 0);

	for (; p != end; ++p) {
		if (*p == c) {
			return p;
		}
	}
	return NULL;
}

// ?getArchivedFileInfo@ArchiveFile@@IBEPBUArchivedFileInfo@@ABVAsciiString@@@Z
const ArchivedFileInfo *ArchiveFile::getArchivedFileInfo(const AsciiString& filename) const
{
	AsciiString path;
	path = filename;
	path.toLower();
	AsciiString token;

	const DetailedArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	path.nextToken(&token, "\\/");

	while ((bfmeFind(token, '.') == NULL) || (bfmeFind(path, '.') != NULL)) {

		DetailedArchivedDirectoryInfoMap::const_iterator it = dirInfo->m_directories.find(token);
		if (it != dirInfo->m_directories.end())
		{
			dirInfo = &it->second;
		}
		else
		{
			return NULL;
		}

		path.nextToken(&token, "\\/");
	}

	ArchivedFileInfoMap::const_iterator it = dirInfo->m_files.find(token);
	if (it != dirInfo->m_files.end())
	{
		return &it->second;
	}
	else
	{
		return NULL;
	}
}
