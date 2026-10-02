// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x005D7280. The wrapper's scalar-destructor operand is ILT
// 0x0001BFDB, which routes directly to the matched destructor at 0x005D71D0.
#include "fx_particle_system.h"

void operator delete[](void *block);

namespace FXParticleSystem
{
SphericalEmissionVelocityInfo *MakeSphericalEmissionVelocityInfoArray()
{
    return new SphericalEmissionVelocityInfo[2];
}

void DeleteSphericalEmissionVelocityInfoArray(SphericalEmissionVelocityInfo *array)
{
    delete[] array;
}
}
