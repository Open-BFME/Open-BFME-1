// cl: /O2
// An optional global dispatch object receives slot 5(1) before the pointer is cleared.
class Rva007EB710Object
{
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4();
    virtual void release(int mode);
};

struct Rva007EB810Diag;
extern Rva007EB810Diag *g_Va0130A5A0;

void Rva007EB710GlobalRelease()
{
    if (g_Va0130A5A0)
        reinterpret_cast<Rva007EB710Object *>(g_Va0130A5A0)->release(1);
    g_Va0130A5A0 = 0;
}
