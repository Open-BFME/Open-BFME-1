// cl: /O2
// Retail RVA 0x005DB460. Destructor ILT 0x00014ED4 routes directly to the
// matched ConcreteModuleTemplate<DefaultModuleTag<7> > destructor at 0x005DB3B0.
namespace FXParticleSystem
{
template<int Category> class DefaultModuleTag;
template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x4C];
};

typedef ConcreteModuleTemplate<DefaultModuleTag<7> > DefaultTag7Template;

DefaultTag7Template *MakeDefaultTag7Template()
{
    return new DefaultTag7Template;
}

void DeleteDefaultTag7Template(DefaultTag7Template *object)
{
    delete object;
}
}
