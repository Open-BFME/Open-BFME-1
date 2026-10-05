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
        return m_data ? (const char *)&m_data->data[0] : "";
    }

    bool startsWithNoCase(const char *text) const
    {
        return ((const StringBase<char> *)this)->startsWithNoCase(text);
    }

};

// Both retail callees this TU needs are referenced directly by name: the
// compact-token append thunk 0x000326D2 (?j_000326d2@@YAXXZ), and the matched
// startsWithNoCase body 0x008875E0 that retail calls directly for the prefix
// checks.  Neither needs a linker alias.
extern void j_000326d2();

class Rva0010E580GameState
{
public:
    AsciiString rva0010e580MapPathCode(const AsciiString &path) const;
};

extern const char *PORTABLE_SAVE;
extern const char *g_012ABFC8;

static __forceinline const char *rva0010e580String(const char *const &value)
{
    return value;
}

const char *rva0010e580MapsCode = "M";
extern const char *PORTABLE_MAPS;
const char *rva0010e580UserCode = "U";
extern const char *PORTABLE_USER_MAPS;
const char *rva0010e580FallbackCode = "X";

// ?rva0010e580MapPathCode@GameState@@QBE?AVAsciiString@@ABV2@@Z
AsciiString Rva0010E580GameState::rva0010e580MapPathCode(
    const AsciiString &path) const
{
    AsciiString prefix;

    // Retail 0x000326D2 is the thunk all three compact-token appends go through.
    // The two-argument prefix check keeps its real retail name
    // (?startsWithNoCase@?$StringBase@D@@QBE_NPBDH@Z, body 0x008875E0): retail
    // calls it directly rather than through the 0x00002667 thunk.
    typedef AsciiString &(AsciiString::*AppendFn)(const char *);
    union
    {
        void (*fn)();
        AppendFn append;
    } appendThunk = { j_000326d2 };

    if (((const StringBase<char> *)&path)->startsWithNoCase(
            rva0010e580String(g_012ABFC8),
            rva0010e580String(g_012ABFC8)
                ? (int)strlen(rva0010e580String(g_012ABFC8)) : 0))
    {
        ((StringBase<char> *)&prefix)->concat(
            rva0010e580String(PORTABLE_SAVE),
            rva0010e580String(PORTABLE_SAVE)
                ? (int)strlen(rva0010e580String(PORTABLE_SAVE)) : 0);

        const int tailOffset =
            (int)strlen(rva0010e580String(g_012ABFC8));
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
            PORTABLE_MAPS,
            PORTABLE_MAPS
                ? (int)strlen(PORTABLE_MAPS) : 0);

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
        (prefix.*appendThunk.append)(PORTABLE_USER_MAPS);

        const int tailOffset =
            (int)strlen(rva0010e580UserCode);
        (prefix.*appendThunk.append)(path.str() + tailOffset);
    }
    else if (path.startsWithNoCase(rva0010e580FallbackCode))
    {
        const int tailOffset =
            (int)strlen(rva0010e580FallbackCode);
        (prefix.*appendThunk.append)(path.str() + tailOffset);
    }
    else
    {
        prefix = path;
    }

    return prefix;
}
