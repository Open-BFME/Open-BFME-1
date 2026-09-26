// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

typedef int Int;
typedef bool Bool;

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// The BFME preference body uses the WWLib StringBase ABI for both string
// members.  The visible forwarding constructors are important: retail calls
// StringBase's copy bodies directly when LadderPref is copied, while str() is
// inlined at the call site.
template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &source);
    StringBase(const T *source);
    void set(const StringBase<T> &source);
    void releaseBuffer();

protected:
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    AsciiString(const char *source) : StringBase<char>(source) {}
    ~AsciiString() { releaseBuffer(); }

    const char *str() const
    {
        return m_data ? &m_data->data[0] : (const char *)0x0107388B;
    }

    void __cdecl format(AsciiString format, ...);
    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(
            *(const StringBase<char> *)&source);
        return *this;
    }
};

class UnicodeString : private StringBase<wchar_t>
{
public:
    UnicodeString() : StringBase<wchar_t>() {}
    UnicodeString(const UnicodeString &source)
        : StringBase<wchar_t>(source)
    {
    }
    ~UnicodeString() { releaseBuffer(); }

    const wchar_t *str() const
    {
        return m_data ? &m_data->data[0] : (const wchar_t *)0x0107388C;
    }
};

extern AsciiString AsciiStringToQuotedPrintable(AsciiString original);
extern AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);

bool operator<(const AsciiString &left, const AsciiString &right);

struct LadderPref
{
    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;
};

typedef std::map<long, LadderPref> LadderPrefMap;

enum NameKeyType
{
    NAMEKEY_INVALID = 0
};

typedef std::map<NameKeyType, float> UserPreferenceClearMap;

class UserPreferenceMap : public std::map<AsciiString, AsciiString>
{
public:
    void clear(void)
    {
        ((UserPreferenceClearMap *)this)->clear();
    }
};

class UserPreferences : public UserPreferenceMap
{
public:
    virtual Bool write(void);

private:
    UnicodeString m_filename;
};

class LadderPreferences : public UserPreferences
{
public:
    virtual Bool write(void);

private:
    LadderPrefMap m_ladders;
};

// ?write@LadderPreferences@@UAE_NXZ
Bool LadderPreferences::write(void)
{
    clear();
    LadderPrefMap::iterator lpIt;

    static const Int MAX_LADDERS = 5;
    Int count;
    for (lpIt = m_ladders.begin(), count = 0;
         lpIt != m_ladders.end() && count < MAX_LADDERS;
         ++lpIt, ++count)
    {
        LadderPref p = lpIt->second;
        AsciiString ladName;
        AsciiString ladData;
        ladName.format("%s:%d", AsciiStringToQuotedPrintable(p.address).str(), p.port);
        ladData.format("%s:%d", UnicodeStringToQuotedPrintable(p.name).str(), p.lastPlayDate);
        (*this)[ladName] = ladData;
    }

    return UserPreferences::write();
}
