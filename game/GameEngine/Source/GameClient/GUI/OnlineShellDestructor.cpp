// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// BfmeAptScreenOnlineShell destructor, retail 0x0055CB50 (297 bytes).
// The paired constructor installs the two OnlineShell vtable views and owns
// the screen-reference pointer vector at +0x25c.

#include <new>
#include <vector>

// stlport

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
};

extern int g_Va012F4988;
extern int g_Va012F4ACC;
extern void HideInGameChat();
extern void j_0003aae9();

// The two OnlineShell vftable views this destructor restores.  The retail
// names are C++-mangled vftable symbols that cannot be declared directly, so
// a plain extern stands in for each and /alternatename binds it to the exact
// ??_7 name dir32_addresses.csv records for that address.
extern "C" const void *bfmeVftOnlineShellScreenBase[];
extern "C" const void *bfmeVftOnlineShellS4Owner[];
#pragma comment(linker, "/alternatename:_bfmeVftOnlineShellScreenBase=??_7BfmeAptScreenOnlineShell@@6BBfmeAptScreenBase@@@")
#pragma comment(linker, "/alternatename:_bfmeVftOnlineShellS4Owner=??_7BfmeAptScreenOnlineShell@@6BS4Owner@@@")

class BfmeAptScreenOnlineShell : public _bfme_AptGameWindow
{
public:
    virtual ~BfmeAptScreenOnlineShell();

private:
    int m_258;
    std::vector<BfmeAptScreenRef *> m_refs;
    AsciiString m_name;
    BfmeAptScreenRef *m_current;
    AsciiString m_fileName;
    void *m_274;
    void *m_278;
    void *m_27c;
};

BfmeAptScreenOnlineShell::~BfmeAptScreenOnlineShell()
{
    *(const void ***)( (char *)this ) = bfmeVftOnlineShellScreenBase;
    *(const void ***)( (char *)this + 0x218 ) = bfmeVftOnlineShellS4Owner;

    if( g_Va012F4988 )
        HideInGameChat();

    for( BfmeAptScreenRef **it = m_refs.begin(); it != m_refs.end(); ++it )
    {
        BfmeAptScreenRef *item = *it;
        if( item )
            delete item;
    }

    m_refs.clear();

    if( (void *)g_Va012F4ACC == this )
    {
        j_0003aae9();
        g_Va012F4ACC = 0;
    }
}
