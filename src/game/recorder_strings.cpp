#include "string_base.h"

#define EOF (-1)

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) int __cdecl fgetc(FILE *stream);

class AsciiString {
public:
    AsciiString() { base()->StringBase<char>::StringBase(); }
    AsciiString(const AsciiString &that) { base()->StringBase<char>::StringBase(*that.base()); }
    AsciiString(const char *str) { base()->StringBase<char>::StringBase(str); }
    ~AsciiString() { base()->releaseBuffer(); }

private:
    StringBase<char> *base() { return (StringBase<char> *)this; }
    const StringBase<char> *base() const { return (const StringBase<char> *)this; }

private:
    StringBase<char>::Header *m_data;
};

class RecorderClass {
protected:
    AsciiString readAsciiString();

private:
    int m_padding0;
    int m_padding4;
    int m_padding8;
    FILE *m_file;
};

AsciiString RecorderClass::readAsciiString()
{
    char str[1024] = "";
    int index = 0;

    int c = fgetc(m_file);
    if (c == EOF) {
        str[index] = 0;
    }
    str[index] = c;

    while (index < 1024 && str[index] != 0) {
        ++index;
        int c = fgetc(m_file);
        if (c == EOF) {
            str[index] = 0;
            break;
        }
        str[index] = c;
    }
    str[1023] = '\0';

    AsciiString retval(str);
    return retval;
}
