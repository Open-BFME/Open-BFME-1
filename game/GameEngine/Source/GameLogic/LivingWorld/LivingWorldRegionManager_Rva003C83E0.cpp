// cl: /DNDEBUG /MD /O2 /EHsc
// Scratch reconstruction of retail 0x003C83E0. Physical callee routes use
// address-only ILT names; this method's lexical spelling remains unknown.

struct Rva003C83E0Pair { int first, second; };
class LivingWorldRegion;

class Rva003C83E0Campaign
{
public:
    char m_pad00[0x1c];
    unsigned char m_at1C;
    char m_pad1D[3];
    Rva003C83E0Pair m_pair;
};

class Rva003C83E0State { };
class Rva003C83E0Gate { };
class Rva003C83E0ResetSink { };

// The canonical global at 0x012F1028 (EA's "TheLivingWorldLogic", defined in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp). This TU
// views it through the local Rva003C83E0Campaign struct above.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

static __forceinline Rva003C83E0Campaign *glo012F1028()
{
    return (Rva003C83E0Campaign *)TheLivingWorldLogic;
}
// Existing singleton definitions at 0x012F7048, 0x012F706C and 0x012F4B98.
class Rva006092D0State;
class LivingWorldManager;
class Rva002EECE0;
extern Rva006092D0State *g_rva012F7048LivingWorld;
extern LivingWorldManager *TheLivingWorldManager;
extern Rva002EECE0 *g_rva002eece0;

extern void j_00048c4d();
extern void j_0000ea7f();
extern void j_000485d1();
extern void j_00025a77();
extern void j_00039801();
extern void j_0001c3be();
extern void j_0004669b();

template<class Owner> static __forceinline bool callFlag(
    Owner *owner, void (*target)())
{
    typedef bool (Owner::*Method)() const;
    union { void (*plain)(); Method member; } route;
    route.plain = target;
    return (owner->*route.member)();
}

class LivingWorldRegionManager
{
public:
    void rva003C83E0(int force);
private:
    char m_pad00[0x40];
    LivingWorldRegion *m_current;
    int m_count;
};

static __forceinline LivingWorldRegion *callRegionLookup(
    LivingWorldRegionManager *owner, const Rva003C83E0Pair *pair)
{
    typedef LivingWorldRegion *(LivingWorldRegionManager::*Method)(
        const Rva003C83E0Pair *);
    union { void (*plain)(); Method member; } route;
    route.plain = j_00039801;
    return (owner->*route.member)(pair);
}

static __forceinline void callResetSink(Rva003C83E0ResetSink *sink)
{
    typedef void (Rva003C83E0ResetSink::*Method)(int);
    union { void (*plain)(); Method member; } route;
    route.plain = j_0004669b;
    (sink->*route.member)(0);
}

void LivingWorldRegionManager::rva003C83E0(int force)
{
    if (callFlag((Rva003C83E0State *)g_rva012F7048LivingWorld, j_00048c4d)
        || callFlag(glo012F1028(), j_0000ea7f))
        return;

    Rva003C83E0Pair pair = glo012F1028()->m_pair;
    if (callFlag((Rva003C83E0Gate *)TheLivingWorldManager, j_000485d1)
        && callFlag(glo012F1028(), j_00025a77))
    {
        if (!glo012F1028()->m_at1C)
            return;

        typedef void (LivingWorldRegionManager::*Update)(LivingWorldRegion *, int);
        union { void (*plain)(); Update member; } target;
        target.plain = j_0001c3be;
        (this->*target.member)(callRegionLookup(this, &pair), force);
        return;
    }

    if (m_current != 0)
    {
        callResetSink((Rva003C83E0ResetSink *)g_rva002eece0);
        m_current = 0;
        m_count = 0;
    }
}
