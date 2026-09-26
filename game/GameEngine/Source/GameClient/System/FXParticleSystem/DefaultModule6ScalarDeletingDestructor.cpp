// cl: /O2
// Retail RVA 0x005E5A80. The DefaultModule<6> constructor at 0x005E5840
// installs vtable 0x01111DB4, whose slot zero reaches this wrapper through
// ILT 0x0000FE1B. The wrapper calls its destructor through ILT 0x000278B8.
namespace FXParticleSystem
{
template<int Category> class DefaultModule
{
public:
    virtual ~DefaultModule();
private:
    unsigned char m_data[0x18];
};

typedef DefaultModule<6> DefaultModule6;

DefaultModule6 *MakeDefaultModule6()
{
    return new DefaultModule6;
}

void DeleteDefaultModule6(DefaultModule6 *object)
{
    delete object;
}
}
