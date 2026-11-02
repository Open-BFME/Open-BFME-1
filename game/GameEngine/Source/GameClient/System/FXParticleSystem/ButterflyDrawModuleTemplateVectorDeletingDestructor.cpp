// cl: /O2
// Open-BFME: ButterflyDrawModuleTemplate vector-deleting destructor, retail
// 0x005D8D80 (84 bytes). Primary vtable 0x01110D10 slot zero routes here
// through ILT 0x0002CE80, and the wrapper calls destructor ILT 0x0003BE8A.

void operator delete[](void *block);

namespace FXParticleSystem
{
class ButterflyDrawModuleTemplate
{
public:
    ButterflyDrawModuleTemplate();
    // ??0ButterflyDrawModuleTemplate@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // the deleting destructor here without a copy of the matched destructor.
    explicit ButterflyDrawModuleTemplate(int) {}
    virtual ~ButterflyDrawModuleTemplate();

private:
    unsigned char m_data[8];
};


// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this 0x0C-byte class.
ButterflyDrawModuleTemplate *MakeButterflyDrawModuleTemplateArray(int count)
{
    return new ButterflyDrawModuleTemplate[count];
}

void DeleteButterflyDrawModuleTemplateArray(ButterflyDrawModuleTemplate *array)
{
    delete[] array;
}

// The complete destructor is a matched row in another unit; a second strong
// definition here duplicated it.
// ?forceButterflyDrawModuleTemplateDeletingDestructor@FXParticleSystem@@YAXXZ absent-from-retail
void forceButterflyDrawModuleTemplateDeletingDestructor()
{
    ButterflyDrawModuleTemplate value(0);
}
}
