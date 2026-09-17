// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS
// Rva00788290Allocation destructor at retail 0x007859D0.
// The constructor caller at 0x00788290 allocates this 0x30-byte object and
// calls Rva00788290Allocation::bfmeConstruct00788290 through ILT 0x0003097C.

template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    StringBase() : m_data( 0 ) {}
    StringBase( const StringBase<T> &other );
    ~StringBase();

    void *m_data;
};

class AsciiString : private StringBase<char>
{
    friend class Rva00788290Allocation;

public:
    AsciiString() : StringBase<char>() {}
    AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
    ~AsciiString() {}

private:
    bool isEmpty() const
    {
        return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
    }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
    ~UnicodeString() {}
};

class DisplayString;

class DisplayStringManager
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual DisplayString *newDisplayString() = 0;
    virtual void freeDisplayString( DisplayString *string ) = 0;
};

extern DisplayStringManager *TheDisplayStringManager;

class WindowManager
{
public:
    void bfme_bindAptText( const AsciiString &name, const UnicodeString &text, class AptTextListener *listener );
};

extern WindowManager *g_theWindowManager;

#pragma comment(linker, "/alternatename:?getText@Rva00788290Allocation@@QAE?AVUnicodeString@@XZ=?j_00005380@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfme_bindAptText@WindowManager@@QAEXABVAsciiString@@ABVUnicodeString@@PAVAptTextListener@@@Z=?j_00023362@@YAXXZ")

class Rva00788290Base
{
public:
    virtual ~Rva00788290Base() {}
};

class Rva00788290Allocation : public Rva00788290Base
{
public:
    virtual ~Rva00788290Allocation();
    UnicodeString getText();

private:
    AsciiString m_name;
    DisplayString *m_displayString;
    char m_tail[0x24];
};

Rva00788290Allocation::~Rva00788290Allocation()
{
    if ( !m_name.isEmpty() )
    {
        g_theWindowManager->bfme_bindAptText( m_name, getText(), 0 );
    }

    if ( TheDisplayStringManager )
    {
        TheDisplayStringManager->freeDisplayString( m_displayString );
        m_displayString = 0;
    }
}
