// Open-BFME: atomic counter increment reconstructed from retail RVA 0x009587C0.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);

class Rva009587C0Counter
{
public:
    int incrementAndGet(void);

private:
    char m_pad0[8];
    long m_count;
};

int Rva009587C0Counter::incrementAndGet(void)
{
    InterlockedIncrement(&m_count);
    return m_count;
}
