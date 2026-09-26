// cl: /O2
// Retail RVA 0x005D7280. The wrapper's scalar-destructor operand is ILT
// 0x0001BFDB, which routes directly to the matched destructor at 0x005D71D0.
void operator delete[](void *block);

namespace FXParticleSystem
{
class SphericalEmissionVelocityInfo
{
public:
    virtual ~SphericalEmissionVelocityInfo();

private:
    unsigned char m_data[0x0C];
};

SphericalEmissionVelocityInfo *MakeSphericalEmissionVelocityInfoArray()
{
    return new SphericalEmissionVelocityInfo[2];
}

void DeleteSphericalEmissionVelocityInfoArray(SphericalEmissionVelocityInfo *array)
{
    delete[] array;
}
}
