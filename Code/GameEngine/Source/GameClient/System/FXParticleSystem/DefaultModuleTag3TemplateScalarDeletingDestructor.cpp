// cl: /O2
// Retail RVA 0x005DB150. Destructor ILT 0x00009C5A routes directly to the
// matched ConcreteModuleTemplate<DefaultModuleTag<3> > destructor at 0x005DB080.
namespace FXParticleSystem
{
template<int Category> class DefaultModuleTag;
template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x24];
};

typedef ConcreteModuleTemplate<DefaultModuleTag<3> > DefaultTag3Template;

DefaultTag3Template *MakeDefaultTag3Template()
{
    return new DefaultTag3Template;
}

void DeleteDefaultTag3Template(DefaultTag3Template *object)
{
    delete object;
}
}
