// Retail at 0x005BD3D0 is a five-byte thiscall tail dispatch through vtable
// offset 0x2C (zero-based slot 11).  The owning class is unknown, so only the
// observed slot shape and calling convention are represented here.

struct Rva005BD3D0VirtualSlot11DispatchThunk
{
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void invoke() = 0;

    void dispatch();
};

void Rva005BD3D0VirtualSlot11DispatchThunk::dispatch()
{
    invoke();
}
