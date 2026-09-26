// Open-BFME: three-stage virtual chain reconstructed from retail RVA 0x0044F320.

class Rva0044F320VirtualChain
{
public:
    virtual void slot0(void);
    virtual void slot1(void);
    virtual void slot2(void);
    virtual void slot3(void);

    void invoke(void);
};

void Rva0044F320VirtualChain::invoke(void)
{
    slot1();
    slot2();
    slot3();
}
