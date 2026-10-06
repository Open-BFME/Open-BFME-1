// RVA 0x00283DF0, 118-byte address-derived record constructor.
// Evidence: targets/game/reverse/identity_evidence/rva00283df0.md
// stlport
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oi /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include <bitset>
typedef _STL::bitset<304> Rva002E7E00Owner;

class Rva00283DF0ExpLevelDrawEntry
{
public:
    Rva00283DF0ExpLevelDrawEntry();
    AsciiString m_unitType;
    unsigned int m_field04;
    Rva002E7E00Owner m_modelState;
    AsciiString m_locomotor;
};

Rva00283DF0ExpLevelDrawEntry::Rva00283DF0ExpLevelDrawEntry()
    : m_unitType(), m_modelState(), m_locomotor()
{
    m_field04 = 0;
    m_locomotor.StringBase<char>::set("", 0);
    m_unitType.StringBase<char>::clear();
}
