// cl: /O2
// Open-BFME: DefaultDrawModuleInfo vector-deleting destructor, retail
// 0x005D56F0 (84 bytes). Vtable 0x01110920 slot zero routes here through
// ILT 0x00007A90, and the wrapper calls destructor ILT 0x00008CBA.

void operator delete[](void *block);

namespace FXParticleSystem
{
class DefaultDrawModuleInfo
{
public:
    DefaultDrawModuleInfo();
    __declspec(noinline) virtual ~DefaultDrawModuleInfo();
};

DefaultDrawModuleInfo::~DefaultDrawModuleInfo()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this four-byte class.
DefaultDrawModuleInfo *MakeDefaultDrawModuleInfoArray(int count)
{
    return new DefaultDrawModuleInfo[count];
}

void DeleteDefaultDrawModuleInfoArray(DefaultDrawModuleInfo *array)
{
    delete[] array;
}
}
