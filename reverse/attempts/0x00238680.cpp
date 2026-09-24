// ?rva00238680@Rva00238680Receiver@@QAE_NPAVRva00238680Object@@@Z
// partial score=0.863 date=2026-09-24
// cl: /DNDEBUG /MD /EHs-c-

class Rva00238680Object
{
public:
    float rva000ED3B0GapSq(const Rva00238680Object *) const;
    Rva00238680Object *rva001CB020Resolve(int);
};

class Rva00238680GameLogic
{
public:
    Rva00238680Object *findObjectByID(int);
    char pad000[0x3C];
    unsigned countAt3C;
};

#define Rva00238680GameLogicGlobal (*(Rva00238680GameLogic **)0x012F0898)
#define Rva00238680Limit (*(float *)0x010AEBB8)

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
    if (!target)
        return false;
    if (!objectIdAt100)
        return false;
    Rva00238680GameLogic *logic = Rva00238680GameLogicGlobal;
    if (logic->countAt3C >= limitAt104)
        return false;
    Rva00238680Object *found = logic->findObjectByID(objectIdAt100);
    if (!found)
        return false;
    char close = target->rva000ED3B0GapSq(*(Rva00238680Object **)((char *)this - 0xDC)) < Rva00238680Limit;
    Rva00238680Object *foundParent = found->rva001CB020Resolve(0);
    Rva00238680Object *targetParent = target->rva001CB020Resolve(0);
    if (foundParent == targetParent)
        return true;
    return close;
}
