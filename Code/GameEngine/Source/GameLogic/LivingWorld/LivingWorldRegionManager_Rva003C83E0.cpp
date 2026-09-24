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

extern Rva003C83E0Campaign *Glo012F1028;
extern Rva003C83E0State *g_bfmeStateDF;
extern Rva003C83E0Gate *g_bfmeGameCW;
extern Rva003C83E0ResetSink *Glo012F4B98;

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
    if (callFlag(g_bfmeStateDF, j_00048c4d)
        || callFlag(Glo012F1028, j_0000ea7f))
        return;

    Rva003C83E0Pair pair = Glo012F1028->m_pair;
    if (callFlag(g_bfmeGameCW, j_000485d1)
        && callFlag(Glo012F1028, j_00025a77))
    {
        if (!Glo012F1028->m_at1C)
            return;

        typedef void (LivingWorldRegionManager::*Update)(LivingWorldRegion *, int);
        union { void (*plain)(); Update member; } target;
        target.plain = j_0001c3be;
        (this->*target.member)(callRegionLookup(this, &pair), force);
        return;
    }

    if (m_current != 0)
    {
        callResetSink(Glo012F4B98);
        m_current = 0;
        m_count = 0;
    }
}
