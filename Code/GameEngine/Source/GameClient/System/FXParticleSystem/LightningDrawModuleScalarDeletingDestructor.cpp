// cl: /O2
// Retail RVA 0x005E5D00. The matched LightningDraw createModule factory owns
// constructor 0x005E5A20, which installs vtable 0x01111EE0. Its slot zero
// reaches this wrapper through ILT 0x00011CE3; the destructor ILT is 0x0000C39C.
namespace FXParticleSystem
{
class LightningDrawModule
{
public:
    virtual ~LightningDrawModule();
private:
    unsigned char m_data[0x18];
};

LightningDrawModule *MakeLightningDrawModule()
{
    return new LightningDrawModule;
}

void DeleteLightningDrawModule(LightningDrawModule *object)
{
    delete object;
}
}
