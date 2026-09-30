// ??0Rva001FCEC0@@QAE@XZ
// partial score=0.0 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "../game/GameEngine/Source/GameLogic/Object/Behavior/GateOpenAndCloseBehaviorModuleDataDestructorThunk.cpp"
#include "ascii_string.h"

extern unsigned int Rva012ADC38;

class Rva001FCEC0Ref
{
public:
    Rva001FCEC0Ref() : m_ptr(0) {}
    ~Rva001FCEC0Ref() { if (m_ptr) m_ptr->Release_Ref(); }
private:
    RefCountedThing *m_ptr;
};

// The vtable installed at 0x010A4210 is shared by the two gate module-data
// names. Preserve an address-derived identity until their base layout is proven.
class Rva001FCEC0 : public Snapshot
{
public:
    Rva001FCEC0();
    virtual ~Rva001FCEC0();
private:
    unsigned int m_unknown04;
    bool m_byte08;
    int m_dword0C;
    int m_dword10;
    AsciiString m_string14;
    Rva001FCEC0Ref m_ref18;
    Rva001FCEC0Ref m_ref1C;
    Rva001FCEC0Ref m_ref20;
    Rva001FCEC0Ref m_ref24;
    std::vector<AsciiString> m_vector28;
    std::vector<AsciiString> m_vector34;
    unsigned int m_dword40;
    unsigned int m_dword44;
};

Rva001FCEC0::Rva001FCEC0()
    : m_ref18(), m_ref1C(), m_ref20(), m_ref24()
{
    m_byte08 = false;
    m_dword0C = 50;
    m_dword10 = 50;
    m_string14.clear();
    AsciiString openLeft("OpenLeft");
    AsciiString openRight("OpenRight");
    AsciiString closed("Closed");
    m_vector28.clear();
    m_vector28.push_back(openLeft);
    m_vector28.push_back(openRight);
    m_vector34.clear();
    m_vector34.push_back(closed);
    unsigned int value = Rva012ADC38;
    m_dword40 = value;
    m_dword44 = value;
}
