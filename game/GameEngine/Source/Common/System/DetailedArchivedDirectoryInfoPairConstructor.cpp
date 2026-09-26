// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <map>

class AsciiString;

#include "string_base.h"

// Retail inlines AsciiString's forwarding constructor and calls its StringBase body.
class AsciiString : private StringBase<char>
{
public:
    __forceinline AsciiString(const AsciiString &src) : StringBase<char>(src) {}
    ~AsciiString();
};

class DetailedArchivedDirectoryInfo;
class ArchivedFileInfo
{
public:
    AsciiString m_filename;
    AsciiString m_archiveFilename;
    unsigned int m_offset;
    unsigned int m_size;
};

typedef std::map<AsciiString, DetailedArchivedDirectoryInfo> DetailedArchivedDirectoryInfoMap;
typedef std::map<AsciiString, ArchivedFileInfo> ArchivedFileInfoMap;

// The matched copy body at 0x009D0DB0 copies the name and maps at +0, +4 and +0x10.
// Keep its declaration local so shared directory-map inlining is unaffected.
class DetailedArchivedDirectoryInfo
{
public:
    DetailedArchivedDirectoryInfo(const DetailedArchivedDirectoryInfo &);
    AsciiString m_directoryName;
    DetailedArchivedDirectoryInfoMap m_directories;
    ArchivedFileInfoMap m_files;
};

// Retail 0x009D0EC0 constructs the key, then calls the Detailed copy body at this+4.
template std::pair<const AsciiString, DetailedArchivedDirectoryInfo>::pair(
    const AsciiString &, const DetailedArchivedDirectoryInfo &);
