class Rva007EB810Diag
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void release(int flags);
};

extern Rva007EB810Diag *g_Va0130A5A0;

void rva007EB710Release()
{
    if (g_Va0130A5A0)
        g_Va0130A5A0->release(1);
    g_Va0130A5A0 = 0;
}
