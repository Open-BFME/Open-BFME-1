// The BFME archive path keeps the WWLib string object by value.  The class is
// repeated here so this body can keep the retail ABI local to its TU.

typedef bool Bool;
typedef int Int;

class BFMERetailAsciiString;

template <typename T>
class StringBase
{
    friend class BFMERetailAsciiString;

private:
    StringBase();
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();

public:
    int getLength() const;
    const T *str() const;

private:
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
    BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
    BFMERetailAsciiString(const BFMERetailAsciiString &other)
        : StringBase<char>(other) {}
    ~BFMERetailAsciiString() {}

    Int getLength() const
    {
        return m_data != 0 ? m_data->length : 0;
    }

    const char *str() const
    {
        return m_data != 0 ? &m_data->data[0] : "";
    }
};

extern "C" int (__cdecl *__imp__tolower)(int character);

// ?SearchStringMatches@@YA_NVBFMERetailAsciiString@@0@Z
Bool SearchStringMatches(BFMERetailAsciiString str, BFMERetailAsciiString searchString)
{
    if (str.getLength() == 0) {
        if (searchString.getLength() == 0) {
            return true;
        }
        return false;
    }
    if (searchString.getLength() == 0) {
        return false;
    }

    const char *c1 = str.str();
    const char *c2 = searchString.str();
    int (__cdecl *toLower)(int) = __imp__tolower;

    while ((toLower(*c1) == toLower(*c2)) || (*c2 == '?') || (*c2 == '*')) {
        if ((toLower(*c1) == toLower(*c2)) || (*c2 == '?')) {
            ++c1;
            ++c2;
        } else if (*c2 == '*') {
            ++c2;
            if (*c2 == 0) {
                return true;
            }
            while (*c1 != 0) {
                if (SearchStringMatches(BFMERetailAsciiString(c1), BFMERetailAsciiString(c2))) {
                    return true;
                }
                ++c1;
            }
        }
        if (*c1 == 0) {
            if (*c2 == 0) {
                return true;
            }
            return false;
        }
        if (*c2 == 0) {
            return false;
        }
    }
    return false;
}
