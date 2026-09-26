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
    __declspec(noinline) virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<7>::~DefaultModuleTemplate()
{
}
}
