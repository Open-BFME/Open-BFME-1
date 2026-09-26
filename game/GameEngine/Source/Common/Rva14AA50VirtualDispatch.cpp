struct Rva14AA50Interface
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
    virtual void dispatch(int first, int second);
};

extern "C" void Rva14AA50VirtualDispatch(Rva14AA50Interface *object, int first, int second)
{
    object->dispatch(first, second);
}
