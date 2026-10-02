// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x003A4BD0/133 applies the old and new selector strings through ILT 0x00032010.
// Selectors read TheLivingWorldManager+0x188..0x190 or the shared empty-string object.
#include "ascii_string.h"

class BfmeGameCW
{
public:
    char m_pad00[0x188];
    AsciiString m_string188;
    AsciiString m_string18C;
    AsciiString m_string190;
};
// EA's singleton at 0x012F706C is defined in LivingWorldManager.cpp.
// The BfmeGameCW view preserves the selector-string layout.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
extern AsciiString Rva01336E50EmptyString;

class Rva003A48B0Owner
{
public:
    void applyByName(const AsciiString *name, char value, int mode);
    void rva003A4BD0(int state);
private:
    char m_pad00[0x3c];
    int m_state3C;
};

void Rva003A48B0Owner::rva003A4BD0(int state)
{
    AsciiString *oldName;
    switch (m_state3C) {
    case 0: oldName = &reinterpret_cast<BfmeGameCW *>(TheLivingWorldManager)->m_string190; break;
    case 1: oldName = &reinterpret_cast<BfmeGameCW *>(TheLivingWorldManager)->m_string18C; break;
    case 2: oldName = &reinterpret_cast<BfmeGameCW *>(TheLivingWorldManager)->m_string188; break;
    default: oldName = &Rva01336E50EmptyString; break;
    }
    AsciiString *newName;
    switch (state) {
    case 0: newName = &reinterpret_cast<BfmeGameCW *>(TheLivingWorldManager)->m_string190; break;
    case 1: newName = &reinterpret_cast<BfmeGameCW *>(TheLivingWorldManager)->m_string18C; break;
    case 2: newName = &reinterpret_cast<BfmeGameCW *>(TheLivingWorldManager)->m_string188; break;
    default: newName = &Rva01336E50EmptyString; break;
    }
    applyByName(oldName, 0, 0);
    applyByName(newName, 1, 0);
    m_state3C = state;
}
