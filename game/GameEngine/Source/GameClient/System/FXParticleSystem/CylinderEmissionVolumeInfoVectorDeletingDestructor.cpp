// cl: /O2
// Retail RVA 0x005D64F0. The wrapper's scalar-destructor operand is ILT
// 0x0001ADB6, which routes directly to the matched destructor at 0x005D6420.
void operator delete[](void *block);

namespace FXParticleSystem
{
class CylinderEmissionVolumeInfo
{
public:
    virtual ~CylinderEmissionVolumeInfo();

private:
    unsigned char m_data[0x18];
};

CylinderEmissionVolumeInfo *MakeCylinderEmissionVolumeInfoArray()
{
    return new CylinderEmissionVolumeInfo[2];
}

void DeleteCylinderEmissionVolumeInfoArray(CylinderEmissionVolumeInfo *array)
{
    delete[] array;
}
}
