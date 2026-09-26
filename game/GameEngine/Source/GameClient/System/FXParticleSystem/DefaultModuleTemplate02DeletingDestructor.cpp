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
    __declspec(noinline) virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<3>::~DefaultModuleTemplate()
{
}
}
