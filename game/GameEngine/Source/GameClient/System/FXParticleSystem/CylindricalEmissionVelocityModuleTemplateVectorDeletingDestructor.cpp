// cl: /O2
// Retail RVA 0x005D7A10. The wrapper's scalar-destructor operand is ILT
// 0x0004099E, which routes directly to the matched destructor at 0x005D78F0.
void operator delete[](void *block);

namespace FXParticleSystem
{
class CylindricalEmissionVelocityModuleTemplate
{
public:
    virtual ~CylindricalEmissionVelocityModuleTemplate();

private:
    unsigned char m_data[0x20];
};

CylindricalEmissionVelocityModuleTemplate *MakeCylindricalEmissionVelocityModuleTemplateArray()
{
    return new CylindricalEmissionVelocityModuleTemplate[2];
}

void DeleteCylindricalEmissionVelocityModuleTemplateArray(CylindricalEmissionVelocityModuleTemplate *array)
{
    delete[] array;
}
}
