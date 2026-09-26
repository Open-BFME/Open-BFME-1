// cl: /O2
// Open-BFME: DefaultModuleTemplate<$01> vector-deleting destructor, retail
// 0x005D84C0 (84 bytes). Primary vtable 0x01110C50 slot zero routes here
// through ILT 0x000150DC, and the wrapper calls destructor ILT 0x0001E952.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<2>
{
public:
    DefaultModuleTemplate();
    __declspec(noinline) virtual ~DefaultModuleTemplate();

private:
    unsigned char m_data[0x48];
};

DefaultModuleTemplate<2>::~DefaultModuleTemplate()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this 0x4C-byte class.
DefaultModuleTemplate<2> *MakeDefaultModuleTemplate01Array(int count)
{
    return new DefaultModuleTemplate<2>[count];
}

void DeleteDefaultModuleTemplate01Array(DefaultModuleTemplate<2> *array)
{
    delete[] array;
}
}
