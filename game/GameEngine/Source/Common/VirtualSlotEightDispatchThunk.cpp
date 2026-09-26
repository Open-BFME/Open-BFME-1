struct VirtualSlotEightDispatchThunk
{
    virtual void slot_zero() = 0;
    virtual void slot_one() = 0;
    virtual void slot_two() = 0;
    virtual void slot_three() = 0;
    virtual void slot_four() = 0;
    virtual void slot_five() = 0;
    virtual void slot_six() = 0;
    virtual void slot_seven() = 0;
    virtual void invoke() = 0;

    void dispatch();
};

// ?d_0006b420@@YAXXZ
void VirtualSlotEightDispatchThunk::dispatch()
{
    invoke();
}
