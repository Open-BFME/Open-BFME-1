// cl: /O2
// Retail RVA 0x005E5BA0. The matched QuadDraw createModule factory owns
// constructor 0x005E5900, which installs vtable 0x01111E2C. Its slot zero
// reaches this wrapper through ILT 0x00040EAD; the destructor ILT is 0x0002FC48.
namespace FXParticleSystem
{
class QuadDrawModule
{
public:
    virtual ~QuadDrawModule();
private:
    unsigned char m_data[0x18];
};

QuadDrawModule *MakeQuadDrawModule()
{
    return new QuadDrawModule;
}

void DeleteQuadDrawModule(QuadDrawModule *object)
{
    delete object;
}
}
