// cl: /O2
// Open-BFME: StreakDrawModuleInfo vector-deleting destructor, retail
// 0x005D8650 (84 bytes). Vtable 0x01110C78 slot zero routes here through
// ILT 0x0000CB8F, and the wrapper calls destructor ILT 0x00049CA1.

void operator delete[](void *block);

namespace FXParticleSystem
{
class StreakDrawModuleInfo
{
public:
    StreakDrawModuleInfo();
    __declspec(noinline) virtual ~StreakDrawModuleInfo();
};

StreakDrawModuleInfo::~StreakDrawModuleInfo()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this four-byte class.
StreakDrawModuleInfo *MakeStreakDrawModuleInfoArray(int count)
{
    return new StreakDrawModuleInfo[count];
}

void DeleteStreakDrawModuleInfoArray(StreakDrawModuleInfo *array)
{
    delete[] array;
}
}
