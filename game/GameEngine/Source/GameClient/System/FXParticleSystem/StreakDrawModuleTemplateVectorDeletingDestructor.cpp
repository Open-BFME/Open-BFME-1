// cl: /O2
// Open-BFME: StreakDrawModuleTemplate vector-deleting destructor, retail
// 0x005D8820 (84 bytes). Primary vtable 0x01110C90 slot zero routes here
// through ILT 0x00049742, and the wrapper calls destructor ILT 0x00038A1E.

void operator delete[](void *block);

namespace FXParticleSystem
{
class StreakDrawModuleTemplate
{
public:
    StreakDrawModuleTemplate();
    __declspec(noinline) virtual ~StreakDrawModuleTemplate();

private:
    unsigned char m_data[8];
};

StreakDrawModuleTemplate::~StreakDrawModuleTemplate()
{
}

// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this 0x0C-byte class.
StreakDrawModuleTemplate *MakeStreakDrawModuleTemplateArray(int count)
{
    return new StreakDrawModuleTemplate[count];
}

void DeleteStreakDrawModuleTemplateArray(StreakDrawModuleTemplate *array)
{
    delete[] array;
}
}
