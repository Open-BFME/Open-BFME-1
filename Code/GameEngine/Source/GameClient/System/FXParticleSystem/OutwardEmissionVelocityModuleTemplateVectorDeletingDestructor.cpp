// cl: /O2
// Retail RVA 0x005D7E20. The wrapper's scalar-destructor operand is ILT
// 0x00033A91, which routes directly to the matched destructor at 0x005D7D00.
void operator delete[](void *block);

namespace FXParticleSystem
{
class OutwardEmissionVelocityModuleTemplate
{
public:
    virtual ~OutwardEmissionVelocityModuleTemplate();

private:
    unsigned char m_data[0x20];
};

OutwardEmissionVelocityModuleTemplate *MakeOutwardEmissionVelocityModuleTemplateArray()
{
    return new OutwardEmissionVelocityModuleTemplate[2];
}

void DeleteOutwardEmissionVelocityModuleTemplateArray(OutwardEmissionVelocityModuleTemplate *array)
{
    delete[] array;
}
}
