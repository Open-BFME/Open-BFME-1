// cl: /O2
// Open-BFME: DefaultModuleTemplate<$06> scalar-deleting destructor, retail
// 0x005DEAB0 (30 bytes). Call thunk 0x0003EE46 routes here and the wrapper
// calls the matched class destructor through ILT 0x00017C1A. The matched
// constructor installs primary vtable 0x0111101C.

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<7>
{
public:
    // ??0?$DefaultModuleTemplate@$06@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // ??_G here without copies of the matched default or copy constructors.
    explicit DefaultModuleTemplate(int) {}
    virtual ~DefaultModuleTemplate();
};
}

// The complete destructor is the matched DestructorThunk row; a second
// strong definition here duplicated it.
// ?forceDefaultModuleTemplate06DeletingDestructor@@YAXXZ absent-from-retail
void forceDefaultModuleTemplate06DeletingDestructor()
{
    FXParticleSystem::DefaultModuleTemplate<7> value(0);
}
