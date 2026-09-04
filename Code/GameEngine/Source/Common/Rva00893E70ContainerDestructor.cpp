// cl: /DNDEBUG /MD /EHsc

struct Rva00893E70Element
{
    unsigned m_first;
    unsigned m_second;
    ~Rva00893E70Element(void);
};

extern void b_00893b30(void);

class Gen_uw_00893e70
{
public:
    ~Gen_uw_00893e70(void);

private:
    unsigned m_pad0;
    unsigned m_pad4;
    Rva00893E70Element *m_data;
    Rva00893E70Element m_inline[2];
};

Gen_uw_00893e70::~Gen_uw_00893e70(void)
{
    if (m_data != m_inline)
        ((void (__cdecl *)(void *, void *, void *))b_00893b30)(m_data, 0, 0);
}
