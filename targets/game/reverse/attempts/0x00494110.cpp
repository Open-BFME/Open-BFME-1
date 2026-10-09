// ??0Rva00494110@@QAE@PAX@Z
// partial score=0.7727 date=2026-10-09
// ??0Rva00494110@@QAE@PAX@Z
// cl: /O2 /DNDEBUG /MD /EHsc
#include "../../../../game/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h"
extern "C" const void *__identifier("??_7S4Dtor00494090@@6B@")[];
class BfmeAptScreenBase {
public:
    BfmeAptScreenBase(void *context);
    ~BfmeAptScreenBase();
    const void **m_bfmeVft;
    BfmeAptScreenBaseLayout<> m_layout;
};
class Rva004948B0OwnedSubsystem {
public:
    Rva004948B0OwnedSubsystem(void *factory);
    ~Rva004948B0OwnedSubsystem();
    char m_storage[0x38];
};
#include "../../../../game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
class Rva00494110 : public BfmeAptScreenBase {
public:
    Rva00494110(void *context);
    Rva004948B0OwnedSubsystem m_owned;
    unsigned int m_status;
    AsciiString m_text;
    int m_258;
    int m_25c;
    int m_260;
    bool m_264;
};
Rva00494110::Rva00494110(void *context)
    : BfmeAptScreenBase(context), m_owned((m_bfmeVft = __identifier("??_7S4Dtor00494090@@6B@"), (void *)0)), m_258(0), m_25c(0), m_260(0)
{
    m_layout.m_status |= 0x640;
    m_status = m_layout.m_status;
    m_264 = false;
}
