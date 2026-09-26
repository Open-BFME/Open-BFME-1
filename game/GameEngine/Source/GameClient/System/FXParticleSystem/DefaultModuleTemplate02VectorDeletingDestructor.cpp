// cl: /O2
// Open-BFME: DefaultModuleTemplate<$02> vector-deleting destructor, retail
// 0x005D8140 (84 bytes). Primary vtable 0x01110C24 slot zero routes here
// through ILT 0x0002CF34, and the wrapper calls destructor ILT 0x000271A6.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<3>
{
public:
    DefaultModuleTemplate();
    __declspec(noinline) virtual ~DefaultModuleTemplate();

private:
    unsigned char m_data[0x24];
};

DefaultModuleTemplate<3>::~DefaultModuleTemplate()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this 0x28-byte class.
DefaultModuleTemplate<3> *MakeDefaultModuleTemplate02Array(int count)
{
    return new DefaultModuleTemplate<3>[count];
}

void DeleteDefaultModuleTemplate02Array(DefaultModuleTemplate<3> *array)
{
    delete[] array;
}
}
