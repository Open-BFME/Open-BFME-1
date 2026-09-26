// cl: /O2
// Retail RVA 0x005EB5F0. The matched DefaultModule<1> factory constructor at
// 0x005EB4A0 installs vtable 0x01112DEC, whose slot zero reaches this wrapper
// through ILT 0x0003CA97. The wrapper calls its destructor through ILT 0x00022674.
namespace FXParticleSystem
{
template<int Category> class DefaultModule
{
public:
    virtual ~DefaultModule();
private:
    unsigned char m_data[0x1c];
};

typedef DefaultModule<1> DefaultModule1;

DefaultModule1 *MakeDefaultModule1()
{
    return new DefaultModule1;
}

void DeleteDefaultModule1(DefaultModule1 *object)
{
    delete object;
}
}
