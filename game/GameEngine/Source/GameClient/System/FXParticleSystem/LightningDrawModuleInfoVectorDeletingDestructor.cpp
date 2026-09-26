// cl: /O2
// Open-BFME: LightningDrawModuleInfo vector-deleting destructor, retail
// 0x005D9030 (84 bytes). Vtable 0x01110D38 slot zero routes here through
// ILT 0x000232E5, and the wrapper calls destructor ILT 0x000121B1. Its
// encoded element size is 0x30 bytes.

void operator delete[](void *block);

namespace FXParticleSystem
{
class LightningDrawModuleInfo
{
public:
    LightningDrawModuleInfo();
    __declspec(noinline) virtual ~LightningDrawModuleInfo();

private:
    unsigned char m_data[0x2C];
};

LightningDrawModuleInfo::~LightningDrawModuleInfo()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this 0x30-byte class.
LightningDrawModuleInfo *MakeLightningDrawModuleInfoArray(int count)
{
    return new LightningDrawModuleInfo[count];
}

void DeleteLightningDrawModuleInfoArray(LightningDrawModuleInfo *array)
{
    delete[] array;
}
}
