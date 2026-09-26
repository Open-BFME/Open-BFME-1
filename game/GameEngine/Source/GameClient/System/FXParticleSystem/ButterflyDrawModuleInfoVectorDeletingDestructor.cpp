// cl: /O2
// Open-BFME: ButterflyDrawModuleInfo vector-deleting destructor, retail
// 0x005D8BB0 (84 bytes). Vtable 0x01110CF8 slot zero routes here through
// ILT 0x000340A4, and the wrapper calls destructor ILT 0x00001C08.

void operator delete[](void *block);

namespace FXParticleSystem
{
class ButterflyDrawModuleInfo
{
public:
    ButterflyDrawModuleInfo();
    __declspec(noinline) virtual ~ButterflyDrawModuleInfo();
};

ButterflyDrawModuleInfo::~ButterflyDrawModuleInfo()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this four-byte class.
ButterflyDrawModuleInfo *MakeButterflyDrawModuleInfoArray(int count)
{
    return new ButterflyDrawModuleInfo[count];
}

void DeleteButterflyDrawModuleInfoArray(ButterflyDrawModuleInfo *array)
{
    delete[] array;
}
}
