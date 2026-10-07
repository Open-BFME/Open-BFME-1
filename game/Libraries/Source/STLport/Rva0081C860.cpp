// cl: /MD /DNDEBUG
// Address-owned initialization wrapper. Original owner and template arguments
// are unproven; the field names below describe only witnessed offsets.
// See targets/game/reverse/identity_evidence/0x0081c860.md.
struct Rva0081C6A0
{
    unsigned int m_00;
    Rva0081C6A0 *rva0081C6A0(const void *, unsigned int);
};
struct Rva0081C860
{
    unsigned int m_00;
    unsigned int m_04;
    Rva0081C6A0 m_08;
    Rva0081C860 *rva0081C860(const void *arg);
};
Rva0081C860 *Rva0081C860::rva0081C860(const void *arg)
{
    m_00 = 0;
    m_04 = 0;
    m_08.rva0081C6A0(arg, 0);
    return this;
}

// A second wrapper has the same observed operations with a distinct
// physical callee. Its original template arguments remain unproven too.
// See targets/game/reverse/identity_evidence/0x0081d8f0.md.
struct Rva0081D5E0
{
    unsigned int m_00;
    Rva0081D5E0 *rva0081D5E0(const void *, unsigned int);
};
struct Rva0081D8F0
{
    unsigned int m_00;
    unsigned int m_04;
    Rva0081D5E0 m_08;
    Rva0081D8F0 *rva0081D8F0(const void *arg);
};
Rva0081D8F0 *Rva0081D8F0::rva0081D8F0(const void *arg)
{
    m_00 = 0;
    m_04 = 0;
    m_08.rva0081D5E0(arg, 0);
    return this;
}
