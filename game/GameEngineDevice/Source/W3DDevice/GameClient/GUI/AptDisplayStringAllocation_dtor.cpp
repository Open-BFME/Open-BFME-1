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

// Retail's WindowManager global at 0x012F19E8, under the one linked-build
// spelling.
extern WindowManager *g_rva012F19E8WindowManager;

// Retail calls both of these through incremental-link thunks at 0x00005380
// and 0x00023362, so the thunks are called through a member-function-pointer
// union rather than a stand-in name and a linker alias directive.
extern void j_00005380();
extern void j_00023362();

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
    typedef UnicodeString ( Rva00788290Allocation::*GetTextFn )();
    typedef void ( WindowManager::*BindAptTextFn )( const AsciiString &, const UnicodeString &, class AptTextListener * );

    if ( !m_name.isEmpty() )
    {
        union { void (*fn)(); GetTextFn call; } getText = { j_00005380 };
        union { void (*fn)(); BindAptTextFn call; } bindAptText = { j_00023362 };

        ( g_rva012F19E8WindowManager->*bindAptText.call )( m_name, ( this->*getText.call )(), 0 );
    }

    if ( TheDisplayStringManager )
    {
        TheDisplayStringManager->freeDisplayString( m_displayString );
        m_displayString = 0;
    }
}
