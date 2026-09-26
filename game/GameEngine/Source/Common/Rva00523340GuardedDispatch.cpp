// Open-BFME: guarded virtual dispatch reconstructed from retail RVA 0x00523340.

class Rva00523340Target
{
public:
#define RVA00523340_UNUSED_SLOT(N) virtual void slot##N();
    RVA00523340_UNUSED_SLOT(0)
    RVA00523340_UNUSED_SLOT(1)
    RVA00523340_UNUSED_SLOT(2)
    RVA00523340_UNUSED_SLOT(3)
    RVA00523340_UNUSED_SLOT(4)
    RVA00523340_UNUSED_SLOT(5)
    RVA00523340_UNUSED_SLOT(6)
    RVA00523340_UNUSED_SLOT(7)
    RVA00523340_UNUSED_SLOT(8)
    RVA00523340_UNUSED_SLOT(9)
    RVA00523340_UNUSED_SLOT(10)
    RVA00523340_UNUSED_SLOT(11)
    RVA00523340_UNUSED_SLOT(12)
    RVA00523340_UNUSED_SLOT(13)
    virtual void dispatch(int value);
#undef RVA00523340_UNUSED_SLOT
};

class Rva00523340Object
{
public:
    void dispatchOnce();

private:
    unsigned char m_padding[4];
    Rva00523340Target* m_target;
    unsigned char m_gap[0x10];
    unsigned char m_dispatched;
};

void Rva00523340Object::dispatchOnce()
{
    if (!m_dispatched)
    {
        m_target->dispatch(1);
        m_dispatched = 1;
    }
}
