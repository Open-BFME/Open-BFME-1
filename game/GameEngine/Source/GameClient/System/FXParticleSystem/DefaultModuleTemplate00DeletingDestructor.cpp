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
    __declspec(noinline) virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<1>::~DefaultModuleTemplate()
{
}
}
