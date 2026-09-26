// cl: /DNDEBUG /MD /EHsc

struct Rva00893E00Element
{
    ~Rva00893E00Element(void);

private:
    unsigned m_value;
};

extern void b_008939c0(void);

class Gen_t_00894a10_p12cd
{
public:
    ~Gen_t_00894a10_p12cd(void);

private:
    unsigned m_pad0;
    unsigned m_pad4;
    Rva00893E00Element *m_data;
    Rva00893E00Element m_inline[2];
};

Gen_t_00894a10_p12cd::~Gen_t_00894a10_p12cd(void)
{
    if (m_data != m_inline)
        ((void (__cdecl *)(void *, void *, void *))b_008939c0)(m_data, 0, 0);
}
