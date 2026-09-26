// cl: /O2
// Retail RVA 0x005DAE90. Destructor ILT 0x0002F2A2 routes directly to the
// matched ConcreteModuleTemplate<DefaultModuleTag<1> > destructor at 0x005DADE0.
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

typedef ConcreteModuleTemplate<DefaultModuleTag<1> > DefaultModuleOneTemplate;

DefaultModuleOneTemplate *MakeDefaultModuleOneTemplate()
{
    return new DefaultModuleOneTemplate;
}

void DeleteDefaultModuleOneTemplate(DefaultModuleOneTemplate *object)
{
    delete object;
}
}
