// cl: /O2
// Open-BFME: DefaultModuleTemplate<$02> scalar-deleting destructor, retail
// 0x005D8110 (30 bytes). Call thunk 0x00048DF6 routes here and the wrapper
// calls the matched class destructor through ILT 0x000271A6. The matched
// constructor installs primary vtable 0x01110C24.

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<3>
{
public:
    // ??0?$DefaultModuleTemplate@$02@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // ??_G here without copies of the matched default or copy constructors.
    explicit DefaultModuleTemplate(int) {}
    virtual ~DefaultModuleTemplate();
};
}

// The complete destructor is the matched DestructorThunk row; a second
// strong definition here duplicated it.
// ?forceDefaultModuleTemplate02DeletingDestructor@@YAXXZ absent-from-retail
void forceDefaultModuleTemplate02DeletingDestructor()
{
    FXParticleSystem::DefaultModuleTemplate<3> value(0);
}
