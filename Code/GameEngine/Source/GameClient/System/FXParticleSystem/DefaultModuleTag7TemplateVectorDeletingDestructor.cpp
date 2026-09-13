// cl: /O2
// Retail RVA 0x005DB490. Scalar destructor ILT 0x00014ED4 routes to the
// matched ConcreteModuleTemplate<DefaultModuleTag<7> > destructor at 0x005DB3B0.
void operator delete[](void *block);

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

DefaultTag7Template *MakeDefaultTag7TemplateArray()
{
    return new DefaultTag7Template[2];
}

void DeleteDefaultTag7TemplateArray(DefaultTag7Template *array)
{
    delete[] array;
}
}
