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
    __declspec(noinline) virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<2>::~DefaultModuleTemplate()
{
}
}
