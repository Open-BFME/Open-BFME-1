// cl: /O2
// Retail RVA 0x005EB630. The matched DefaultModule<2> factory constructor at
// 0x005EB510 installs vtable 0x01112E1C, whose slot zero reaches this wrapper
// through ILT 0x00048E23. The wrapper calls its destructor through ILT 0x000287D6.
namespace FXParticleSystem
{
template<int Category> class DefaultModule
{
public:
    virtual ~DefaultModule();
private:
    unsigned char m_data[0x1c];
};

typedef DefaultModule<2> DefaultModule2;

DefaultModule2 *MakeDefaultModule2()
{
    return new DefaultModule2;
}

void DeleteDefaultModule2(DefaultModule2 *object)
{
    delete object;
}
}
