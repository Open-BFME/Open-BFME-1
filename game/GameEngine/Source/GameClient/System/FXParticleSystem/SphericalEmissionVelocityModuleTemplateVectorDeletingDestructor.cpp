// cl: /O2
// Retail RVA 0x005D7480 is slot 0 of vtable 0x01110B24, which both
// SphericalEmissionVelocityModuleTemplate constructors install. Its element
// destructor operand is ILT 0x0003CC2C, which routes to the matched destructor
// at 0x005D7380; encoded element size is 0x18.
void operator delete[](void *block);

namespace FXParticleSystem
{
class SphericalEmissionVelocityModuleTemplate
{
public:
    virtual ~SphericalEmissionVelocityModuleTemplate();

private:
    unsigned char m_data[0x14];
};

SphericalEmissionVelocityModuleTemplate *MakeSphericalEmissionVelocityModuleTemplateArray()
{
    return new SphericalEmissionVelocityModuleTemplate[2];
}

void DeleteSphericalEmissionVelocityModuleTemplateArray(SphericalEmissionVelocityModuleTemplate *array)
{
    delete[] array;
}
}
