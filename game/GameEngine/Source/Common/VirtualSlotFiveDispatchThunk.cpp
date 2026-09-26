struct VirtualSlotFiveDispatchThunk
{
    virtual void slot_zero() = 0;
    virtual void slot_one() = 0;
    virtual void slot_two() = 0;
    virtual void slot_three() = 0;
    virtual void slot_four() = 0;
    virtual void invoke() = 0;

    void dispatch();
};

void VirtualSlotFiveDispatchThunk::dispatch()
{
    invoke();
}
