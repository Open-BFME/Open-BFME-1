// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"
#include "subsystem_interface.h"

// Opaque views of two subsystem forwarding entries. The inherited init
// declaration supplies the independently established slot-one ABI.
class Rva00880DF0 : public SubsystemInterface
{
public:
    virtual void method();
};
void Rva00880DF0::method() { init(); }

class Rva009F2620 : public SubsystemInterface
{
public:
    virtual void method();
};
void Rva009F2620::method() { init(); }
