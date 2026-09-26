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
    __declspec(noinline) virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<0>::~DefaultModuleTemplate()
{
}
}
