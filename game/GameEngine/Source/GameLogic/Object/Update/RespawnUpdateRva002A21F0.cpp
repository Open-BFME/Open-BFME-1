// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame
// stlport

// Retail 0x002A21F0..0x002A22A8; RET at 0x002A22A7, then INT3 padding.
// Caller 0x002147E0 looks up the literal "RespawnUpdate" (VA 0x01085FFC)
// and passes that module to ILT 0x0001ABE5 -> this body. The method spelling
// and member meanings are unproven, so their names remain address-derived.
// The matched constructor confirms the module-data/object slots and +0x2C.
// Include the game Module header before UpdateModule: the generic sweep
// Module shim has different base offsets. Native game accessors reproduce
// retail module-data +4, Object +8, and UpdateModule extent 0x20.
// The Object update receives two references to ten-word condition masks.
#include "Lib/BaseType.h"
#include "Common/DisabledTypes.h"
#define OBJECT_TU_MEMBERS bool clearDisabled(DisabledType); void clearAndSetModelConditionFlags(const BitFlags<320> &, const BitFlags<320> &);
#include "GameEngine/Source/GameLogic/Object/object.h"
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

#include "GameEngine/Include/Common/Module.h"
#include "GameEngine/Include/GameLogic/Module/UpdateModule.h"

struct Rva002A21F0Data
{
    char m_pad00[12];
    _STL::bitset<304> m_mask0C;
    _STL::bitset<304> m_mask34;
};

class RespawnUpdate : public UpdateModule
{
public:
    void rva002A21F0();
private:
    char m_rva002A21F0Pad20[12];
    unsigned m_rva002A21F0Field2C;
    unsigned m_rva002A21F0Field30;
};

void RespawnUpdate::rva002A21F0()
{
    const Rva002A21F0Data *data =
        reinterpret_cast<const Rva002A21F0Data *>(getModuleData());
    Object *object = getObject();
    if (m_rva002A21F0Field2C)
    {
        {
            _STL::bitset<304> empty;
            object->clearAndSetModelConditionFlags(
                reinterpret_cast<const BitFlags<320> &>(data->m_mask0C),
                reinterpret_cast<const BitFlags<320> &>(empty));
        }
        {
            _STL::bitset<304> empty;
            object->clearAndSetModelConditionFlags(
                reinterpret_cast<const BitFlags<320> &>(data->m_mask34),
                reinterpret_cast<const BitFlags<320> &>(empty));
        }
        object->clearDisabled(static_cast<DisabledType>(4));
        setWakeFrame(object, UPDATE_SLEEP_FOREVER);
        m_rva002A21F0Field2C = 2;
        m_rva002A21F0Field30 = 0;
    }
}
