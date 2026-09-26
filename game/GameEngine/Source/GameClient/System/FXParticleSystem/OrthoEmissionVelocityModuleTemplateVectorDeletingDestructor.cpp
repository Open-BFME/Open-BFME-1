// cl: /O2
// Retail RVA 0x005D70F0. The wrapper's scalar-destructor operand is ILT
// 0x00046E11, which routes directly to the matched destructor at 0x005D6FC0.
void operator delete[](void *block);

namespace FXParticleSystem
{
class OrthoEmissionVelocityModuleTemplate
{
public:
    virtual ~OrthoEmissionVelocityModuleTemplate();

private:
    unsigned char m_data[0x2C];
};

OrthoEmissionVelocityModuleTemplate *MakeOrthoEmissionVelocityModuleTemplateArray()
{
    return new OrthoEmissionVelocityModuleTemplate[2];
}

void DeleteOrthoEmissionVelocityModuleTemplateArray(OrthoEmissionVelocityModuleTemplate *array)
{
    delete[] array;
}
}
