// cl: /O2
// Retail RVA 0x005E3360. The DefaultParticleModule<5> base constructor at
// 0x005E3300 installs vtable 0x0111182C, whose slot zero reaches this wrapper
// through ILT 0x0000C32E. The wrapper calls its destructor through ILT 0x0004016A.
namespace FXParticleSystem
{
template<int Category> class DefaultParticleModule
{
public:
    virtual ~DefaultParticleModule();
private:
    unsigned char m_data[0x14];
};

typedef DefaultParticleModule<5> DefaultParticleModule5;

DefaultParticleModule5 *MakeDefaultParticleModule5()
{
    return new DefaultParticleModule5;
}

void DeleteDefaultParticleModule5(DefaultParticleModule5 *object)
{
    delete object;
}
}
