// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// OnlineShell screen-table dispatch, retail 0x0055D030 (225 bytes).
// The shell closes its current screen, looks up the requested APT name in
// the paired name/factory table, constructs the selected screen, and records
// both its filename and its owning reference.

#include <cstring>
#include <vector>

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    StringBase( const T *text );
    StringBase( const StringBase<T> &other );
    ~StringBase();

    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString( const char *text ) : StringBase<char>( text ) {}
    AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
    ~AsciiString() {}

    AsciiString &operator=( const char *text );
};

class _bfme_AptGameWindow
{
public:
    virtual ~_bfme_AptGameWindow();

private:
    unsigned char m_unmodelled[ 0x254 ];
};

class BfmeAptScreenRef
{
public:
    virtual ~BfmeAptScreenRef();
    virtual void close();

private:
    unsigned char m_unmodelled[ 0x34 ];

public:
    const char *m_fileName;
};

struct Gen_t_0055cfc0_m4pod
{
    BfmeAptScreenRef *m_value;
};

typedef BfmeAptScreenRef *(*BfmeAptScreenFactory)( void *context );

struct Gen_t_012b7c58_entry
{
    const char *m_name;
    BfmeAptScreenFactory m_factory;
};

extern Gen_t_012b7c58_entry g_012B7C58[];

class BfmeAptScreenOnlineShell : public _bfme_AptGameWindow
{
public:
    void openScreen( const char *name );

private:
    int m_258;
    std::vector<Gen_t_0055cfc0_m4pod> m_refs;
    AsciiString m_name;
    Gen_t_0055cfc0_m4pod m_current;
    AsciiString m_fileName;
    void *m_274;
    void *m_278;
    void *m_27c;
};

void BfmeAptScreenOnlineShell::openScreen( const char *name )
{
    if( m_current.m_value )
    {
        m_current.m_value->close();
        m_current.m_value = 0;
    }

    const char *screenName =
        g_012B7C58[ 0 ].m_name;
    unsigned int index = 0;
    if( screenName == 0 )
        return;

    for( ; screenName != 0; ++index )
    {
        if( strcmp( screenName, name ) == 0 )
        {
            m_current.m_value = g_012B7C58[ index ].m_factory( this );
            if( m_current.m_value == 0 )
                return;

            m_current.m_value->m_fileName = screenName;
            m_fileName = screenName;
            m_refs.push_back( m_current );
            return;
        }

        screenName = g_012B7C58[ index + 1 ].m_name;
    }
}
