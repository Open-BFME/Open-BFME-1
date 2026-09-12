// cl: /O2
// Retail RVA 0x005D7C00. The wrapper's scalar-destructor operand is ILT
// 0x000206CB, which routes directly to the matched destructor at 0x005D7B10.
void operator delete[](void *block);

namespace FXParticleSystem
{
class OutwardEmissionVelocityInfo
{
public:
    virtual ~OutwardEmissionVelocityInfo();

private:
    unsigned char m_data[0x18];
};

OutwardEmissionVelocityInfo *MakeOutwardEmissionVelocityInfoArray()
{
    return new OutwardEmissionVelocityInfo[2];
}

void DeleteOutwardEmissionVelocityInfoArray(OutwardEmissionVelocityInfo *array)
{
    delete[] array;
}
}
