// cl: /O2
// Retail RVA 0x005D60B0. The wrapper's scalar-destructor operand is ILT
// 0x0001DCA0, which routes directly to the matched destructor at 0x005D5F80.
void operator delete[](void *block);

namespace FXParticleSystem
{
class BoxEmissionVolumeModuleTemplate
{
public:
    virtual ~BoxEmissionVolumeModuleTemplate();

private:
    unsigned char m_data[0x18];
};

BoxEmissionVolumeModuleTemplate *MakeBoxEmissionVolumeModuleTemplateArray()
{
    return new BoxEmissionVolumeModuleTemplate[2];
}

void DeleteBoxEmissionVolumeModuleTemplateArray(BoxEmissionVolumeModuleTemplate *array)
{
    delete[] array;
}
}
