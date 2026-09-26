// cl: /O2
// Retail RVA 0x005E5CC0. The matched DefaultParticleModule<6> constructor at
// 0x005E59C0 installs vtable 0x01111EA4, whose slot zero reaches this wrapper
// through ILT 0x0002DF0B. The wrapper calls its destructor through ILT 0x0002E050.
namespace FXParticleSystem
{
template<int Category> class DefaultParticleModule
{
public:
    virtual ~DefaultParticleModule();
private:
    unsigned char m_data[0x14];
};

typedef DefaultParticleModule<6> DefaultParticleModule6;

DefaultParticleModule6 *MakeDefaultParticleModule6()
{
    return new DefaultParticleModule6;
}

void DeleteDefaultParticleModule6(DefaultParticleModule6 *object)
{
    delete object;
}
}
