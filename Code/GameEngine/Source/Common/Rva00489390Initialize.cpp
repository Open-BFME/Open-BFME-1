// Open-BFME: critical-section initialization helper reconstructed from
// retail RVA 0x00489390.

struct Rva00489390CriticalSection
{
    char m_storage[0x18];
};

extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(
    Rva00489390CriticalSection *section);

class Rva00489390Object
{
public:
    __declspec(noinline) void initialize(void);

private:
    char m_gap[0x20];
    unsigned int m_value20;
    unsigned int m_value24;
    unsigned int m_value28;
    unsigned int m_value2C;
    char m_pad30[4];
    Rva00489390CriticalSection m_section;
    unsigned char m_initialized;
};

void Rva00489390Object::initialize(void)
{
    m_value20 = 0;
    m_value24 = 0;
    m_value28 = 0;
    m_value2C = 0;

    if (m_initialized == 0)
    {
        InitializeCriticalSection(&m_section);
        m_initialized = 1;
    }
}
