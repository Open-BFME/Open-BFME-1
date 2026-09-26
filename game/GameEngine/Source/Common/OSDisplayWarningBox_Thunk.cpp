// cl: /DNDEBUG /MD /EHsc
// OSDisplayWarningBox at retail RVA 0x006BB040, 509 bytes.

typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

template <typename T> struct StringInlineData
{
    int m_refCount;
    int m_length;
    T m_text[1];
};

template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    StringBase() : m_data( 0 ) {}
    StringBase( const T *text );
    StringBase( const StringBase<T> &other );
    ~StringBase();
    void set( const StringBase<T> &other );

    StringInlineData<T> *m_data;
};

class UnicodeString;

extern const char Rva006A16B0Empty[];
extern const char g_bfmeEmptyUnicode[];

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
    ~AsciiString() {}

    const char *str() const
    {
        return m_data ? m_data->m_text : Rva006A16B0Empty;
    }

    void translate( const UnicodeString &other );
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString() : StringBase<WideChar>() {}
    UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
    UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
    ~UnicodeString() {}

    UnicodeString &operator=( const UnicodeString &other )
    {
        StringBase<WideChar>::set( *(const StringBase<WideChar> *)&other );
        return *this;
    }

    const WideChar *str() const
    {
        return m_data ? m_data->m_text : (const WideChar *)g_bfmeEmptyUnicode;
    }

    void __cdecl format( UnicodeString format, ... );
};

class GameTextInterface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual UnicodeString fetch( AsciiString label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;
extern const bool TheSystemIsUnicode;
static void RTSFlagsToOSFlags( UnsignedInt buttonFlags, UnsignedInt otherFlags,
    UnsignedInt &outWindowsFlags )
{
    outWindowsFlags = 0;
    if ( buttonFlags & 2 )
        outWindowsFlags |= 1;
    if ( buttonFlags & 1 )
        outWindowsFlags |= 0x1000;
    if ( otherFlags & 4 )
        outWindowsFlags |= 0x2000;
    if ( otherFlags & 8 )
        outWindowsFlags |= 0x30;
    if ( otherFlags & 0x10 )
        outWindowsFlags |= 0x40;
    if ( otherFlags & 0x11 )
        outWindowsFlags |= 0x10;
    if ( otherFlags & 0x12 )
        outWindowsFlags |= 0x10;
}
extern void *Rva0048CD50WindowHandle;

extern "C" __declspec( dllimport ) int __stdcall MessageBoxW(
    void *window, const WideChar *message, const WideChar *caption, UnsignedInt flags );
extern "C" __declspec( dllimport ) int __stdcall MessageBoxA(
    void *window, const char *message, const char *caption, UnsignedInt flags );
extern "C" __declspec( dllimport ) int __stdcall SetWindowPos(
    void *window, int insertAfter, int x, int y, int width, int height, UnsignedInt flags );

enum OSDisplayButtonType
{
    OSDBT_OK = 1,
    OSDBT_CANCEL = 2,
    OSDBT_ERROR = 0x80000000
};

// ?OSDisplayWarningBox@@YA?AW4OSDisplayButtonType@@VAsciiString@@0II@Z
OSDisplayButtonType OSDisplayWarningBox( AsciiString p, AsciiString m,
    UnsignedInt buttonFlags, UnsignedInt otherFlags )
{
    if ( TheGameText == 0 )
        return OSDBT_ERROR;

    UnicodeString promptStr = TheGameText->fetch( p );
    UnicodeString mesgStr = TheGameText->fetch( m );

    UnsignedInt windowsOptionsFlags = 0;
    RTSFlagsToOSFlags( buttonFlags, otherFlags, windowsOptionsFlags );

    int returnResult = 0;
    if ( TheSystemIsUnicode )
    {
        returnResult = MessageBoxW( 0, mesgStr.str(), promptStr.str(), windowsOptionsFlags );
    }
    else
    {
        AsciiString promptA;
        AsciiString mesgA;
        promptA.translate( promptStr );
        mesgA.translate( mesgStr );
        SetWindowPos( Rva0048CD50WindowHandle, -2, 0, 0, 0, 0, 3 );
        returnResult = MessageBoxA( 0, mesgA.str(), promptA.str(), windowsOptionsFlags );
    }

    if ( returnResult == 1 )
        return OSDBT_OK;
    return OSDBT_CANCEL;
}
