// cl: /O2
// Retail RVA 0x005E7060. The matched LifeEvent createModule factory owns
// constructor 0x005E64A0, which installs vtable 0x01112190. Its slot zero
// reaches this wrapper through ILT 0x00005344; the destructor ILT is 0x00023650.
namespace FXParticleSystem
{
class LifeEventModule
{
public:
    virtual ~LifeEventModule();
private:
    unsigned char m_data[0x20];
};

LifeEventModule *MakeLifeEventModule()
{
    return new LifeEventModule;
}

void DeleteLifeEventModule(LifeEventModule *object)
{
    delete object;
}
}
