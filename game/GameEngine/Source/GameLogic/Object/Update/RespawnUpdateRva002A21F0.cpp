// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame
// stlport

// Retail 0x002A21F0..0x002A22A8; RET at 0x002A22A7, then INT3 padding.
// Caller 0x002147E0 looks up the literal "RespawnUpdate" (VA 0x01085FFC)
// and passes that module to ILT 0x0001ABE5 -> this body. The method spelling
// and member meanings are unproven, so their names remain address-derived.
// The matched constructor confirms the module-data/object slots and +0x2C.
// Existing BfmeThingVKP::bfmeSetVKP is the one ledger identity at 0x001C7720.
// Its two integer ABI slots carry addresses of 40-byte condition masks.
// This caller reuses that exact signature without claiming another identity.
#include "Lib/BaseType.h"
#include "Common/DisabledTypes.h"
#define OBJECT_TU_MEMBERS bool clearDisabled(DisabledType);
#include "GameEngine/Source/GameLogic/Object/object.h"
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

class BfmeThingVKP
{
public:
    void bfmeSetVKP(int, int);
};

enum UpdateSleepTime
{
    UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModule
{
protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    char m_rva002A21F0Pad00[4];
    const void *m_rva002A21F0Data;
    Object *m_rva002A21F0Object;
    char m_rva002A21F0Pad0C[0x14];
};

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
        static_cast<const Rva002A21F0Data *>(m_rva002A21F0Data);
    Object *object = m_rva002A21F0Object;
    if (m_rva002A21F0Field2C)
    {
        {
            _STL::bitset<304> empty;
            reinterpret_cast<BfmeThingVKP *>(object)->bfmeSetVKP(
                reinterpret_cast<int>(&data->m_mask0C),
                reinterpret_cast<int>(&empty));
        }
        {
            _STL::bitset<304> empty;
            reinterpret_cast<BfmeThingVKP *>(object)->bfmeSetVKP(
                reinterpret_cast<int>(&data->m_mask34),
                reinterpret_cast<int>(&empty));
        }
        object->clearDisabled(static_cast<DisabledType>(4));
        setWakeFrame(object, UPDATE_SLEEP_FOREVER);
        m_rva002A21F0Field2C = 2;
        m_rva002A21F0Field30 = 0;
    }
}
