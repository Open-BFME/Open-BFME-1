// cl: /O2
// Open-BFME: DefaultDrawModuleInfo scalar-deleting destructor wrapper,
// retail 0x005D56C0 (30 bytes). The wrapper calls destructor ILT 0x00008CBA;
// the matched constructor at 0x005F3090 installs vtable 0x01110920 and the
// matched destructor at 0x005D5690 resets the inherited vtable.

namespace FXParticleSystem
{
class DefaultDrawModuleInfo
{
public:
    __declspec(noinline) virtual ~DefaultDrawModuleInfo();
};

DefaultDrawModuleInfo::~DefaultDrawModuleInfo()
{
}
}
