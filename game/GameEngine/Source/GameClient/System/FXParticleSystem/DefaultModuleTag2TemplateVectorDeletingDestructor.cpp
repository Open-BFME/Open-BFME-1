// cl: /O2
// Retail RVA 0x005DB2D0. Scalar destructor ILT 0x0002DCE0 routes to the
// matched ConcreteModuleTemplate<DefaultModuleTag<2> > destructor at 0x005DB1F0.
void operator delete[](void *block);

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

DefaultTag2Template *MakeDefaultTag2TemplateArray()
{
    return new DefaultTag2Template[2];
}

void DeleteDefaultTag2TemplateArray(DefaultTag2Template *array)
{
    delete[] array;
}
}
