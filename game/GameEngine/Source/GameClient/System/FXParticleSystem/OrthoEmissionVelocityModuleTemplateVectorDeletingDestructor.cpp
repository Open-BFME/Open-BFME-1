// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x005D70F0. The wrapper's scalar-destructor operand is ILT
// 0x00046E11, which routes directly to the matched destructor at 0x005D6FC0.
#include "fx_particle_system.h"

void operator delete[](void *block);

namespace FXParticleSystem
{
OrthoEmissionVelocityModuleTemplate *MakeOrthoEmissionVelocityModuleTemplateArray()
{
    return new OrthoEmissionVelocityModuleTemplate[2];
}

void DeleteOrthoEmissionVelocityModuleTemplateArray(OrthoEmissionVelocityModuleTemplate *array)
{
    delete[] array;
}
}
