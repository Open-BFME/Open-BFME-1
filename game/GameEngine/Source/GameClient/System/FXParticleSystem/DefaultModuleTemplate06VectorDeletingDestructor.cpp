// cl: /O2
// Open-BFME: DefaultModuleTemplate<$06> vector-deleting destructor, retail
// 0x005DC820 (84 bytes). Primary vtable 0x0111101C slot zero routes here
// through ILT 0x0004000C, and the wrapper calls destructor ILT 0x00017C1A.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<7>
{
public:
    DefaultModuleTemplate();
    __declspec(noinline) virtual ~DefaultModuleTemplate();

private:
    unsigned char m_data[0x4C];
};

DefaultModuleTemplate<7>::~DefaultModuleTemplate()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this 0x50-byte class.
DefaultModuleTemplate<7> *MakeDefaultModuleTemplate06Array(int count)
{
    return new DefaultModuleTemplate<7>[count];
}

void DeleteDefaultModuleTemplate06Array(DefaultModuleTemplate<7> *array)
{
    delete[] array;
}
}
