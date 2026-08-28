// cl: /DNDEBUG /MD /EHsc
//
// BFME's bridge module ABI passes the owning Object to Module::onObjectCreated.
// The public Generals headers still carry the older no-argument declaration,
// so this body uses the retail layout locally until that ABI declaration is
// reconciled in the shared header.

struct FlagPair
{
    bool m_first;
    bool m_second;
};

class FlagPairTarget;

class Gen002B2080
{
public:
    void handle(FlagPairTarget *target);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    virtual void slot00(); virtual void slot04();
    virtual void slot08(); virtual void slot0C();
    virtual bool slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24();
    virtual void applyFlags(const FlagPair &flags);
    virtual void slot2C(); virtual void slot30();
    virtual void slot34(); virtual void slot38();
    virtual void slot3C(); virtual void slot40();
    virtual void slot44(); virtual void slot48();
    virtual void slot4C(); virtual void slot50();
    virtual void slot54(); virtual void slot58();
    virtual void slot5C(); virtual void fillCoord(void *out);
    virtual void slot64(); virtual void slot68();
    virtual void fillReal(void *out); virtual void slot70();
    virtual void slot74(); virtual void slot78();
    virtual void slot7C(); virtual void slot80();
    virtual void slot84(); virtual void slot88();
    virtual void slot8C(); virtual void slot90();
};

class MidVirtualSlot90Receiver
{
public:
#define BFME_SLOT90_PAD(N) virtual void pad##N();
    BFME_SLOT90_PAD(00) BFME_SLOT90_PAD(01) BFME_SLOT90_PAD(02)
    BFME_SLOT90_PAD(03) BFME_SLOT90_PAD(04) BFME_SLOT90_PAD(05)
    BFME_SLOT90_PAD(06) BFME_SLOT90_PAD(07) BFME_SLOT90_PAD(08)
    BFME_SLOT90_PAD(09) BFME_SLOT90_PAD(10) BFME_SLOT90_PAD(11)
    BFME_SLOT90_PAD(12) BFME_SLOT90_PAD(13) BFME_SLOT90_PAD(14)
    BFME_SLOT90_PAD(15) BFME_SLOT90_PAD(16) BFME_SLOT90_PAD(17)
    BFME_SLOT90_PAD(18) BFME_SLOT90_PAD(19) BFME_SLOT90_PAD(20)
    BFME_SLOT90_PAD(21) BFME_SLOT90_PAD(22) BFME_SLOT90_PAD(23)
    BFME_SLOT90_PAD(24) BFME_SLOT90_PAD(25) BFME_SLOT90_PAD(26)
    BFME_SLOT90_PAD(27) BFME_SLOT90_PAD(28) BFME_SLOT90_PAD(29)
    BFME_SLOT90_PAD(30) BFME_SLOT90_PAD(31) BFME_SLOT90_PAD(32)
    BFME_SLOT90_PAD(33) BFME_SLOT90_PAD(34) BFME_SLOT90_PAD(35)
#undef BFME_SLOT90_PAD
    virtual void dispatch(const void *table, void *context, int flags);
};

extern void Rva0010C080(MidVirtualSlot90Receiver *receiver, void *context);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    float x;
    float y;
    float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeScaffoldBehavior.h
class BridgeScaffoldBehavior
{
public:
    virtual void onObjectCreated(Object *owner);

private:
    char moduleBase[0x20];
    int m_targetMotion;
    Coord3D m_createPos;
    Coord3D m_riseToPos;
    Coord3D m_buildPos;
    float m_lateralSpeed;
    float m_verticalSpeed;
    Coord3D m_targetPos;
};

// ?onObjectCreated@BridgeScaffoldBehavior@@UAEXPAVObject@@@Z
void BridgeScaffoldBehavior::onObjectCreated(Object *owner)
{
    ((Gen002B2080 *)this)->handle((FlagPairTarget *)owner);
    if (owner->slot10())
        return;

    FlagPair flags;
    flags.m_first = true;
    flags.m_second = true;
    owner->applyFlags(flags);
    Rva0010C080((MidVirtualSlot90Receiver *)owner, &m_targetMotion);
    owner->fillCoord(&m_createPos);
    owner->fillCoord(&m_riseToPos);
    owner->fillCoord(&m_buildPos);
    owner->fillReal(&m_lateralSpeed);
    owner->fillReal(&m_verticalSpeed);
    owner->fillCoord(&m_targetPos);
}
