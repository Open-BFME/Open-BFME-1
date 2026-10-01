// ?method@Rva000E15A0@@QAE_NW4NameKeyType@@PAI@Z
// partial score=0.375 date=2026-10-01
// cl: /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include <vector>

enum NameKeyType;
AsciiString KEYNAME(NameKeyType key);

struct Rva000E15A0Record
{
    NameKeyType m_at00;
    char m_at04[0x120];
};

class Rva000E15A0
{
public:
    bool method(NameKeyType key, unsigned int *outIndex);
    char m_at00[8];
    _STL::vector<Rva000E15A0Record> m_records;

    unsigned int count() const { return m_records.size(); }
};

bool Rva000E15A0::method(NameKeyType key, unsigned int *outIndex)
{
    for (unsigned int index = 0; index < count(); ++index)
    {
        AsciiString name = KEYNAME(m_records[index].m_at00);
        if (m_records[index].m_at00 == key)
        {
            *outIndex = index;
            return true;
        }
    }
    return false;
}
