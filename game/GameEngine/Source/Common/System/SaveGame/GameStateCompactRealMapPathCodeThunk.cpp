// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0010F820 is a compact real-to-portable map-path helper reached
// through ILT 0x00011B35.  The caller loads TheGameState into ECX and passes
// an AsciiString reference with the hidden AsciiString result, but no caller
// recovers the original public member spelling.  Keep that proven ABI in an
// address-derived GameState view rather than claiming the nearby
// realMapPathToPortableMapPath method.

#include <string.h>

class AsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    bool startsWithNoCase(const StringBase<T> &source) const;
    bool startsWithNoCase(const T *text, int length) const;
    void set(const StringBase<T> &source);
    void set(const T *text, int length);
    void concat(const T *text, int length);
    void concat(const StringBase<T> &source);
    void toLower();

    // This overload is the retail one-argument concat used by the UserData
    // tail.  Keeping it distinct from concat(text,length) preserves both its
    // lifetime semantics and the exact compact helper call shape.
    void concat(const T *text);

    void set(const T *text)
    {
        set(text, text ? (int)strlen(text) : 0);
    }

    bool startsWithNoCase(const T *text) const
    {
        return startsWithNoCase(text, text ? (int)strlen(text) : 0);
    }

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &source);
    StringBase(const T *text);
    ~StringBase();

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}

    AsciiString(const AsciiString &source)
        : StringBase<char>(*(const StringBase<char> *)&source) {}

    AsciiString(const char *text)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(text);
    }

    ~AsciiString() {}

    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
        return *this;
    }

    AsciiString &operator=(const char *text);

    const char *str() const
    {
        return m_data ? (const char *)&m_data->data[0] : "";
    }

    int getLength() const
    {
        return m_data ? m_data->length : 0;
    }

    bool startsWithNoCase(const char *text, int length) const
    {
        return ((const StringBase<char> *)this)->startsWithNoCase(text, length);
    }

    bool startsWithNoCase(const char *text) const
    {
        return ((const StringBase<char> *)this)->startsWithNoCase(text);
    }

    void set(const char *text, int length)
    {
        ((StringBase<char> *)this)->set(text, length);
    }

    void concat(const char *text, int length)
    {
        ((StringBase<char> *)this)->concat(text, length);
    }

    void toLower()
    {
        ((StringBase<char> *)this)->toLower();
    }
};

class GameState
{
public:
    // The original public method name is not recovered; this is an
    // address-derived identity carrying only the proven GameState ABI.
    AsciiString rva0010f820MapPathCode(const AsciiString &path) const;
};

extern const char *PORTABLE_SAVE;
extern const char *g_012ABFC8;

static __forceinline const char *rva0010f820String(const char *const *slot)
{
    return *slot;
}

// The retail slots at C0/C4/CC/D0/D4 hold these path/code values.  These
// address-derived data views live only in this standalone TU, so the compiler
// sees the same mutable pointer loads as the compact helper.  BC/C8 remain
// direct address-derived lvalues because they are the Save prefix and its
// route code slots also consumed by matched map-path code.
extern const char *PORTABLE_MAPS;
extern const char *PORTABLE_USER_MAPS;
extern const char *rva0010e580MapsCode;
extern const char *rva0010e580UserCode;
extern const char *rva0010e580FallbackCode;

AsciiString GameState::rva0010f820MapPathCode(const AsciiString &path) const
{
    AsciiString prefix;

    if (((const StringBase<char> *)&path)->startsWithNoCase(
            rva0010f820String(&PORTABLE_SAVE),
            rva0010f820String(&PORTABLE_SAVE)
                ? (int)strlen(rva0010f820String(&PORTABLE_SAVE)) : 0))
    {
        const char *code = rva0010f820String(&g_012ABFC8);
        ((StringBase<char> *)&prefix)->set(
            code, code ? (int)strlen(code) : 0);

        const int tailOffset = (int)strlen(rva0010f820String(&PORTABLE_SAVE));
        const char *tail = path.str() + tailOffset;
        const int tailLength = tail ? (int)strlen(tail) : 0;
        ((StringBase<char> *)&prefix)->concat(tail, tailLength);
    }
    else if (((const StringBase<char> *)&path)->startsWithNoCase(
                 PORTABLE_MAPS,
                 PORTABLE_MAPS ? (int)strlen(PORTABLE_MAPS) : 0))
    {
        const char *code = rva0010e580MapsCode;
        ((StringBase<char> *)&prefix)->set(
            code, code ? (int)strlen(code) : 0);

        const int tailOffset =
            (int)strlen(PORTABLE_MAPS);
        const char *tail = path.str() + tailOffset;
        const int tailLength = tail ? (int)strlen(tail) : 0;
        ((StringBase<char> *)&prefix)->concat(tail, tailLength);
    }
    else if (((const StringBase<char> *)&path)->startsWithNoCase(
                 PORTABLE_USER_MAPS,
                 PORTABLE_USER_MAPS ? (int)strlen(PORTABLE_USER_MAPS) : 0))
    {
        prefix = rva0010e580UserCode;
        const int tailOffset =
            (int)strlen(PORTABLE_USER_MAPS);
        ((StringBase<char> *)&prefix)->concat(path.str() + tailOffset);
    }
    else
    {
        prefix = rva0010e580FallbackCode;
        ((StringBase<char> *)&prefix)->concat(
            *(const StringBase<char> *)&path);
    }

    prefix.toLower();
    return prefix;
}
