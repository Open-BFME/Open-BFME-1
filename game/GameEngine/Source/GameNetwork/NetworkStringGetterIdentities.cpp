// cl: /DNDEBUG /MD /EHsc
// These 32-byte accessors were previously claimed as LANAPI::GetMyName.
// Four neutral owners use StringBase<char>'s sharing constructor at887B60.
// DownloadManager and the real LANAPI getter685660 use wide constructor888400.
// Unknown class owners remain address scoped; no shared Unicode pin is changed.
template<class T> class StringBase {
    friend class BfmeSharedString;
    friend class UnicodeString;
private:
    StringBase(const StringBase<T>&);
    ~StringBase();
    void *data;
};
class BfmeSharedString : private StringBase<char> {
public:
    BfmeSharedString(const BfmeSharedString& other) : StringBase<char>(other) {}
    ~BfmeSharedString() {}
};

// The sole caller4C79D5 is DownloadManagerMunkee::OnError, which passes this
// return object directly as MessageBoxOk's text beside the GameText title.
// The released caller names getErrorString with a UnicodeString return and
// the retail getter calls the wide StringBase sharing constructor888400.
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString(const UnicodeString& other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
};
class DownloadManager {
public:
    UnicodeString getErrorString();
private:
    char preceding[0x10];
    UnicodeString m_errorString;
};
UnicodeString DownloadManager::getErrorString() { return m_errorString; }

class Rva00361960 {
public: BfmeSharedString copyString();
private: char preceding[0x10]; BfmeSharedString m_string;
};
class Rva00489B30 {
public: BfmeSharedString copyString();
private: char preceding[0x10]; BfmeSharedString m_string;
};
class Rva006E2280 {
public: BfmeSharedString copyString();
private: char preceding[0x10]; BfmeSharedString m_string;
};
class Rva000AF1F0 {
public: BfmeSharedString copyString();
private: char preceding[0x10]; BfmeSharedString m_string;
};
BfmeSharedString Rva00361960::copyString() { return m_string; }
BfmeSharedString Rva00489B30::copyString() { return m_string; }
BfmeSharedString Rva006E2280::copyString() { return m_string; }
BfmeSharedString Rva000AF1F0::copyString() { return m_string; }
