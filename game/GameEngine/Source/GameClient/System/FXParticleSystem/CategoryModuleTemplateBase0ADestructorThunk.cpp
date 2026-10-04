// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: CategoryModuleTemplateBase<10> empty dual-vtbl dtor.
//
// The body below is empty: the two vtable stores are emitted by the compiler
// from the class hierarchy, so this TU references retail's vtable symbols
// directly instead of through extern "C" stand-ins plus a linker alias:
//   *(this + 4) = ??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@
//   *(this + 0) = ??_7ModuleTemplate@FXParticleSystem@@6B@
// (retail 0x005D850: test/jz null-base form, then the two stores and ret.)
//
// MSVC 7.1 mangles a template's non-type argument as $0<arg-1> in any TU that
// declares an explicit specialization (plain hex elsewhere), which is why this
// specialisation is written CategoryModuleTemplateBase<0> and inherits
// CategoryModuleInfo<0>: both spell the retail names
// ??1?$CategoryModuleTemplateBase@$0A@@FXParticleSystem@@UAE@XZ and
// ??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@. CategoryModuleInfo<0>
// and <10> are the same empty class, so the emitted vtable is retail's.

#include "fx_particle_system.h"

namespace FXParticleSystem
{

template <>
class __declspec(novtable) CategoryModuleTemplateBase<0> : public ModuleTemplate, public CategoryModuleInfo<0>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$0A@@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<0>::~CategoryModuleTemplateBase()
{
}

}
