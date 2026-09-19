// cl: /DNDEBUG /MD /EHsc
// NetCommandMsg debug description, RVA0x006747C0, complete298B.
// Matched constructor0x006735D0 installs vtableVA0x0111A20C; slot+0x0C
// points through ILT0x0002D204 to this body. Derived frame/ACK descriptions
// call this base explicitly and append their payload fields. The debug method
// name follows EA GeneralsMD NetCommandMsg.h and its override family.
// BFME adds the base frame/player/ID text instead of returning an empty string.
// The command-type helper is GetAsciiNetCommandType, not a packet decoder.
template <typename T> class StringBase {
    friend class AsciiString;
private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase &other);
    ~StringBase();
protected:
    void *m_data;
};
extern const char g_bfmeEmptyAscii[];
class AsciiString : private StringBase<char> {
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *s) : StringBase<char>(s) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    const char *str() const { return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii; }
    void __cdecl format(AsciiString fmt, ...);
};
enum NetCommandType { NETCOMMANDTYPE_FRAMEINFO = 3 };
bool DoesCommandRequireACommandID(NetCommandType);
AsciiString GetAsciiNetCommandType(NetCommandType);
class NetCommandMsg {
public:
    virtual ~NetCommandMsg();
    virtual int getSortNumber();
    virtual bool unknownSlot08();
    virtual AsciiString getContentsAsAsciiString();
    unsigned timestamp;
    unsigned frame;
    unsigned player;
    unsigned short id;
    NetCommandType type;
    int references;
};
// NetCommandMsg vtable 0x0111A20C slot 2 reaches the 3-byte retail body at 0x006627A0.
bool NetCommandMsg::unknownSlot08()
{
    return false;
}

AsciiString NetCommandMsg::getContentsAsAsciiString()
{
    AsciiString result;
    if (DoesCommandRequireACommandID(type))
        result.format("%s, frame=%d, player=%d, id=%d", GetAsciiNetCommandType(type).str(), frame, player, id);
    else
        result.format("%s, frame=%d, player=%d", GetAsciiNetCommandType(type).str(), frame, player);
    return result;
}
