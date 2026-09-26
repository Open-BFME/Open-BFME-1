// cl: /O2
// Open-BFME: DefaultUpdateModuleInfo vector-deleting destructor, retail
// 0x005D8350 (84 bytes). Vtable 0x01110C38 slot zero routes here through
// ILT 0x00045F98, and the wrapper calls destructor ILT 0x00017242. Its
// encoded element size is 0x44 bytes.

void operator delete[](void *block);

namespace FXParticleSystem
{
class DefaultUpdateModuleInfo
{
public:
    DefaultUpdateModuleInfo();
    __declspec(noinline) virtual ~DefaultUpdateModuleInfo();

private:
    unsigned char m_data[0x40];
};

DefaultUpdateModuleInfo::~DefaultUpdateModuleInfo()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this 0x44-byte class.
DefaultUpdateModuleInfo *MakeDefaultUpdateModuleInfoArray(int count)
{
    return new DefaultUpdateModuleInfo[count];
}

void DeleteDefaultUpdateModuleInfoArray(DefaultUpdateModuleInfo *array)
{
    delete[] array;
}
}
