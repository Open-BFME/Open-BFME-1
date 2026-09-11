// cl: /DNDEBUG /MD /EHsc
// Retail 0x0010E580 expands BFME's compact map-path route codes back into
// their real prefixes.  Its public spelling is not recovered; keep the
// proven GameState ABI in this TU-local address-derived view.

#include <string.h>

class AsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    bool startsWithNoCase(const T *text, int length) const;
    bool startsWithNoCase(const T *text) const;
    void set(const StringBase<T> &source);
    void concat(const T *text, int length);

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
        : StringBase<char>(*(const StringBase<char> *)&source)
    {
    }

    ~AsciiString() {}

    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
        return *this;
    }

    AsciiString &operator+=(const char *text);

    const char *str() const
    {
        return m_data ? (const char *)&m_data->data[0] : (const char *)0x0107388B;
    }

    bool startsWithNoCase(const char *text) const
    {
        return ((const StringBase<char> *)this)->startsWithNoCase(text);
    }

};

// Retail 0x000326D2 is the thunk used by all four compact-token appends.
#pragma comment(linker, "/alternatename:??YAsciiString@@QAEAAV0@PBD@Z=?j_000326d2@@YAXXZ")
// Retail 0x00002667 is the thunk used by the one-argument fallback prefix check.
#pragma comment(linker, "/alternatename:?startsWithNoCase@?$StringBase@D@@QBE_NPBD@Z=?j_00002667@@YAXXZ")

class Rva0010E580GameState
{
public:
    AsciiString rva0010e580MapPathCode(const AsciiString &path) const;
};

static __forceinline const char *rva0010e580String(unsigned int address)
{
    return *(const char *const *)address;
}

const char *rva0010e580MapsCode = "M";
const char *rva0010e580MapsPrefix = "Maps\\";
const char *rva0010e580UserCode = "U";
const char *rva0010e580UserPrefix = "UserData\\Maps\\";
const char *rva0010e580FallbackCode = "X";

// ?rva0010e580MapPathCode@GameState@@QBE?AVAsciiString@@ABV2@@Z
AsciiString Rva0010E580GameState::rva0010e580MapPathCode(
    const AsciiString &path) const
{
    AsciiString prefix;

    if (((const StringBase<char> *)&path)->startsWithNoCase(
            rva0010e580String(0x012ABFC8),
            rva0010e580String(0x012ABFC8)
                ? (int)strlen(rva0010e580String(0x012ABFC8)) : 0))
    {
        ((StringBase<char> *)&prefix)->concat(
            rva0010e580String(0x012ABFBC),
            rva0010e580String(0x012ABFBC)
                ? (int)strlen(rva0010e580String(0x012ABFBC)) : 0);

        const int tailOffset =
            (int)strlen(rva0010e580String(0x012ABFC8));
        const char *tail = path.str() + tailOffset;
        const int tailLength = tail ? (int)strlen(tail) : 0;
        ((StringBase<char> *)&prefix)->concat(tail, tailLength);
    }
    else if (((const StringBase<char> *)&path)->startsWithNoCase(
                 rva0010e580MapsCode,
                 rva0010e580MapsCode
                     ? (int)strlen(rva0010e580MapsCode) : 0))
    {
        ((StringBase<char> *)&prefix)->concat(
            rva0010e580MapsPrefix,
            rva0010e580MapsPrefix
                ? (int)strlen(rva0010e580MapsPrefix) : 0);

        const int tailOffset =
            (int)strlen(rva0010e580MapsCode);
        const char *tail = path.str() + tailOffset;
        const int tailLength = tail ? (int)strlen(tail) : 0;
        ((StringBase<char> *)&prefix)->concat(tail, tailLength);
    }
    else if (((const StringBase<char> *)&path)->startsWithNoCase(
                 rva0010e580UserCode,
                 rva0010e580UserCode
                     ? (int)strlen(rva0010e580UserCode) : 0))
    {
        prefix += rva0010e580UserPrefix;

        const int tailOffset =
            (int)strlen(rva0010e580UserCode);
        prefix += path.str() + tailOffset;
    }
    else if (path.startsWithNoCase(rva0010e580FallbackCode))
    {
        const int tailOffset =
            (int)strlen(rva0010e580FallbackCode);
        prefix += path.str() + tailOffset;
    }
    else
    {
        prefix = path;
    }

    return prefix;
}
