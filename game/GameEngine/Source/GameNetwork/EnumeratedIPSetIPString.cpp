// cl: /DNDEBUG /MD /EHsc
// EnumeratedIP::setIPstring, RVA 00624C10, 72 bytes. Both callers are in
// IPEnumeration::getAddresses at 00624C80: 00624D56 sets the loopback text,
// followed by IP 0100007F at +4 and next pointer at +8; 00624E18 assigns a
// formatted address before storing its numeric address at +4. The released
// IPEnumeration source names this accessor. It is not LANPlayer::setName.
template<class T> class StringBase {
    friend class AsciiString;
private:
    StringBase(const StringBase<T>&);
    ~StringBase();
    void set(const StringBase<T>&);
    void *data;
};
class AsciiString : private StringBase<char> {
public:
    AsciiString(const AsciiString& other) : StringBase<char>(other) {}
    ~AsciiString() {}
    AsciiString& operator=(const AsciiString& other) {
        StringBase<char>::set(other);
        return *this;
    }
};
class EnumeratedIP {
public:
    void setIPstring(AsciiString name);
private:
    AsciiString m_IPstring;
    unsigned m_IP;
    EnumeratedIP *m_next;
};
void EnumeratedIP::setIPstring(AsciiString name)
{
    m_IPstring = name;
}
