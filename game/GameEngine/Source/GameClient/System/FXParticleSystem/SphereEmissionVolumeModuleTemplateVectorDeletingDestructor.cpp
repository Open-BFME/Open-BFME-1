// cl: /O2
// Retail RVA 0x005D6380. The wrapper's scalar-destructor operand is ILT
// 0x00029BEA, which routes directly to the matched destructor at 0x005D6280.
void operator delete[](void *block);

namespace FXParticleSystem
{
class SphereEmissionVolumeModuleTemplate
{
public:
    virtual ~SphereEmissionVolumeModuleTemplate();

private:
    unsigned char m_data[0x10];
};

SphereEmissionVolumeModuleTemplate *MakeSphereEmissionVolumeModuleTemplateArray()
{
    return new SphereEmissionVolumeModuleTemplate[2];
}

void DeleteSphereEmissionVolumeModuleTemplateArray(SphereEmissionVolumeModuleTemplate *array)
{
    delete[] array;
}
}
