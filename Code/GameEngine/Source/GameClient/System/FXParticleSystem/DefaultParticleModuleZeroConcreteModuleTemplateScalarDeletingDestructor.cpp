// cl: /O2
// Retail RVA 0x005DAFE0. Destructor ILT 0x00032C95 routes directly to the
// matched ConcreteModuleTemplate<DefaultModuleTag<0> > destructor at 0x005DAF30.
namespace FXParticleSystem
{
template<int Category> class DefaultModuleTag;

template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[8];
};

typedef ConcreteModuleTemplate<DefaultModuleTag<0> > DefaultModuleZeroTemplate;

DefaultModuleZeroTemplate *MakeDefaultModuleZeroTemplate()
{
    return new DefaultModuleZeroTemplate;
}

void DeleteDefaultModuleZeroTemplate(DefaultModuleZeroTemplate *object)
{
    delete object;
}
}
