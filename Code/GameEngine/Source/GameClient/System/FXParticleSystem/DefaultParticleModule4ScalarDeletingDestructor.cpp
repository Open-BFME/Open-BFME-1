// cl: /O2
// Retail RVA 0x005E3920. The DefaultParticleModule<4> base constructor at
// 0x005E38E0 installs vtable 0x01111994, whose slot zero reaches this wrapper
// through ILT 0x0001C0E4. The wrapper calls its destructor through ILT 0x0000EA52.
namespace FXParticleSystem
{
template<int Category> class DefaultParticleModule
{
public:
    virtual ~DefaultParticleModule();
private:
    unsigned char m_data[0x14];
};

typedef DefaultParticleModule<4> DefaultParticleModule4;

DefaultParticleModule4 *MakeDefaultParticleModule4()
{
    return new DefaultParticleModule4;
}

void DeleteDefaultParticleModule4(DefaultParticleModule4 *object)
{
    delete object;
}
}
