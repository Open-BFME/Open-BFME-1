// cl: /O2
// Retail RVA 0x005D7600. The wrapper's scalar-destructor operand is ILT
// 0x0002A08B, which routes directly to the matched destructor at 0x005D7520.
void operator delete[](void *block);

namespace FXParticleSystem
{
class HemisphericalEmissionVelocityModuleTemplate
{
public:
    virtual ~HemisphericalEmissionVelocityModuleTemplate();

private:
    unsigned char m_data[0x14];
};

HemisphericalEmissionVelocityModuleTemplate *MakeHemisphericalEmissionVelocityModuleTemplateArray()
{
    return new HemisphericalEmissionVelocityModuleTemplate[2];
}

void DeleteHemisphericalEmissionVelocityModuleTemplateArray(HemisphericalEmissionVelocityModuleTemplate *array)
{
    delete[] array;
}
}
