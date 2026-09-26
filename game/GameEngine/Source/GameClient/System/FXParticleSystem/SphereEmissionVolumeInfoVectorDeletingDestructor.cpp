// cl: /O2
// Retail RVA 0x005D61D0. The wrapper's scalar-destructor operand is ILT
// 0x00028E9D, which routes directly to the matched destructor at 0x005D6140.
void operator delete[](void *block);

namespace FXParticleSystem
{
class SphereEmissionVolumeInfo
{
public:
    virtual ~SphereEmissionVolumeInfo();

private:
    unsigned char m_data[8];
};

SphereEmissionVolumeInfo *MakeSphereEmissionVolumeInfoArray()
{
    return new SphereEmissionVolumeInfo[2];
}

void DeleteSphereEmissionVolumeInfoArray(SphereEmissionVolumeInfo *array)
{
    delete[] array;
}
}
