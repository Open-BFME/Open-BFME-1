// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x005D6380. The wrapper's scalar-destructor operand is ILT
// 0x00029BEA, which routes directly to the matched destructor at 0x005D6280.
#include "fx_particle_system.h"

void operator delete[](void *block);

namespace FXParticleSystem
{
SphereEmissionVolumeModuleTemplate *MakeSphereEmissionVolumeModuleTemplateArray()
{
    return new SphereEmissionVolumeModuleTemplate[2];
}

void DeleteSphereEmissionVolumeModuleTemplateArray(SphereEmissionVolumeModuleTemplate *array)
{
    delete[] array;
}
}
