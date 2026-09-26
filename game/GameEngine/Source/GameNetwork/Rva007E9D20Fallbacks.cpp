struct Rva007E9D20Provider
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void *resolve();
};

struct Rva007E9D40Provider
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void *resolve();
};

class Rva007E9D20Owner
{
public:
    void *resolve();
private:
    char m_padding00[0xc];
    Rva007E9D20Provider *m_provider;
    char m_padding10[0x218];
    void *m_cached;
};

void *Rva007E9D20Owner::resolve()
{
    if (m_cached)
        return m_cached;
    if (m_provider)
        return m_provider->resolve();
    return 0;
}

class Rva007E9D40Owner
{
public:
    unsigned char *resolve();
private:
    char m_padding00[0xc];
    Rva007E9D40Provider *m_provider;
    char m_padding10[0xf1];
    unsigned char m_flag;
};

unsigned char *Rva007E9D40Owner::resolve()
{
    if (m_flag)
        return &m_flag;
    if (m_provider)
        return reinterpret_cast<unsigned char *>(m_provider->resolve());
    return 0;
}

class Rva007EA970Owner
{
public:
    unsigned char *resolve();
private:
    void *m_head;
    Rva007E9D40Owner *m_inner;
};

unsigned char *Rva007EA970Owner::resolve()
{
    return m_inner->resolve();
}
