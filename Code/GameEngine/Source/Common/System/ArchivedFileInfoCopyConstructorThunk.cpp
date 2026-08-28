// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
class ArchivedFileInfo
{
public:
    AsciiString m_filename;
    AsciiString m_archiveFilename;
    UnsignedInt m_offset;
    UnsignedInt m_size;

    ArchivedFileInfo();
    ArchivedFileInfo(const ArchivedFileInfo &that);
};

// ??0ArchivedFileInfo@@QAE@ABV0@@Z
ArchivedFileInfo::ArchivedFileInfo(const ArchivedFileInfo &that) :
    m_filename(that.m_filename),
    m_archiveFilename(that.m_archiveFilename)
{
    m_offset = that.m_offset;
    m_size = that.m_size;
}

// ??0ArchivedFileInfo@@QAE@XZ
ArchivedFileInfo::ArchivedFileInfo()
{
    m_filename.clear();
    m_archiveFilename.clear();
    m_offset = 0;
    m_size = 0;
}
