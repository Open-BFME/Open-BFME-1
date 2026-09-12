// cl: /O2
// Retail RVA 0x005BD870. The wrapper's scalar-destructor operand is ILT
// 0x0003CF47, which routes to the matched destructor at 0x005BD810.
void operator delete[](void *block);

namespace FXParticleSystem
{
class EmissionVelocityInfo
{
public:
    virtual ~EmissionVelocityInfo();
};

EmissionVelocityInfo *MakeEmissionVelocityInfoArray()
{ return new EmissionVelocityInfo[2]; }

void DeleteEmissionVelocityInfoArray(EmissionVelocityInfo *array)
{ delete[] array; }
}
