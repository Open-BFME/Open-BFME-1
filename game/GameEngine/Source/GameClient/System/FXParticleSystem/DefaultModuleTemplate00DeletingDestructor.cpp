// cl: /O2
// Open-BFME: DefaultModuleTemplate<$00> scalar-deleting destructor, retail
// 0x005D5230 (30 bytes). Call thunk 0x0002BDB9 routes here and the wrapper
// calls the matched class destructor through ILT 0x0003F783. The matched
// constructor installs primary vtable 0x011108B8.

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<1>
{
public:
    // ??0?$DefaultModuleTemplate@$00@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // ??_G here without copies of the matched default or copy constructors.
    explicit DefaultModuleTemplate(int) {}
    virtual ~DefaultModuleTemplate();
};
}

// The complete destructor is the matched DestructorThunk row; a second
// strong definition here duplicated it.
// ?forceDefaultModuleTemplate00DeletingDestructor@@YAXXZ absent-from-retail
void forceDefaultModuleTemplate00DeletingDestructor()
{
    FXParticleSystem::DefaultModuleTemplate<1> value(0);
}
