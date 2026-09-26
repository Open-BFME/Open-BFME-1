// cl: /O2
// Retail RVA 0x005DB180. Scalar destructor ILT 0x00009C5A routes to the
// matched ConcreteModuleTemplate<DefaultModuleTag<3> > destructor at 0x005DB080.
void operator delete[](void *block);

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

DefaultTag3Template *MakeDefaultTag3TemplateArray()
{
    return new DefaultTag3Template[2];
}

void DeleteDefaultTag3TemplateArray(DefaultTag3Template *array)
{
    delete[] array;
}
}
