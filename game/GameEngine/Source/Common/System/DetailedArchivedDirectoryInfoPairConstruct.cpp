// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <map>
#include <memory>

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

typedef std::pair<const AsciiString, DetailedArchivedDirectoryInfo> DetailedArchivedDirectoryInfoPair;

// Retail inlines this STLport pair copy into placement construction.
template <>
__forceinline std::pair<const AsciiString, DetailedArchivedDirectoryInfo>::pair(
    const DetailedArchivedDirectoryInfoPair &src)
    : first(src.first), second(src.second)
{
}

// Retail 0x009CE9B0 copies the pair into uninitialized node storage.
template void _STL::_Construct(DetailedArchivedDirectoryInfoPair *, const DetailedArchivedDirectoryInfoPair &);
