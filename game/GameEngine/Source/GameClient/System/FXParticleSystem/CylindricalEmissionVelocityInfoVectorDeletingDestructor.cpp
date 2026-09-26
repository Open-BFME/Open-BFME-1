// cl: /O2
// Retail RVA 0x005D77F0. The wrapper's scalar-destructor operand is ILT
// 0x00038C94, which routes directly to the matched destructor at 0x005D7700.
void operator delete[](void *block);

namespace FXParticleSystem
{
class CylindricalEmissionVelocityInfo
{
public:
    virtual ~CylindricalEmissionVelocityInfo();

private:
    unsigned char m_data[0x18];
};

CylindricalEmissionVelocityInfo *MakeCylindricalEmissionVelocityInfoArray()
{
    return new CylindricalEmissionVelocityInfo[2];
}

void DeleteCylindricalEmissionVelocityInfoArray(CylindricalEmissionVelocityInfo *array)
{
    delete[] array;
}
}
