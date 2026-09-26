// Open-BFME: two virtual calls reconstructed from retail RVA 0x002D9A70.

class Rva002D9A70Object
{
public:
#define RVA002D9A70_UNUSED_SLOT(N) virtual void slot##N();
    RVA002D9A70_UNUSED_SLOT(0)
    RVA002D9A70_UNUSED_SLOT(1)
    RVA002D9A70_UNUSED_SLOT(2)
    RVA002D9A70_UNUSED_SLOT(3)
    RVA002D9A70_UNUSED_SLOT(4)
    RVA002D9A70_UNUSED_SLOT(5)
    RVA002D9A70_UNUSED_SLOT(6)
    virtual void first();
    virtual void second(int value);
#undef RVA002D9A70_UNUSED_SLOT
};

void Rva002D9A70Invoke(Rva002D9A70Object *object)
{
    object->first();
    object->second(0);
}
