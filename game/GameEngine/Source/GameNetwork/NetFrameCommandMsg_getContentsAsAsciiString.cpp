// cl: /DNDEBUG /MD /EHsc
// NetFrameCommandMsg debug description, RVA0x00674940, complete195B.
// Constructor installs vtableVA0x0111A220; slot+0x0C is ILT0x0004B02E
// to this body. Calls the NetCommandMsg base at0x00674982 through2D204,
// then appends logicFrame/clientFrame/totalCommands from payload1C/20/24.
// Original constant stringVA0x0111A620 independently confirms field meanings.
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
class NetFrameCommandMsg : public NetCommandMsg {
public:
 virtual AsciiString getContentsAsAsciiString();
 unsigned getFrame(){return logicFrame;}
 unsigned getClientFrame(){return clientFrame;}
 int getCommandCount(){return totalCommands;}
 unsigned logicFrame, clientFrame;
 int totalCommands;
};
AsciiString NetFrameCommandMsg::getContentsAsAsciiString()
{
 AsciiString result;
 result.format("%s, logicFrame=%d, clientFrame=%d, totalCommands=%d", NetCommandMsg::getContentsAsAsciiString().str(), getFrame(), getClientFrame(), getCommandCount());
 return result;
}
