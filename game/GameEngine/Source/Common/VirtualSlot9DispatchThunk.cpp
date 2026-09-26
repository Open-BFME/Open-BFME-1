struct VirtualSlot9Dispatch
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
    virtual void invoke(void *first, void *second) = 0;
};

void dispatchVirtualSlot9(VirtualSlot9Dispatch *object, void *first, void *second)
{
    object->invoke(first, second);
}
