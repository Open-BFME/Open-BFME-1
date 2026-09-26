// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// GameTextManager::fetch(AsciiString, bool*) at RVA 0x00436F90.
// The constructor at 0x00438350 installs vtable 0x010F39F0: +0x24 routes
// through ILT 0x000449AE to this overload, which forwards to char-fetch +0x28.
// MSVC orders the overload slots in reverse declaration order below.
//
// Retail's private StringBase payload starts after an eight-byte header and
// its nontrivial by-value string lifetime requires the real base destructor.
// The previous 47-byte claim cut inside the old source's wrong add eax,4;
// the complete function is 114 bytes through ret12 at RVA 0x00436FFF.
// This isolated ABI view leaves the other GameText.cpp bodies unchanged.

template<class T> struct StringData { int ref_count; unsigned short length, capacity; T text[1]; };
template<class T> class StringBase {
    friend class AsciiString;
    friend class UnicodeString;
private:
    StringData<T> *data;
    StringBase():data(0) {}
    StringBase(const T*);
    StringBase(const StringBase&);
    ~StringBase();
    void set(const StringBase&);
};
class AsciiString : private StringBase<char> {
public:
    AsciiString() {}
    AsciiString(const char *p):StringBase<char>(p) {}
    AsciiString(const AsciiString &p):StringBase<char>(p) {}
    ~AsciiString() {}
    const char *str() const { return data ? data->text : ""; }
    void __cdecl format(AsciiString, ...);
    AsciiString &operator=(const AsciiString &other) { set(other); return *this; }
};
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString() {}
    UnicodeString(const unsigned short *p):StringBase<unsigned short>(p) {}
    UnicodeString(const UnicodeString &p):StringBase<unsigned short>(p) {}
    ~UnicodeString() {}
    const unsigned short *str() const { return data ? data->text : (const unsigned short *)L""; }
    void __cdecl format(UnicodeString, ...);
    void translate(const AsciiString&);
    UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
};

class GameTextManager {
public:
 virtual ~GameTextManager();
 virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c(); virtual void slot20();
 virtual UnicodeString fetch(const char *label, bool *exists);
 virtual UnicodeString fetch(AsciiString label, bool *exists);
};
UnicodeString GameTextManager::fetch(AsciiString label,bool *exists) { return fetch(label.str(),exists); }
