// cl: /O2
// Retail RVA 0x005DE180. The wrapper's scalar-destructor operand is ILT
// 0x00044E31, which routes directly to the matched destructor at 0x005DDFE0.
void operator delete[](void *block);

namespace FXParticleSystem
{
class LifeEventModuleTemplate
{
public:
    virtual ~LifeEventModuleTemplate();

private:
    unsigned char m_data[0x20];
};

LifeEventModuleTemplate *MakeLifeEventModuleTemplateArray()
{
    return new LifeEventModuleTemplate[2];
}

void DeleteLifeEventModuleTemplateArray(LifeEventModuleTemplate *array)
{
    delete[] array;
}
}
