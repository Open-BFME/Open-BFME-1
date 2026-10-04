// cl: /EHsc /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// The vtable-pointer reset sequence a destructor emits for a module template
// whose three subobjects sit at +0x00, +0x04 and +0x08.  The vftables are the
// base classes' and are named here because the compiler cannot: the header
// defines the bases in other translation units, so a reconstructed class would
// resolve the stores to whatever address the linker gave a local vftable
// instead of retail's.
//
//   +0x00  ModuleTemplate                 ??_7ModuleTemplate@FXParticleSystem@@6B@
//                                          0x01073758
//   +0x04  CategoryModuleInfo<Category>   comdat vftable
//                                          0x0110F9AC
//   +0x08  <Tag>EmissionVolumeInfo        base vftable (Snapshot)
//                                          0x01073744
//
// FXPS_V is deliberately left undefined, as in the retail TU that carried this
// body, so the specialization's destructor mangles QAE@XZ (non-virtual).
#include "fx_particle_system.h"

// Each store below targets a base class' vftable by its retail name.  A
// vftable has no C++ spelling, so __identifier names retail's mangled symbol
// itself and the object references that symbol directly: no stand-in name and
// no linker alias directive.  Snapshot is complete here, so its declaration
// repeats the type the compiler already gave `const Snapshot::`vftable''
// (void (__cdecl *const [4])(void)); any other spelling is a redefinition.
extern "C" void (__cdecl *const __identifier("??_7Snapshot@@6B@")[4])(void);
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@QAE@XZ
//
// 0x005D65B0, 50 bytes.  The address carries two more ledger names; the
// evidence favours CylinderEmissionVolumeModuleTemplate, whose two deleting
// destructors (0x005D66D0, 0x005D6700, both matched) are the only callers of
// 0x005D65B0 in the image, and whose ctor/copy ctor/operator= sit either side
// of it.  This BOX specialization is claimed at 0x005DC1E0 under the same name
// spelled UAE@XZ.  The bodies are byte-identical, so all three names stay on
// this address; this file is the anchor TU the other two rows resolve through
// their object-symbol= note.
ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = (unsigned int)__identifier("??_7Snapshot@@6B@");

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@");
    *(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
