// cl: /O2
// Open-BFME: DefaultModuleTemplate<$0A> scalar-deleting destructor, retail
// 0x005D55F0 (30 bytes). Call thunk 0x0003F260 routes here and the wrapper
// calls the matched class destructor through ILT 0x0004791F. The matched
// constructor installs primary vtable 0x011108F8.

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<0>
{
public:
    // ??0?$DefaultModuleTemplate@$0A@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // ??_G here without copies of the matched default or copy constructors.
    explicit DefaultModuleTemplate(int) {}
    virtual ~DefaultModuleTemplate();
};
}

// The complete destructor is the matched DestructorThunk row; a second
// strong definition here duplicated it.
// ?forceDefaultModuleTemplate0ADeletingDestructor@@YAXXZ absent-from-retail
void forceDefaultModuleTemplate0ADeletingDestructor()
{
    FXParticleSystem::DefaultModuleTemplate<0> value(0);
}
