// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// BFME FXParticleSystem::CategoryModuleTemplate<2> vector-deleting
// destructor at retail RVA 0x005BF510. The scalar destructor is matched at
// 0x005BF470 and the wrapper reaches it through ILT 0x00037E66.
void operator delete[](void *block);

#define FXPS_V virtual
#include "fx_particle_system.h"

namespace FXParticleSystem
{
// Owned by CategoryModuleTemplate01DestructorThunk.cpp and
// CategoryModuleTemplateBase01DestructorThunk.cpp.
template<> CategoryModuleTemplate<2>::~CategoryModuleTemplate();
template<> CategoryModuleTemplateBase<2>::~CategoryModuleTemplateBase();
// Matched out of line at 0x005BF450 (fx_particle_system.cpp); declared so
// new[] calls it instead of inlining it and emitting Base<2>'s vftable.
template<> CategoryModuleTemplate<2>::CategoryModuleTemplate();

CategoryModuleTemplate<2> *MakeCategoryModuleTemplate01Array()
{
	return new CategoryModuleTemplate<2>[2];
}

void DeleteCategoryModuleTemplate01Array(CategoryModuleTemplate<2> *array)
{
	delete[] array;
}
}
