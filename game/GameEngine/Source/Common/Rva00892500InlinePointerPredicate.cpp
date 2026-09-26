// Open-BFME: inline-buffer pointer predicate reconstructed from retail RVA 0x00892500.

class Rva00892500Object
{
public:
    char m_padding[8];
    int *m_end;
    int m_inline;

    bool usesInlineBuffer();
};

bool Rva00892500Object::usesInlineBuffer()
{
    int *end = m_end;
    int *inlineValue = &m_inline;
    return end == inlineValue;
}

class Rva00892550Object
{
public:
    char m_padding[8];
    int *m_end;
    int m_inline;

    bool usesInlineBuffer();
};

bool Rva00892550Object::usesInlineBuffer()
{
    int *end = m_end;
    int *inlineValue = &m_inline;
    return end == inlineValue;
}
