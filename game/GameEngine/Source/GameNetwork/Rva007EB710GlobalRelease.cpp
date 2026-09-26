// cl: /O2
// An optional global dispatch object receives slot 5(1) before the pointer is cleared.
class Rva007EB710Object
{
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4();
    virtual void release(int mode);
};

extern Rva007EB710Object *Rva007EB710Global;

void Rva007EB710GlobalRelease()
{
    if (Rva007EB710Global)
        Rva007EB710Global->release(1);
    Rva007EB710Global = 0;
}
