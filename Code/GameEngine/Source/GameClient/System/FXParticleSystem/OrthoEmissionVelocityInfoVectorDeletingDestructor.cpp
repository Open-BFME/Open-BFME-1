// cl: /O2
// Retail RVA 0x005D6EC0. The wrapper's scalar-destructor operand is ILT
// 0x000346BC, which routes directly to the matched destructor at 0x005D6D90.
void operator delete[](void *block);

namespace FXParticleSystem
{
class OrthoEmissionVelocityInfo
{
public:
    virtual ~OrthoEmissionVelocityInfo();

private:
    unsigned char m_data[0x24];
};

OrthoEmissionVelocityInfo *MakeOrthoEmissionVelocityInfoArray()
{
    return new OrthoEmissionVelocityInfo[2];
}

void DeleteOrthoEmissionVelocityInfoArray(OrthoEmissionVelocityInfo *array)
{
    delete[] array;
}
}
