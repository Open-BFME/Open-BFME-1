// Open-BFME: nested-field sum reconstructed from retail RVA 0x0020D830.

// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads the dword at +0x3C through
// its own file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

class Rva0020D830Nested
{
public:
    char m_pad0[8];
    int m_value;
    char m_pad0C[0x30];
    int m_globalValue;
};

class Rva0020D830Object
{
public:
    void update(void);

private:
    char m_pad0[4];
    Rva0020D830Nested * volatile m_nested;
    char m_pad8[0x1C];
    int m_sumFirst;
    int m_sumSecond;
};

void Rva0020D830Object::update(void)
{
    int nestedValue = m_nested->m_value;
    int globalValue = ((Rva0020D830Nested *)TheGameLogic)->m_globalValue;
    int sum = globalValue + nestedValue;
    m_sumFirst = sum;
    m_sumSecond = sum;
}
