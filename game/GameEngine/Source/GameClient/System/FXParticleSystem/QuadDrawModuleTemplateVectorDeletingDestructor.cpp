// cl: /O2
// Open-BFME: QuadDrawModuleTemplate vector-deleting destructor, retail
// 0x005D8AD0 (84 bytes). Primary vtable 0x01110CD0 slot zero routes here
// through ILT 0x00021E0E, and the wrapper calls destructor ILT 0x000459F8.

void operator delete[](void *block);

namespace FXParticleSystem
{
class QuadDrawModuleTemplate
{
public:
    QuadDrawModuleTemplate();
    // ??0QuadDrawModuleTemplate@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // the deleting destructor here without a copy of the matched destructor.
    explicit QuadDrawModuleTemplate(int) {}
    virtual ~QuadDrawModuleTemplate();

private:
    unsigned char m_data[8];
};


// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this 0x0C-byte class.
QuadDrawModuleTemplate *MakeQuadDrawModuleTemplateArray(int count)
{
    return new QuadDrawModuleTemplate[count];
}

void DeleteQuadDrawModuleTemplateArray(QuadDrawModuleTemplate *array)
{
    delete[] array;
}

// The complete destructor is a matched row in another unit; a second strong
// definition here duplicated it.
// ?forceQuadDrawModuleTemplateDeletingDestructor@FXParticleSystem@@YAXXZ absent-from-retail
void forceQuadDrawModuleTemplateDeletingDestructor()
{
    QuadDrawModuleTemplate value(0);
}
}
