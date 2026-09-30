// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00362670 resets this record through the caller at 0x00365DF0.
// The receiver identity is unproved; field names retain their witnessed offsets.
#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>

extern const AsciiString Rva01336E50EmptyString;

template<int N> struct Rva00362670Words
{
    unsigned int words[N];
    void clear() { memset(words, 0, sizeof(words)); }
};

class Rva00362670Owner
{
public:
    void reset();
private:
    int field00;
    AsciiString field04;
    int field08, field0C;
    Rva00362670Words<6> field10;
    Rva00362670Words<3> field28;
    int field34;
    bool field38, field39;
    char padding3A[2];
    int field3C, field40, field44, field48;
    AsciiString field4C;
    Rva00362670Words<10> field50;
    UnicodeString field78;
    Rva00362670Words<6> field7C, field94;
    AsciiString fieldAC, fieldB0;
};

void Rva00362670Owner::reset()
{
    field04 = Rva01336E50EmptyString;
    field08 = 0;
    field0C = 0;
    field10.clear();
    field7C.clear();
    field94.clear();
    field28.clear();
    field34 = 0;
    field38 = false;
    field39 = false;
    field3C = 0;
    field40 = 0;
    field44 = 0;
    field48 = 0;
    field50.clear();
    ((StringBase<unsigned short> *)&field78)->clear();
    fieldAC.clear();
    fieldB0.clear();
    field4C.clear();
}
