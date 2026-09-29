// cl: /MD

class Rva0087DC40VirtualOwner
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
    virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
    virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
    virtual void slot90(const void *, void *, int);
};

void Rva0087DC40DispatchRaw(Rva0087DC40VirtualOwner *owner, void *value)
{
    owner->slot90("GeometryType", value, 4);
}
