// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled

#include "PreRTS.h"
#include <string.h>
#include <time.h>

#pragma intrinsic( strrchr )

// The retail body at 0x000A29E0 is StatsCollector::createFileName. The
// filename literals and the neighboring StatsCollector methods identify the
// body, while the local declarations keep the string calls at their retail
// WWLib addresses.
template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    StringBase() : m_data( 0 ) {}

private:
    StringBase( const StringBase<T> &other );
    StringBase( const T *text );
    void releaseBuffer();

public:
    void set( const T *text, int length );
    void removeLastChar();

    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T data[ 1 ];
    };

    Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
    AsciiString( const char *text ) : StringBase<char>( text ) {}
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

    void clear() { ((StringBase<char> *)this)->releaseBuffer(); }
    const char *str() const { return m_data ? m_data->data : ""; }
    const char *reverseFind( char character ) const
    {
        const char *start = m_data ? m_data->data : "";
        const char *end = start + (m_data ? m_data->length : 0);
        while( end != start )
        {
            --end;
            if( *end == character )
                return end;
        }
        return 0;
    }
    void removeLastChar() { ((StringBase<char> *)this)->removeLastChar(); }
    AsciiString &operator=( const char *text )
    {
        ((StringBase<char> *)this)->set( text, text ? strlen( text ) : 0 );
        return *this;
    }
    void __cdecl format( AsciiString format, ... );
};

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
    m_statsFileName.clear();

    char datestr[ 256 ] = "";
    time_t longTime;
    struct tm *curtime;
    time( &longTime );
    curtime = localtime( &longTime );
    strftime( datestr, 256, "_%b%d_%I%M%p", curtime );

    AsciiString name = TheWritableGlobalData->m_mapName;
    const char *fname = name.reverseFind( '\\' );
    if( fname )
        name = fname + 1;

    name.removeLastChar();
    name.removeLastChar();
    name.removeLastChar();
    name.removeLastChar();

    m_statsFileName.clear();
    m_statsFileName.format( "%s%s%s.txt", statsDir, name.str(), datestr );
}
