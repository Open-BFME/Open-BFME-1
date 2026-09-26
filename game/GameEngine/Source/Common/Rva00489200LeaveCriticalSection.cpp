// Open-BFME: lock-release method reconstructed from retail RVA 0x00489200.

struct Rva00489200CriticalSection;
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
    Rva00489200CriticalSection *section);

class Rva00489200Lock
{
public:
    void leave(void);

private:
    Rva00489200CriticalSection *m_section;
};

void Rva00489200Lock::leave(void)
{
    LeaveCriticalSection(m_section);
}
