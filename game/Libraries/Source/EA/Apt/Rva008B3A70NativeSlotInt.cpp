// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B3A70: wrap virtual slot 0x74 when value kind is 0x21.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

struct Rva008B3A70Target
{
    virtual void unknownSlot00();
    virtual void unknownSlot01();
    virtual void unknownSlot02();
    virtual void unknownSlot03();
    virtual void unknownSlot04();
    virtual void unknownSlot05();
    virtual void unknownSlot06();
    virtual void unknownSlot07();
    virtual void unknownSlot08();
    virtual void unknownSlot09();
    virtual void unknownSlot10();
    virtual void unknownSlot11();
    virtual void unknownSlot12();
    virtual void unknownSlot13();
    virtual void unknownSlot14();
    virtual void unknownSlot15();
    virtual void unknownSlot16();
    virtual void unknownSlot17();
    virtual void unknownSlot18();
    virtual void unknownSlot19();
    virtual void unknownSlot20();
    virtual void unknownSlot21();
    virtual void unknownSlot22();
    virtual void unknownSlot23();
    virtual void unknownSlot24();
    virtual void unknownSlot25();
    virtual void unknownSlot26();
    virtual void unknownSlot27();
    virtual void unknownSlot28();
    virtual int slot74();
};

struct Rva008B3A70Value
{
    void *m_vtable;
    unsigned int m_flags;
    char m_padding[0x18];
    Rva008B3A70Target *m_target;
};

AptInteger *aptNativeSlot74At008B3A70(Rva008B3A70Value *value, int argc)
{
    int result = 0;
    if ((value->m_flags & 0x3f) == 0x21 && value->m_target)
    {
        Rva008B3A70Target *target = value->m_target;
        result = target->slot74();
    }
    return AptInteger::Create(result);
}
