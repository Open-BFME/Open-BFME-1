struct Rva189BA0VirtualSlotFourDispatchThunk
{
    virtual void slot_zero() = 0;
    virtual void slot_one() = 0;
    virtual void slot_two() = 0;
    virtual void slot_three() = 0;
    virtual void invoke() = 0;

    void dispatch();
};

// ?d_00189ba0@@YAXXZ
void Rva189BA0VirtualSlotFourDispatchThunk::dispatch()
{
    invoke();
}
