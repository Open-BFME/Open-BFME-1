// cl: /O2
// Retail RVA 0x005E6FE0. The matched DefaultModule<3> factory constructor at
// 0x005E60F0 installs vtable 0x01112050, whose slot zero reaches this wrapper
// through ILT 0x000430EA. The wrapper calls its destructor through ILT 0x0003A1B6.
namespace FXParticleSystem
{
template<int Category> class DefaultModule
{
public:
    virtual ~DefaultModule();
private:
    unsigned char m_data[0x1c];
};

typedef DefaultModule<3> DefaultModule3;

DefaultModule3 *MakeDefaultModule3()
{
    return new DefaultModule3;
}

void DeleteDefaultModule3(DefaultModule3 *object)
{
    delete object;
}
}
