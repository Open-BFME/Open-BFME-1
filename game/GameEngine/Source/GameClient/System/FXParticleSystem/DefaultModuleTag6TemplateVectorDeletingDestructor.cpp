// cl: /O2
// RVA 0x005D9E30: scalar destructor ILT 0x00040FDE routes to the
// matched ConcreteModuleTemplate<DefaultModuleTag<6> > destructor 0x005D9D80.
// The retail array destructor encodes a 12-byte element stride.
void operator delete[](void *block);

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

ConcreteModuleTemplate<DefaultModuleTag<6> > *MakeDefaultModuleTag6TemplateArray()
{
    return new ConcreteModuleTemplate<DefaultModuleTag<6> >[2];
}

void DeleteDefaultModuleTag6TemplateArray(ConcreteModuleTemplate<DefaultModuleTag<6> > *array)
{
    delete[] array;
}
}
