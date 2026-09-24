// AICommandInterface::aiDoCommand body recovered at 0x002C2E30.
// GiantBirdAIUpdate's constructor at 0x002C2430 installs vtable 0x010C7E68
// at its +0x20 subobject. Slot 0 reaches this body through thunk 0x00005DA8.
// The full owner type is not established, so the receiver view keeps the RVA.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "GameLogic/AI.h"

class Rva002BC470StateAction
{
public:
    void run(void *first, void *second);
};
class Rva002BC540StateAction
{
public:
    void run(void *first, void *second, unsigned char third);
};
class Rva002BC4E0StateAction
{
public:
    void run(void *first, void *second);
};
class Rva002BC670StateAction
{
public:
    void run(void *first, void *second);
};

class GiantBirdAIUpdate
{
public:
    void followWaypointPathRva002C2C10(const Waypoint *waypoint, Bool asTeam,
        CommandSourceType source);
};

class AIUpdateInterface
{
public:
    // Call-only view: retail passes the same secondary-subobject this pointer
    // directly to the already-matched dispatcher at 0x00277780.
    virtual void aiDoCommand(const AICommandParms *parms);
};

class Rva002C2E30Primary
{
public:
    virtual void slot00() = 0;
    virtual void slot004() = 0;
    virtual void slot008() = 0;
    virtual void slot00c() = 0;
    virtual void slot010() = 0;
    virtual void slot014() = 0;
    virtual void slot018() = 0;
    virtual void slot01c() = 0;
    virtual void slot020() = 0;
    virtual void slot024() = 0;
    virtual void slot028() = 0;
    virtual void slot02c() = 0;
    virtual void slot030() = 0;
    virtual void slot034() = 0;
    virtual void slot038() = 0;
    virtual void slot03c() = 0;
    virtual void slot040() = 0;
    virtual void slot044() = 0;
    virtual void slot048() = 0;
    virtual void slot04c() = 0;
    virtual void slot050() = 0;
    virtual void slot054() = 0;
    virtual void slot058() = 0;
    virtual void slot05c() = 0;
    virtual void slot060() = 0;
    virtual void slot064() = 0;
    virtual void slot068() = 0;
    virtual void slot06c() = 0;
    virtual void slot070() = 0;
    virtual void slot074() = 0;
    virtual void slot078() = 0;
    virtual void slot07c() = 0;
    virtual void slot080() = 0;
    virtual void slot084() = 0;
    virtual void slot088() = 0;
    virtual void slot08c() = 0;
    virtual void slot090() = 0;
    virtual void slot094() = 0;
    virtual void slot098() = 0;
    virtual void slot9c(unsigned int source) = 0;
    virtual void slot0a0() = 0;
    virtual void slot0a4() = 0;
    virtual void slot0a8() = 0;
    virtual void slot0ac() = 0;
    virtual void slot0b0() = 0;
    virtual void slot0b4() = 0;
    virtual void slot0b8() = 0;
    virtual void slot0bc() = 0;
    virtual void slot0c0() = 0;
    virtual void slot0c4() = 0;
    virtual void slot0c8() = 0;
    virtual void slot0cc() = 0;
    virtual void slot0d0() = 0;
    virtual void slot0d4() = 0;
    virtual void slot0d8() = 0;
    virtual void slot0dc() = 0;
    virtual void slot0e0() = 0;
    virtual void slot0e4() = 0;
    virtual void slot0e8() = 0;
    virtual void slot0ec() = 0;
    virtual void slot0f0() = 0;
    virtual void slot0f4() = 0;
    virtual void slot0f8() = 0;
    virtual void slot0fc() = 0;
    virtual void slot100() = 0;
    virtual void slot104() = 0;
    virtual void slot108() = 0;
    virtual void slot10c() = 0;
    virtual void slot110() = 0;
    virtual void slot114() = 0;
    virtual void slot118() = 0;
    virtual void slot11c() = 0;
    virtual void slot120() = 0;
    virtual void slot124() = 0;
    virtual void slot128() = 0;
    virtual void slot12c() = 0;
    virtual void slot130() = 0;
    virtual void slot134() = 0;
    virtual void slot138() = 0;
    virtual void slot13c() = 0;
    virtual void slot140() = 0;
    virtual void slot144() = 0;
    virtual void slot148() = 0;
    virtual void slot14c() = 0;
    virtual void slot150() = 0;
    virtual void slot154() = 0;
    virtual void slot158() = 0;
    virtual void slot15c() = 0;
    virtual void slot160() = 0;
    virtual void slot164() = 0;
    virtual void slot168() = 0;
    virtual void slot16c() = 0;
    virtual void slot170() = 0;
    virtual void slot174() = 0;
    virtual void slot178() = 0;
    virtual void slot17c() = 0;
    virtual void slot180() = 0;
    virtual void slot184() = 0;
    virtual void slot188() = 0;
    virtual void slot18c() = 0;
    virtual void slot190() = 0;
    virtual void slot194() = 0;
    virtual void slot198() = 0;
    virtual void slot19c() = 0;
    virtual void slot1a0() = 0;
    virtual void slot1a4() = 0;
    virtual void slot1a8() = 0;
    virtual void slot1ac() = 0;
    virtual void slot1b0() = 0;
    virtual void slot1b4() = 0;
    virtual void slot1b8() = 0;
    virtual void slot1bc() = 0;
    virtual void slot1c0() = 0;
    virtual void slot1c4() = 0;
    virtual void slot1c8() = 0;
    virtual void slot1cc() = 0;
    virtual void slot1d0() = 0;
    virtual void slot1d4() = 0;
    virtual void slot1d8() = 0;
    virtual void slot1dc() = 0;
    virtual void slot1e0() = 0;
    virtual void slot1e4() = 0;
    virtual void slot1e8() = 0;
    virtual void slot1ec() = 0;
    virtual void slot1f0() = 0;
    virtual void slot1f4() = 0;
    virtual void slot1f8() = 0;
    virtual void slot1fc() = 0;
    virtual void slot200() = 0;
    virtual void slot204() = 0;
    virtual void slot208() = 0;
    virtual void slot20c() = 0;
    virtual bool slot210(const AICommandParms *parms) const = 0;
private:
    char m_padding004[0x1c];
};

class Rva002C2E30CommandSubobject : public AICommandInterface
{
public:
    virtual void aiDoCommand(const AICommandParms *parms);

private:
    char m_unmodelled_004[0x328];
    AICommandParmsStorage m_pendingCommand;
    char m_unmodelled_3c0[0xb0];
    unsigned char m_pendingFlag470;
};

class Rva002C2E30OwnerLayout : public Rva002C2E30Primary,
    public Rva002C2E30CommandSubobject
{
};

void Rva002C2E30CommandSubobject::aiDoCommand(const AICommandParms *parms)
{
    Rva002C2E30Primary *owner = reinterpret_cast<Rva002C2E30Primary *>(
        (char *)this - 0x20);
    if (!owner->slot210(parms))
        return;

    if (m_pendingFlag470)
    {
        m_pendingCommand.store(*parms);
        return;
    }

    ((Int *)((char *)this + 0x32c))[0] = -1;
    // This order follows the retail jump blocks so MSVC 7.1 emits them at
    // the same addresses as the command table.
    switch (parms->m_cmd)
    {
    case 0x00:
        ((Rva002BC470StateAction *)owner)->run((void *)&parms->m_pos,
            (void *)(unsigned int)parms->m_cmdSource);
        return;
    case 0x3f:
        ((Rva002BC540StateAction *)owner)->run(parms->m_obj,
            (void *)(unsigned int)parms->m_cmdSource, 1);
        return;
    case 0x0b:
    case 0x0c:
    case 0x39:
        ((Rva002BC540StateAction *)owner)->run(parms->m_obj,
            (void *)(unsigned int)parms->m_cmdSource, 0);
        return;
    case 0x23:
        ((Rva002BC670StateAction *)owner)->run((void *)parms->m_polygon,
            (void *)(unsigned int)parms->m_cmdSource);
        return;
    case 0x12:
        owner->slot9c((unsigned int)parms->m_cmdSource);
        return;
    case 0x06:
    case 0x32:
        ((GiantBirdAIUpdate *)(void *)owner)->followWaypointPathRva002C2C10(
            parms->m_waypoint, false, parms->m_cmdSource);
        return;
    case 0x07:
    case 0x33:
        ((GiantBirdAIUpdate *)(void *)owner)->followWaypointPathRva002C2C10(
            parms->m_waypoint, true, parms->m_cmdSource);
        return;
    case 0x0f:
        ((Rva002BC4E0StateAction *)owner)->run((void *)&parms->m_pos,
            (void *)(unsigned int)parms->m_cmdSource);
        return;
    case 0x0e:
    case 0x40:
        return;
    default:
        ((unsigned int *)((char *)owner + 0x3f0))[0] &= ~1u;
        ((AIUpdateInterface *)(void *)this)->AIUpdateInterface::aiDoCommand(parms);
        return;
    }
}
