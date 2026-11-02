// cl: /O2
// Open-BFME: DefaultModuleTemplate<$01> scalar-deleting destructor, retail
// 0x005D8490 (30 bytes). Call thunk 0x00004F61 routes here and the wrapper
// calls the matched class destructor through ILT 0x0001E952. The matched
// constructor installs primary vtable 0x01110C50.

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<2>
{
public:
    // ??0?$DefaultModuleTemplate@$01@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // ??_G here without copies of the matched default or copy constructors.
    explicit DefaultModuleTemplate(int) {}
    virtual ~DefaultModuleTemplate();
};
}

// The complete destructor is the matched DestructorThunk row; a second
// strong definition here duplicated it.
// ?forceDefaultModuleTemplate01DeletingDestructor@@YAXXZ absent-from-retail
void forceDefaultModuleTemplate01DeletingDestructor()
{
    FXParticleSystem::DefaultModuleTemplate<2> value(0);
}
