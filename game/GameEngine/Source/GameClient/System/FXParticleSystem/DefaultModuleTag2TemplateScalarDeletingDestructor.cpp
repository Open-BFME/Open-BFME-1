// cl: /O2
// Retail RVA 0x005DB2A0. Destructor ILT 0x0002DCE0 routes directly to the
// matched ConcreteModuleTemplate<DefaultModuleTag<2> > destructor at 0x005DB1F0.
namespace FXParticleSystem
{
template<int Category> class DefaultModuleTag;
template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x48];
};

typedef ConcreteModuleTemplate<DefaultModuleTag<2> > DefaultTag2Template;

DefaultTag2Template *MakeDefaultTag2Template()
{
    return new DefaultTag2Template;
}

void DeleteDefaultTag2Template(DefaultTag2Template *object)
{
    delete object;
}
}
