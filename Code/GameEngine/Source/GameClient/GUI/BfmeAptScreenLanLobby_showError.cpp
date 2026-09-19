// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The LanLobby secondary vtable uses slot 2 for this chat/error callback.
// The vtable at 0x01105A28 routes slot 2 through thunk 0x000089E5 to 0x00516D80.
// The neighboring LanLobby slots and the matching Skirmish callback name show
// that this method is BfmeAptScreenLanLobby::showError.
// Retail 0x00516D80 sends normal and emote text through OnChat, and sends
// system text through RequestChat.

typedef unsigned short wchar_t;

template <typename T> struct StringData
{
    int m_refCount;
    int m_length;
    T m_text[1];
};

template <typename T> class StringBase
{
    friend class UnicodeString;

private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other) throw();
    ~StringBase();

    StringData<T> *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const wchar_t *text) : StringBase<unsigned short>(text) {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
};

class LANAPIInterface
{
public:
    enum ChatType
    {
        LANCHAT_NORMAL = 0,
        LANCHAT_EMOTE = 1,
        LANCHAT_SYSTEM = 2
    };
};

class LANAPI
{
public:
#define LANAPI_SLOT(N) virtual void slot##N();
    LANAPI_SLOT(00) LANAPI_SLOT(01) LANAPI_SLOT(02) LANAPI_SLOT(03)
    LANAPI_SLOT(04) LANAPI_SLOT(05) LANAPI_SLOT(06) LANAPI_SLOT(07)
    LANAPI_SLOT(08) LANAPI_SLOT(09) LANAPI_SLOT(10) LANAPI_SLOT(11)
    LANAPI_SLOT(12) LANAPI_SLOT(13) LANAPI_SLOT(14) LANAPI_SLOT(15)
#undef LANAPI_SLOT
    virtual void RequestChat(UnicodeString message,
        LANAPIInterface::ChatType format);
#define LANAPI_SLOT(N) virtual void slot##N();
    LANAPI_SLOT(17) LANAPI_SLOT(18) LANAPI_SLOT(19) LANAPI_SLOT(20)
    LANAPI_SLOT(21) LANAPI_SLOT(22) LANAPI_SLOT(23) LANAPI_SLOT(24)
    LANAPI_SLOT(25) LANAPI_SLOT(26) LANAPI_SLOT(27) LANAPI_SLOT(28)
    LANAPI_SLOT(29) LANAPI_SLOT(30) LANAPI_SLOT(31) LANAPI_SLOT(32)
    LANAPI_SLOT(33) LANAPI_SLOT(34)
    virtual void OnChat(UnicodeString player, unsigned int ip,
        UnicodeString message, LANAPIInterface::ChatType format);
    LANAPI_SLOT(36) LANAPI_SLOT(37) LANAPI_SLOT(38) LANAPI_SLOT(39)
    LANAPI_SLOT(40) LANAPI_SLOT(41) LANAPI_SLOT(42) LANAPI_SLOT(43)
    LANAPI_SLOT(44) LANAPI_SLOT(45) LANAPI_SLOT(46) LANAPI_SLOT(47)
    LANAPI_SLOT(48) LANAPI_SLOT(49) LANAPI_SLOT(50) LANAPI_SLOT(51)
    LANAPI_SLOT(52) LANAPI_SLOT(53) LANAPI_SLOT(54)
    virtual unsigned int GetLocalIP();
#undef LANAPI_SLOT
};

extern LANAPI *TheLAN;

class BfmeAptScreenLanLobby
{
public:
    void showError(const UnicodeString &message, int format);
};

// ?showError@BfmeAptScreenLanLobby@@QAEXABVUnicodeString@@H@Z
void BfmeAptScreenLanLobby::showError(const UnicodeString &message, int format)
{
    if (TheLAN == 0)
        return;

    switch (format)
    {
        case LANAPIInterface::LANCHAT_NORMAL:
        {
            TheLAN->OnChat(UnicodeString(L"SYSTEM"), TheLAN->GetLocalIP(), message,
                LANAPIInterface::LANCHAT_SYSTEM);
            break;
        }
        case LANAPIInterface::LANCHAT_EMOTE:
        {
            TheLAN->OnChat(UnicodeString(L"SYSTEM"), TheLAN->GetLocalIP(), message,
                LANAPIInterface::LANCHAT_SYSTEM);
            break;
        }
        case LANAPIInterface::LANCHAT_SYSTEM:
            TheLAN->RequestChat(message, LANAPIInterface::LANCHAT_SYSTEM);
            break;
        default:
            break;
    }
}
