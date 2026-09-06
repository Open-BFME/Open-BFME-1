// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2

class Rva002D9910Result
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void *getValue();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void apply(int value);
};

class Rva002D9910Nested
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual Rva002D9910Result *getResult();
};

class Rva002D9910Element
{
private:
    char m_pad00[0x0C];

public:
    Rva002D9910Nested m_nested;
};

class Rva002D9910Owner
{
private:
    char m_pad00[0x1F0];

public:
    Rva002D9910Element **m_elements;
};

class Rva002D9910State
{
private:
    char m_pad00[0x70];

public:
    void *m_compare;
};

class Rva002D9910
{
public:
    void process();
};

void Rva002D9910::process()
{
    Rva002D9910Owner *owner = *(Rva002D9910Owner **)((char *)this - 8);
    for (Rva002D9910Element **it = owner->m_elements; *it != 0; ++it)
    {
        Rva002D9910Result *result = (*it)->m_nested.getResult();
        if (result != 0)
        {
            Rva002D9910State *state = *(Rva002D9910State **)((char *)this - 0x0C);
            if (result->getValue() == state->m_compare)
                result->apply(1);
        }
    }
}
