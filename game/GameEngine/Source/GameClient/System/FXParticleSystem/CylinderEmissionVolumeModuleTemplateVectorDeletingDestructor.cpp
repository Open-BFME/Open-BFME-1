// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x005D6700. The wrapper's scalar-destructor operand is ILT
// 0x00012968, which routes directly to the matched destructor at 0x005D65B0.
#include "fx_particle_system.h"

void operator delete[](void *block);

namespace FXParticleSystem
{
CylinderEmissionVolumeModuleTemplate *MakeCylinderEmissionVolumeModuleTemplateArray()
{
    return new CylinderEmissionVolumeModuleTemplate[2];
}

void DeleteCylinderEmissionVolumeModuleTemplateArray(CylinderEmissionVolumeModuleTemplate *array)
{
    delete[] array;
}
}
