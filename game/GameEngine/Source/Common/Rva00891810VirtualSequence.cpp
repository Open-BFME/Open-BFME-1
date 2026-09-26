// Open-BFME: three virtual calls reconstructed from retail RVA 0x00891810.

class Rva00891810Object
{
public:
#define RVA00891810_UNUSED_SLOT(N) virtual void slot##N();
    RVA00891810_UNUSED_SLOT(0)
    RVA00891810_UNUSED_SLOT(1)
    RVA00891810_UNUSED_SLOT(2)
    RVA00891810_UNUSED_SLOT(3)
    RVA00891810_UNUSED_SLOT(4)
    RVA00891810_UNUSED_SLOT(5)
    RVA00891810_UNUSED_SLOT(6)
    RVA00891810_UNUSED_SLOT(7)
    RVA00891810_UNUSED_SLOT(8)
    RVA00891810_UNUSED_SLOT(9)
    RVA00891810_UNUSED_SLOT(10)
    RVA00891810_UNUSED_SLOT(11)
    RVA00891810_UNUSED_SLOT(12)
    virtual void callAt34(int value);
    virtual void callAt38();
    virtual void callAt3C();
#undef RVA00891810_UNUSED_SLOT

    void invoke();
};

void Rva00891810Object::invoke()
{
    callAt38();
    callAt3C();
    callAt34(1);
}
