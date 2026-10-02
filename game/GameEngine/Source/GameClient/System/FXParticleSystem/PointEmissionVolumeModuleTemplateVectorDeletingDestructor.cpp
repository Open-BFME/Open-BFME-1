// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// BFME PointEmissionVolumeModuleTemplate vector-deleting destructor at retail
// RVA 0x005D59E0. The scalar destructor is matched at 0x005D58F0 and this
// wrapper reaches it through ILT 0x00041F56.

#include "fx_particle_system.h"

void operator delete[](void *block);

namespace FXParticleSystem
{
PointEmissionVolumeModuleTemplate *MakePointEmissionVolumeModuleTemplateArray()
{
	return new PointEmissionVolumeModuleTemplate[2];
}

void DeletePointEmissionVolumeModuleTemplateArray(PointEmissionVolumeModuleTemplate *array)
{
	delete[] array;
}
}
