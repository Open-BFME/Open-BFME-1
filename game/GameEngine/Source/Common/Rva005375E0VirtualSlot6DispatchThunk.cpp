// Retail at 0x005375E0 is a five-byte thiscall tail dispatch through vtable
// offset 0x18 (zero-based slot 6).  The owning class is unknown, so only the
// observed slot shape and calling convention are represented here.

struct Rva005375E0VirtualSlot6DispatchThunk
{
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void invoke() = 0;

    void dispatch();
};

void Rva005375E0VirtualSlot6DispatchThunk::dispatch()
{
    invoke();
}
