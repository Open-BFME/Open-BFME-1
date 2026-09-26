// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <utility>
#include <memory>

class AsciiString;

#include "string_base.h"

// Retail's pair copy inlines this forwarder and calls the narrow StringBase body.
class AsciiString : private StringBase<char>
{
public:
    __forceinline AsciiString(const AsciiString &src) : StringBase<char>(src) {}
    ~AsciiString();
};

// The matched copy at 0x009CEBF0 copies strings at +0/+4 and uints at +8/+0xC.
class ArchivedFileInfo
{
public:
    ArchivedFileInfo(const ArchivedFileInfo &);
    AsciiString m_filename;
    AsciiString m_archiveFilename;
    unsigned int m_offset;
    unsigned int m_size;
};

typedef std::pair<const AsciiString, ArchivedFileInfo> ArchivedFileInfoPair;

// Keep the pair copy out of the helper, as retail 0x009CF3C0 calls 0x009CF180.
template void _STL::_Construct(ArchivedFileInfoPair *, const ArchivedFileInfoPair &);
