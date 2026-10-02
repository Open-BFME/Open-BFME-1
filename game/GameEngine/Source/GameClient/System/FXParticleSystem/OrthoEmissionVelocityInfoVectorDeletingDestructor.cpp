// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x005D6EC0. The wrapper's scalar-destructor operand is ILT
// 0x000346BC, which routes directly to the matched destructor at 0x005D6D90.
#include "fx_particle_system.h"

void operator delete[](void *block);

namespace FXParticleSystem
{
OrthoEmissionVelocityInfo *MakeOrthoEmissionVelocityInfoArray()
{
    return new OrthoEmissionVelocityInfo[2];
}

void DeleteOrthoEmissionVelocityInfoArray(OrthoEmissionVelocityInfo *array)
{
    delete[] array;
}
}
