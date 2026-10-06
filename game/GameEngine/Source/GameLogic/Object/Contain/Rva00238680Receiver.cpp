// ?rva00238680@Rva00238680Receiver@@QAE_NPAVRva00238680Object@@@Z
// The served body has no named caller or installed vtable, so its owner stays
// address-derived. Calls use the matched Object and GameLogic ABI declarations.
// cl: /DNDEBUG /MD /EHs-c-

class Object
{
public:
    Object *bfmeResolveMeleeTarget(int);
};

// ILT 0x00043CED -> 0x000ED3B0, the matched radius-adjusted planar gap
// squared ?bfmeGapSq@Gen_000ED3B0@@QBEMPBV1@@Z (Bfme5NinetyEight.cpp); other
// matched callers reach it through the same view.
class Gen_000ED3B0
{
public:
    float bfmeGapSq(const Gen_000ED3B0 *other) const;
};

class Rva00238680Object
{
};

class GameLogic
{
public:
    Object *findObjectByID(int);
    char pad000[0x3C];
    unsigned m_frame; // +0x3C in AIAttackMeleeHordeWaitState_update.cpp
};

extern GameLogic *TheGameLogic;
#define Rva00238680Limit 10000.0f

class Rva00238680Receiver
{
public:
    char pad000[0x100];
    int objectIdAt100;
    unsigned limitAt104;
    bool rva00238680(Rva00238680Object *target);
};

bool Rva00238680Receiver::rva00238680(Rva00238680Object *target)
{
    if (target == 0)
    {
        return false;
    }
    else
    {
        if (objectIdAt100 == 0)
            return false;
        GameLogic *logic = TheGameLogic;
        if (logic->m_frame >= limitAt104)
            return false;
        Object *found = logic->findObjectByID(objectIdAt100);
        if (!found)
            return false;
        char close = ((Gen_000ED3B0 *)target)->bfmeGapSq(*(Gen_000ED3B0 **)((char *)this - 0xDC)) < Rva00238680Limit;
        Object *foundParent = found->bfmeResolveMeleeTarget(0);
        Object *targetParent = ((Object *)target)->bfmeResolveMeleeTarget(0);
        if (targetParent == foundParent)
            return true;
        return close;
    }
}
