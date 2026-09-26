// cl: /O2
// Retail RVA 0x005E7020. The matched DefaultModule<7> factory constructor at
// 0x005E6220 installs vtable 0x011120CC, whose slot zero reaches this wrapper
// through ILT 0x000360A2. The wrapper calls its destructor through ILT 0x00043612.
namespace FXParticleSystem
{
template<int Category> class DefaultModule
{
public:
    virtual ~DefaultModule();
private:
    unsigned char m_data[0x1c];
};

typedef DefaultModule<7> DefaultModule7;

DefaultModule7 *MakeDefaultModule7()
{
    return new DefaultModule7;
}

void DeleteDefaultModule7(DefaultModule7 *object)
{
    delete object;
}
}
