// cl: /O2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: DefaultDrawModuleInfo vector-deleting destructor, retail
// 0x005D56F0 (84 bytes). Vtable 0x01110920 slot zero routes here through
// ILT 0x00007A90, and the wrapper calls destructor ILT 0x00008CBA.

#include "fx_particle_system.h"

void operator delete[](void *block);

namespace FXParticleSystem
{
// Non-retail helpers force MSVC 7.1 to materialize the compiler-generated
// vector-deleting destructor for this four-byte class.
DefaultDrawModuleInfo *MakeDefaultDrawModuleInfoArray(int count)
{
    return new DefaultDrawModuleInfo[count];
}

void DeleteDefaultDrawModuleInfoArray(DefaultDrawModuleInfo *array)
{
    delete[] array;
}
}
