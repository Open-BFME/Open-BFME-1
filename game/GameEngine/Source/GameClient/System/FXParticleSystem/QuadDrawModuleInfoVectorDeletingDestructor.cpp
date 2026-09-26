// cl: /O2
// Open-BFME: QuadDrawModuleInfo vector-deleting destructor, retail
// 0x005D8900 (84 bytes). Vtable 0x01110CB8 slot zero routes here through
// ILT 0x00039329, and the wrapper calls destructor ILT 0x0001C5CB.

void operator delete[](void *block);

namespace FXParticleSystem
{
class QuadDrawModuleInfo
{
public:
    QuadDrawModuleInfo();
    __declspec(noinline) virtual ~QuadDrawModuleInfo();
};

QuadDrawModuleInfo::~QuadDrawModuleInfo()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this four-byte class.
QuadDrawModuleInfo *MakeQuadDrawModuleInfoArray(int count)
{
    return new QuadDrawModuleInfo[count];
}

void DeleteQuadDrawModuleInfoArray(QuadDrawModuleInfo *array)
{
    delete[] array;
}
}
