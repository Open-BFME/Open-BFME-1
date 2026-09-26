// Retail at 0x00382900 is a five-byte thiscall tail dispatch through vtable
// offset 0x1C (slot 7).  The owning class is not recovered, so this shim
// preserves the observed virtual slot and calling convention only.

struct Rva00382900VirtualSlot7DispatchThunk
{
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void invoke() = 0;

    void dispatch();
};

void Rva00382900VirtualSlot7DispatchThunk::dispatch()
{
    invoke();
}
