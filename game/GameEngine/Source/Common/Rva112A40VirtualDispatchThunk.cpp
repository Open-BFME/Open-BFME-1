struct Rva112A40VirtualDispatchThunk
{
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void slot2() = 0;
    virtual void slot3() = 0;
    virtual void slot4() = 0;
    virtual void slot5() = 0;
    virtual void slot6() = 0;
    virtual void slot7() = 0;
    virtual void slot8() = 0;
    virtual void target() = 0;

    void dispatch();
};

void Rva112A40VirtualDispatchThunk::dispatch()
{
    target();
}
