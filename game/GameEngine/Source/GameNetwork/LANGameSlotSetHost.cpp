// cl: /DNDEBUG /MD /EHsc
// LANGameSlot::setHost(AsciiString), RVA 00685420, 75 bytes.
// RequestGameCreate687E90 calls ILT241BD at688057 with the ASCII LANAPI+18
// host string, just after setLogin at+14. The established 68-byte LANGameSlot
// layout embeds its LANPlayer at+44; its Unicode host field is therefore+4C.
// The callee translates from ASCII (8891F0), then destroys a char StringBase
// argument (887940). The old User::setName(UnicodeString) claim had both the
// owner and input type wrong. The existing setHost body pin has this identity.
template<class T> class StringBase {
    friend class AsciiString;
private:
    StringBase(const StringBase<T>&);
    ~StringBase();
    void *data;
};
class AsciiString : private StringBase<char> {
public:
    AsciiString(const AsciiString& other) : StringBase<char>(other) {}
    ~AsciiString() {}
};
class UnicodeString {
public:
    void translate(const AsciiString&);
private:
    void *data;
};
class LANGameSlot {
public:
    void setHost(AsciiString name);
private:
    char preceding[0x4C];
    UnicodeString m_host;
};
void LANGameSlot::setHost(AsciiString name)
{
    m_host.translate(name);
}
