// cl: /O2
// Open-BFME: StreakDrawModuleInfo scalar-deleting destructor wrapper,
// retail 0x005D8620 (30 bytes). The wrapper calls destructor ILT 0x00049CA1;
// the matched constructor at 0x005F7EF0 installs vtable 0x01110C78 and the
// matched destructor at 0x005D85F0 resets the inherited vtable.

namespace FXParticleSystem
{
class StreakDrawModuleInfo
{
public:
    // ??0StreakDrawModuleInfo@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // the deleting destructor here without a copy of the matched destructor.
    explicit StreakDrawModuleInfo(int) {}
    virtual ~StreakDrawModuleInfo();
};

// The complete destructor is a matched row in another unit; a second strong
// definition here duplicated it.
// ?forceStreakDrawModuleInfoDeletingDestructor@FXParticleSystem@@YAXXZ absent-from-retail
void forceStreakDrawModuleInfoDeletingDestructor()
{
    StreakDrawModuleInfo value(0);
}
}
