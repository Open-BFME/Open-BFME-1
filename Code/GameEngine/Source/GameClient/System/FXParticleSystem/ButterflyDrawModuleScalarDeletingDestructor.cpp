// cl: /O2
// Retail RVA 0x005E5C30. The matched ButterflyDraw createModule factory owns
// constructor 0x005E5960, which installs vtable 0x01111E68. Its slot zero
// reaches this wrapper through ILT 0x00039E87; the destructor ILT is 0x0002CEB7.
namespace FXParticleSystem
{
class ButterflyDrawModule
{
public:
    virtual ~ButterflyDrawModule();
private:
    unsigned char m_data[0x18];
};

ButterflyDrawModule *MakeButterflyDrawModule()
{
    return new ButterflyDrawModule;
}

void DeleteButterflyDrawModule(ButterflyDrawModule *object)
{
    delete object;
}
}
