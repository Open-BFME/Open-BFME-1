// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x003A4BD0/133: the receiver at ECX is passed unchanged to
// Rva003A48B0Owner::applyByName through ILT 0x00032010 twice. The matched
// MainMenuMediumScaleUpTransition::init and Rva003BEED0::finish callers
// independently confirm this body, but no source-level method spelling is
// known; the address stays in the method name. The old/new selectors choose
// the three four-byte strings at g_bfmeGameCW+0x188..0x190 or the shared
// empty-string object at 0x01336E50.
#include "ascii_string.h"

class BfmeGameCW
{
public:
    char m_pad00[0x188];
    AsciiString m_string188;
    AsciiString m_string18C;
    AsciiString m_string190;
};
extern BfmeGameCW *g_bfmeGameCW;
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
    case 0: oldName = &g_bfmeGameCW->m_string190; break;
    case 1: oldName = &g_bfmeGameCW->m_string18C; break;
    case 2: oldName = &g_bfmeGameCW->m_string188; break;
    default: oldName = &Rva01336E50EmptyString; break;
    }
    AsciiString *newName;
    switch (state) {
    case 0: newName = &g_bfmeGameCW->m_string190; break;
    case 1: newName = &g_bfmeGameCW->m_string18C; break;
    case 2: newName = &g_bfmeGameCW->m_string188; break;
    default: newName = &Rva01336E50EmptyString; break;
    }
    applyByName(oldName, 0, 0);
    applyByName(newName, 1, 0);
    m_state3C = state;
}
