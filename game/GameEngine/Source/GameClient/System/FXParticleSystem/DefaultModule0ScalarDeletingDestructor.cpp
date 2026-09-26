// cl: /O2
// Retail RVA 0x005E6FA0. The matched DefaultModule<0> factory constructor at
// 0x005E5FC0 installs vtable 0x01111FCC, whose slot zero reaches this wrapper
// through ILT 0x00045E99. The wrapper calls its destructor through ILT 0x000343EC.
namespace FXParticleSystem
{
template<int Category> class DefaultModule
{
public:
    virtual ~DefaultModule();
private:
    unsigned char m_data[0x1c];
};

typedef DefaultModule<0> DefaultModule0;

DefaultModule0 *MakeDefaultModule0()
{
    return new DefaultModule0;
}

void DeleteDefaultModule0(DefaultModule0 *object)
{
    delete object;
}
}
