// Open-BFME: conditional virtual dispatch reconstructed from retail RVA 0x0081C340.

class Rva0081C340Object
{
public:
#define RVA0081C340_UNUSED_SLOT(N) virtual void slot##N();
    RVA0081C340_UNUSED_SLOT(0)
    RVA0081C340_UNUSED_SLOT(1)
    RVA0081C340_UNUSED_SLOT(2)
    RVA0081C340_UNUSED_SLOT(3)
    RVA0081C340_UNUSED_SLOT(4)
    RVA0081C340_UNUSED_SLOT(5)
    RVA0081C340_UNUSED_SLOT(6)
    RVA0081C340_UNUSED_SLOT(7)
    RVA0081C340_UNUSED_SLOT(8)
    RVA0081C340_UNUSED_SLOT(9)
    RVA0081C340_UNUSED_SLOT(10)
    RVA0081C340_UNUSED_SLOT(11)
    RVA0081C340_UNUSED_SLOT(12)
    RVA0081C340_UNUSED_SLOT(13)
    virtual void dispatch();
#undef RVA0081C340_UNUSED_SLOT

    void resetIfNeeded();

private:
    unsigned char m_padding[0x10];
    unsigned char m_pending;
};

void Rva0081C340Object::resetIfNeeded()
{
    if (!m_pending)
        dispatch();
    m_pending = 0;
}
