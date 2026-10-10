// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled

#include "PreRTS.h"
#include <string.h>
#include <time.h>

#pragma intrinsic( strrchr )

// The retail body at 0x000A29E0 is StatsCollector::createFileName. The
// filename literals and the neighboring StatsCollector methods identify the
// body, while the local declarations keep the string calls at their retail
// WWLib addresses.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template<> inline const char *StringBase<char>::reverseFind(char c) const
{
    const char *start = m_data ? &m_data->data[0] : (const char *)"";
    const char *p = start + (m_data ? m_data->length : 0);
    while (p != start) {
        --p;
        if (*p == c) return p;
    }
    return 0;
}

inline AsciiString &AsciiString::operator=(const char *str)
{
    ((StringBase<char> *)this)->set(str, str ? strlen(str) : 0);
    return *this;
}

static char statsDir[ 255 ] = "Stats\\";

class StatsCollector
{
private:
    void createFileName();

    AsciiString m_statsFileName;
};

class GlobalData
{
public:
    unsigned char m_unmodelled00[ 8 ];
    AsciiString m_mapName;
};

extern GlobalData *TheWritableGlobalData;

void StatsCollector::createFileName()
{
    m_statsFileName.StringBase<char>::clear();

    char datestr[ 256 ] = "";
    time_t longTime;
    struct tm *curtime;
    time( &longTime );
    curtime = localtime( &longTime );
    strftime( datestr, 256, "_%b%d_%I%M%p", curtime );

    AsciiString name = TheWritableGlobalData->m_mapName;
    const char *fname = name.StringBase<char>::reverseFind( '\\' );
    if( fname )
        name = fname + 1;

    name.StringBase<char>::removeLastChar();
    name.StringBase<char>::removeLastChar();
    name.StringBase<char>::removeLastChar();
    name.StringBase<char>::removeLastChar();

    m_statsFileName.StringBase<char>::clear();
    m_statsFileName.format( "%s%s%s.txt", statsDir, name.str(), datestr );
}
