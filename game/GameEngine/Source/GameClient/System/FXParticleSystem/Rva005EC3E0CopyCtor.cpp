// ??0Rva005EC3E0@@QAE@ABV0@@Z
// cl: /DNDEBUG /MD /GX- /Ob2 /Igame/GameEngine/Source/GameClient/System/FXParticleSystem /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#include "fx_particle_system.h"
class Rva005EC4C0 {
public:
    Rva005EC4C0(const Rva005EC4C0 &other);
    char m_storage[0x1c];
};
extern "C" char __identifier("??_7T1Base_005EFD60@@6BDefaultColorModuleInfo@FXParticleSystem@@@")[];
extern "C" char __identifier("??_7T1Base_005EFD60@@6BT1A1_005DD290@@@")[];
extern "C" char __identifier("??_7T1Base_005EFD60@@6BT1P1_005EFD60@@@")[];
extern "C" char __identifier("??_7T1Base_005EFD60@@6BT1P2_005EFD60@@@")[];
extern "C" char __identifier("??_7T4Derived_005EFD10@@6BT1A1_005DD290@@@")[];
extern "C" char __identifier("??_7T4Derived_005EFD10@@6BT4A2_01073760@@@")[];
extern "C" char __identifier("??_7T4Derived_005EFD10@@6BT4A2_0111081C@@@")[];
class Rva005EC3E0 {
public:
    Rva005EC3E0(const Rva005EC3E0 &other);
    char m_storage[0xac];
};
// Ported from Open BFME 2 Code/GameEngine/Source/GameClient/System/FXParticleSystem/DefaultModuleTemplate01InlineCopyCtors.cpp.
Rva005EC3E0::Rva005EC3E0(const Rva005EC3E0 &that)
{
    const void *src = &that;
    ((Rva005EC4C0 *)this)->Rva005EC4C0::Rva005EC4C0(*(const Rva005EC4C0 *)src);
    FXParticleSystem::DefaultColorModuleInfo *sub =
        (FXParticleSystem::DefaultColorModuleInfo *)((char *)this + 0x1c);
    *(void **)this = __identifier("??_7T4Derived_005EFD10@@6BT1A1_005DD290@@@");
    *(void **)((char *)this + 0x14) = __identifier("??_7T4Derived_005EFD10@@6BT4A2_0111081C@@@");
    *(void **)((char *)this + 0x18) = __identifier("??_7T4Derived_005EFD10@@6BT4A2_01073760@@@");
    const void *sub_src = src ? (const char *)src + 0x1c : 0;
    sub->DefaultColorModuleInfo::DefaultColorModuleInfo(*(const FXParticleSystem::DefaultColorModuleInfo *)sub_src);
    *(void **)this = __identifier("??_7T1Base_005EFD60@@6BT1A1_005DD290@@@");
    *(void **)((char *)this + 0x14) = __identifier("??_7T1Base_005EFD60@@6BT1P1_005EFD60@@@");
    *(void **)((char *)this + 0x18) = __identifier("??_7T1Base_005EFD60@@6BT1P2_005EFD60@@@");
    *(void **)((char *)this + 0x1c) = __identifier("??_7T1Base_005EFD60@@6BDefaultColorModuleInfo@FXParticleSystem@@@");
}
