// cl: /O2

// Retail 0x0026CD40 forwards its third stack argument through vtable slot 11.
// The carved boundary provides no stronger owner identity.
struct Rva0026CD40VirtualSlot11
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void invoke(int value);

    void invokeThird(int unused1, int unused2, int value);
};

void Rva0026CD40VirtualSlot11::invokeThird(int, int, int value)
{
    invoke(value);
}
