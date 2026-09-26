// cl: /O2
// Retail RVA 0x005E5B10. The matched StreakDraw createModule factory owns
// constructor 0x005E58A0, which installs vtable 0x01111DF0. Its slot zero
// reaches this wrapper through ILT 0x00029AEB; the destructor ILT is 0x00019CA4.
namespace FXParticleSystem
{
class StreakDrawModule
{
public:
    virtual ~StreakDrawModule();
private:
    unsigned char m_data[0x18];
};

StreakDrawModule *MakeStreakDrawModule()
{
    return new StreakDrawModule;
}

void DeleteStreakDrawModule(StreakDrawModule *object)
{
    delete object;
}
}
