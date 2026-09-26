// cl: /DNDEBUG /MD /EHsc
// The GDI callee at RVA 0x0093C4A0 consumes UTF-16 text, WORD glyph
// output and a signed count; both calls below preserve that exact ABI.

class Rva0093C4A0Target
{
public:
    bool Check(const unsigned short *text, unsigned short *glyphs, int count);

    void *m_gap00;
    void *m_gap04;
    Rva0093C4A0Target *m_child;
};

class Rva0093C870Owner
{
public:
    Rva0093C4A0Target *Check(const unsigned short *text, unsigned short *glyphs, int count);

private:
    char m_gap00[0x4c];
    Rva0093C4A0Target *m_target;
};

Rva0093C4A0Target *Rva0093C870Owner::Check(
    const unsigned short *text, unsigned short *glyphs, int count)
{
    if (!m_target->Check(text, glyphs, count))
    {
        if (m_target->m_child != 0)
        {
            m_target->m_child->Check(text, glyphs, count);
            return m_target->m_child;
        }
    }

    return m_target;
}
