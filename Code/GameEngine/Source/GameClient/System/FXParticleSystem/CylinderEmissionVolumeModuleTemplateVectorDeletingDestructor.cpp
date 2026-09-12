// cl: /O2
// Retail RVA 0x005D6700. The wrapper's scalar-destructor operand is ILT
// 0x00012968, which routes directly to the matched destructor at 0x005D65B0.
void operator delete[](void *block);

namespace FXParticleSystem
{
class CylinderEmissionVolumeModuleTemplate
{
public:
    virtual ~CylinderEmissionVolumeModuleTemplate();

private:
    unsigned char m_data[0x20];
};

CylinderEmissionVolumeModuleTemplate *MakeCylinderEmissionVolumeModuleTemplateArray()
{
    return new CylinderEmissionVolumeModuleTemplate[2];
}

void DeleteCylinderEmissionVolumeModuleTemplateArray(CylinderEmissionVolumeModuleTemplate *array)
{
    delete[] array;
}
}
