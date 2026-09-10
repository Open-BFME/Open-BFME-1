// ?fetch@GameTextManager@@UAE?AVUnicodeString@@PBDPA_N@Z
// partial score=0.78 date=2026-09-10
// scratch only: BFME StringBase ABI view for GameTextManager::fetch.
// Retail target: 0x00437F60, 622 bytes.  Not a production source.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
// stlport

typedef int Int;
typedef bool Bool;
typedef char Char;
typedef unsigned short WideChar;
typedef int LanguageID;

#include <string.h>

#define NULL 0
#define TRUE true
#define FALSE false
#define NEW new
#define DEBUG_ASSERTCRASH(condition, message) ((void)0)

extern int __cdecl stricmp(const char *, const char *);

template <typename T> struct StringData
{
    int m_refCount;
    unsigned short m_length;
    unsigned short m_capacity;
    T m_text[1];
};

template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

protected:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();
    void set(const T *text, int length);
    void set(const StringBase<T> &other);

    StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}

    AsciiString &operator=(const char *text)
    {
        int length = text ? (int)strlen(text) : 0;
        ((StringBase<char> *)this)->set(text, length);
        return *this;
    }

    const char *str() const
    {
        return m_data ? m_data->m_text : "";
    }
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString() : StringBase<WideChar>() {}
    UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
    UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
    ~UnicodeString() {}

    void format(UnicodeString format, ...);

    UnicodeString &operator=(const UnicodeString &other)
    {
        ((StringBase<WideChar> *)this)->set(
            *(const StringBase<WideChar> *)&other);
        return *this;
    }

    const WideChar *str() const
    {
        return m_data ? m_data->m_text : 0;
    }

    bool operator==(const UnicodeString &other) const
    {
        const WideChar *left = str();
        const WideChar *right = other.str();
        unsigned int leftLength = m_data ? m_data->m_length : 0;
        unsigned int rightLength = other.m_data ? other.m_data->m_length : 0;
        unsigned int length = leftLength < rightLength ? leftLength : rightLength;
        while (length && *left == *right)
        {
            ++left;
            ++right;
            --length;
        }
        return length == 0 && leftLength == rightLength;
    }
};

struct StringInfo
{
    AsciiString label;
    UnicodeString text;
};

struct StringLookUp
{
    AsciiString *label;
    StringInfo *info;
};

inline bool operator<(const StringLookUp &left, const StringLookUp &right)
{
    return stricmp(left.label->str(), right.label->str()) < 0;
}

inline bool operator==(const StringLookUp &left, const StringLookUp &right)
{
    return stricmp(left.label->str(), right.label->str()) == 0;
}

template<class T> T *Binary_Search(T *A, int n, T const &target)
{
    const T *pointer = A;
    int stride = n;
    while (0 < stride)
    {
        int const pivot = stride / 2;
        T const * const tryptr = pointer + pivot;
        if (target < *tryptr)
        {
            stride = pivot;
        }
        else
        {
            if (*tryptr == target)
                return (T *)tryptr;
            pointer = tryptr + 1;
            stride -= pivot + 1;
        }
    }
    return NULL;
}

struct NoString
{
    NoString *next;
    UnicodeString text;
};

class GameTextInterface
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;

protected:
    int m_subsystemBase;
};

class GameTextManager : public GameTextInterface
{
public:
    virtual UnicodeString fetch(const Char *label, Bool *exists = NULL);

private:
    Int m_textCount;
    Char m_buffer[10 * 1024];
    Char m_buffer2[10 * 1024];
    Char m_buffer3[10 * 1024];
    StringInfo *m_stringInfo;
    StringLookUp *m_stringLUT;
    Bool m_initialized;
    unsigned char m_padding[3];
    NoString *m_noStringList;
    Int m_useStringFile;
    LanguageID m_language;
    UnicodeString m_failed;
    StringInfo *m_mapStringInfo;
    StringLookUp *m_mapStringLUT;
    Int m_mapTextCount;
};

UnicodeString GameTextManager::fetch(const Char *label, Bool *exists)
{
    DEBUG_ASSERTCRASH(m_initialized, ("String Manager has not been initialized"));

    if (m_stringInfo == NULL)
    {
        if (exists)
            *exists = FALSE;
        return m_failed;
    }

    StringLookUp *lookUp;
    StringLookUp key;
    AsciiString lb;
    lb = label;
    key.info = NULL;
    key.label = &lb;

    lookUp = Binary_Search(m_stringLUT, m_textCount, key);

    if (lookUp == NULL && m_mapStringLUT && m_mapTextCount)
    {
        lookUp = Binary_Search(m_mapStringLUT, m_mapTextCount, key);
    }

    if (lookUp == NULL)
    {
        if (exists)
            *exists = FALSE;

        UnicodeString missingString;
        missingString.format(UnicodeString(L"MISSING: '%hs'"), label);

        NoString *noString = m_noStringList;
        while (noString)
        {
            if (noString->text == missingString)
                return missingString;
            noString = noString->next;
        }

        noString = NEW NoString;
        noString->text = missingString;
        noString->next = m_noStringList;
        m_noStringList = noString;
        return noString->text;
    }

    if (exists)
        *exists = TRUE;
    return lookUp->info->text;
}
