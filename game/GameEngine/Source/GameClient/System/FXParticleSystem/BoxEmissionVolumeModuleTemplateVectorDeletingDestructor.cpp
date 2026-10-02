// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x005D60B0. The wrapper's scalar-destructor operand is ILT
// 0x0001DCA0, which routes directly to the matched destructor at 0x005D5F80.
#include "fx_particle_system.h"

void operator delete[](void *block);

namespace FXParticleSystem
{
BoxEmissionVolumeModuleTemplate *MakeBoxEmissionVolumeModuleTemplateArray()
{
    return new BoxEmissionVolumeModuleTemplate[2];
}

void DeleteBoxEmissionVolumeModuleTemplateArray(BoxEmissionVolumeModuleTemplate *array)
{
    delete[] array;
}
}
