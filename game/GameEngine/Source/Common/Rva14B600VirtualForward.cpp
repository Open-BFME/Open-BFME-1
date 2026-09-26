struct Rva14B600Interface
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
    virtual void dispatch();

    void forward();
};

// ?d_0014b600@@YAXXZ
void Rva14B600Interface::forward()
{
    dispatch();
}
