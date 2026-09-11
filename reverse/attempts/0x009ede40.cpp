// ?bfmeForward@Gen_009EBB60Target@@QAEHXZ
// partial score=0.97 date=2026-09-11
// ?bfmeForward@Gen_009EBB60Target@@QAEHXZ
// cl: /O2 /DNDEBUG /MD /EHs-c-
extern "C" __declspec(dllimport) void __stdcall Rva01358D18Enter(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave(void *lock);

class Gen_009EBB60Target
{
public:
    int bfmeForward(void);

private:
    char m_pad00[0x78];
    int *m_78;
    int *m_7c;
    int *m_80;
    int *m_84;
    int *m_88;
    int *m_8c;
    int *m_90;
    int *m_94;
    int *m_98;
    int *m_9c;
    int *m_a0;
    int *m_a4;
    int *m_a8;
    int *m_ac;
    int *m_b0;
    int *m_b4;
    int *m_b8;
    int *m_bc;
    int *m_c0;
    int *m_c4;
    int *m_c8;
    int *m_cc;
    int *m_d0;
    int *m_d4;
    int *m_d8;
    int *m_dc;
    int *m_e0_data;
    int *m_e4_data;
    char m_pade8[0xf8];
    int m_1e0;
    int m_1e4;
};

int Gen_009EBB60Target::bfmeForward(void)
{
    if (m_1e0 == 0 && m_1e4 == 0)
        return 100;

    Rva01358D18Enter(reinterpret_cast<char *>(this) + 0x60);

    int result = ((m_e4_data - m_d4) + (m_bc - m_ac)
        + (m_94 - m_84) - 3) * 32
        + (m_b0 - m_b4) + (m_88 - m_8c)
        + (m_d8 - m_dc) + (m_a8 - m_a0)
        + (m_c8 - m_d0) + (m_80 - m_78);

    Rva01358E74Leave(reinterpret_cast<char *>(this) + 0x60);

    if (result == 0)
        return 100;

    unsigned int total = static_cast<unsigned int>(m_1e0 + m_1e4);
    return 99 - static_cast<int>(static_cast<unsigned int>(result * 99) / total);
}
