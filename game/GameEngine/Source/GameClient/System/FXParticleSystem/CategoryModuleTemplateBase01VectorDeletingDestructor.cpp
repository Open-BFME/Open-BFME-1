// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// BFME FXParticleSystem::CategoryModuleTemplateBase<2> vector-deleting
// destructor at retail RVA 0x005BF3E0. The scalar destructor is matched at
// 0x005BF350 and the wrapper reaches it through ILT 0x0000EAB1.

void operator delete[](void *block);

#define FXPS_V virtual
#include "fx_particle_system.h"

namespace FXParticleSystem
{
// Owned by CategoryModuleTemplateBase01DestructorThunk.cpp.
template<> CategoryModuleTemplateBase<2>::~CategoryModuleTemplateBase();

CategoryModuleTemplateBase<2> *MakeCategoryModuleTemplateBase01Array()
{
	return new CategoryModuleTemplateBase<2>[2];
}

void DeleteCategoryModuleTemplateBase01Array(CategoryModuleTemplateBase<2> *array)
{
	delete[] array;
}
}
