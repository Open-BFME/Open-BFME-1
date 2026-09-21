// ?d_003e8e10@@YAXXZ
// partial score=0.464902807775 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/pathfind
// Astra complete structural reconstruction, retail RVA 0x003E8E10 (1852 bytes).
// See ANALYSIS.md for every call/edge/layout and the single static-init EH state.
// Partial, not an exact match. All 38 retail calls and all observed paths are modeled.
// Calling views use address-derived types and the independently decoded ILT targets.
// Native /EHsc emits the ONE static-initialization unwind state; no invented destructor.
// Priority: keep the retail E8 frame and call structure before tuning registers/locals.
// P063 before cleanup: 1846 bytes; 979 non-reloc differing bytes; first +0x35.
// The full callee contract and every retail basic block are in ANALYSIS.md.
#define private protected
#include "GameLogic/AIPathfind.h"
#undef private

extern void j_0000187a();
extern void j_000022bb();
extern void j_00005ee3();
extern void j_000105cd();
extern void j_00010ea1();
extern void j_000171e8();
extern void j_0001bb80();
extern void j_0001c675();
extern void j_00027bc9();
extern void j_0002ae23();
extern void j_0002bd82();
extern void j_0002fc7a();
extern void j_00036089();
extern void j_00036994();
extern void j_0003a391();
extern void j_0003a4e5();
extern void j_0003add7();
extern void j_0004375c();
extern void j_0004596c();
extern void j_000461ff();
extern void j_00048112();
extern void j_00049f3f();

class Rva003E8E10CallReceiver {};
template<class P> __forceinline P Rva003E8E10Pmf(void (*f)())
{
    union { void (*raw)(); P member; } u;
    u.raw = f;
    return u.member;
}
struct Rva003E8E10Template;
struct Rva003E8E10Object;
struct Rva003E8E10Profile;
typedef Rva003E8E10Template* (Rva003E8E10CallReceiver::*Rva087A80)();
typedef bool (Rva003E8E10CallReceiver::*Rva1E6930)(Rva003E8E10Object*,const Coord3D*,Rva003E8E10Object*,const Coord3D*,float);
typedef bool (Rva003E8E10CallReceiver::*Rva3E5E40)(Rva003E8E10Object*);
typedef void (Rva003E8E10CallReceiver::*Rva3DEE30)(Rva003E8E10Object*,int*,bool*);
typedef void (Rva003E8E10CallReceiver::*Rva132190)(Coord3D*);
typedef void (Rva003E8E10CallReceiver::*Rva0FB930)();
typedef void (Rva003E8E10CallReceiver::*Rva3E3B20)(Rva003E8E10Object*,Rva003E8E10Object*,Coord3D*);
typedef void (Rva003E8E10CallReceiver::*Rva1C0010)(Coord3D*);
typedef bool (Rva003E8E10CallReceiver::*Rva3D7EC0)(const Coord3D*,ICoord2D*);
typedef int (Rva003E8E10CallReceiver::*Rva1A7C20)(Rva003E8E10Object*,const Coord3D*);
typedef PathfindCell* (Rva003E8E10CallReceiver::*Rva3FBAB0)(int,int);
typedef int (Rva003E8E10CallReceiver::*Rva1BEC20)();
typedef bool (Rva003E8E10CallReceiver::*Rva1BE410)();
typedef unsigned short (Rva003E8E10CallReceiver::*Rva4033E0)(const Rva003E8E10Profile*,unsigned int);
typedef unsigned short (Rva003E8E10CallReceiver::*Rva403390)(const Rva003E8E10Profile*,unsigned int);
typedef int (Rva003E8E10CallReceiver::*Rva08FFC0)(const char*);
typedef void* (Rva003E8E10CallReceiver::*Rva1BEE60)(int);
typedef bool (Rva003E8E10CallReceiver::*Rva266340)();
#define RVA_CALL(T,obj,fn) (((Rva003E8E10CallReceiver*)(obj))->*Rva003E8E10Pmf<T>(fn))

struct Rva003E8E10Template
{
    unsigned int u00;
    Rva003E8E10Template *u04;
    char u08[0xC8-8];
    unsigned int uC8, uCC, uD0, uD4, uD8;
    __forceinline unsigned int rvaC8() const { return uC8; }
    char uDC[0x444-0xDC];
    int u444;
    char u448[0x4CC-0x448];
    bool u4CC;
};
struct Rva003E8E10Object
{
    unsigned int u00;
    Rva003E8E10Template *u04;
    char u08[0x38-8];
    Coord3D position;
    __forceinline Rva003E8E10Template *rvaTemplate() const
    {
        Rva003E8E10Template *t = u04;
        if (t != 0 && t->u04 != 0)
            t = RVA_CALL(Rva087A80,t->u04,j_000022bb)();
        return t;
    }
};
struct Rva003E8E10Arg3 { char u00[0x10]; int u10; };
struct Rva003E8E10Profile
{
    int u00;
    bool u04, u05;
    int u08;
};
class Rva001E6930 {};
class Rva003E8E10;
struct Rva003D5670Context
{
    Rva003E8E10 *u00;
    Rva003E8E10Profile *u04;
    unsigned int u08;
    bool u0C;
    int u10;
    Coord3D u14;
    bool u20;
    Rva001E6930 *u24;
    Rva003E8E10Object *u28, *u2C;
    int u30;
    Coord3D *u34;
    bool u38;
};
static __forceinline void Rva003D5670Inline(Rva003D5670Context *self,
    Rva003E8E10 *p, Rva003E8E10Profile *m, Rva003E8E10Object *s,
    Rva003E8E10Object *t, Rva001E6930 *w, int radius, bool center, bool sourceSpecial,
    unsigned int zone, int layer, Coord3D *q, bool special)
{
    self->u00=p; self->u04=m; self->u08=zone; self->u0C=center; self->u10=layer;
    self->u14.x=q->x; self->u14.y=q->y; self->u14.z=q->z;
    self->u20=sourceSpecial; self->u24=w; self->u28=s; self->u2C=t;
    self->u30=radius; self->u34=q; self->u38=special;
}
typedef char Rva003E8E10CheckProfileSize[(sizeof(Rva003E8E10Profile)==12)?1:-1];
typedef char Rva003E8E10CheckContextSize[(sizeof(Rva003D5670Context)==60)?1:-1];

static __forceinline bool Rva003DF580Call(void *p, Rva003E8E10Object *s,
    int x, int y, int layer, int radius, bool center, PathfindCell **out, bool flag)
{
    typedef bool (Rva003E8E10CallReceiver::*P)(Rva003E8E10Object*,int,int,int,int,bool,PathfindCell**,bool);
    return (((Rva003E8E10CallReceiver*)p)->*Rva003E8E10Pmf<P>(j_00049f3f))(s,x,y,layer,radius,center,out,flag);
}
static __forceinline Rva003D5670Context *Rva003D5670Call(Rva003D5670Context *self,
    Rva003E8E10 *p, Rva003E8E10Profile *m, Rva003E8E10Object *s,
    Rva003E8E10Object *t, Rva001E6930 *w, int radius, bool center, bool sourceSpecial,
    unsigned int zone, int layer, Coord3D *q, bool special)
{
    typedef Rva003D5670Context *(Rva003E8E10CallReceiver::*P)(Rva003E8E10*,Rva003E8E10Profile*,
        Rva003E8E10Object*,Rva003E8E10Object*,Rva001E6930*,int,bool,bool,unsigned int,int,Coord3D*,bool);
    return (((Rva003E8E10CallReceiver*)self)->*Rva003E8E10Pmf<P>(j_0001bb80))
        (p,m,s,t,w,radius,center,sourceSpecial,zone,layer,q,special);
}

class Rva003E8E10 : public Pathfinder
{
public:
    __forceinline PathfindCell *rvaCell(PathfindLayerEnum layer, const ICoord2D &c)
    {
        const int y = c.y;
        if (c.x >= m_extent.lo.x && c.x <= m_extent.hi.x &&
            y >= m_extent.lo.y && y <= m_extent.hi.y)
        {

            const int x = c.x;
            if (layer > 1 && layer <= 15)
            {
                PathfindCell *cell = RVA_CALL(Rva3FBAB0,&m_layers[layer],j_000105cd)(x,y);
                if (cell) return cell;
            }
            return &m_map[x][y];
        }
        return 0;
    }
    bool run(Rva003E8E10Object *s, Rva001E6930 *w, Rva003E8E10Arg3 *l,
             Coord3D *q, Rva003E8E10Object *t);
};

bool Rva003E8E10::run(Rva003E8E10Object *s, Rva001E6930 *w,
    Rva003E8E10Arg3 *l, Coord3D *q, Rva003E8E10Object *t)
{
    // Retail +000..074: C01/C02 and source-position fast success.
    const Coord3D *sp = &s->position;
    if (RVA_CALL(Rva1E6930,w,j_0003a4e5)(s,sp,t,&t->position,0.0f) &&
        RVA_CALL(Rva3E5E40,this,j_00036089)(s))
    {
        *q = *sp;
        return true;
    }

    // +075..1A6: C03..C09, direction and conditional displacement.
    int radius;
    bool center;
    RVA_CALL(Rva3DEE30,this,j_000461ff)(s,&radius,&center);
    Coord3D a; a.x=sp->x; a.y=sp->y; a.z=sp->z;
    Coord3D direction;
    RVA_CALL(Rva132190,s,j_00005ee3)(&direction);
    direction.x *= 10.0f;
    direction.y *= 10.0f;
    a.x += direction.x;
    a.y += direction.y;
    a.z += direction.z;
    Coord3D v;
    v.x = a.x - q->x;
    v.y = a.y - q->y;
    v.z = 0.0f;
    RVA_CALL(Rva0FB930,&v,j_0002bd82)();
    v.x *= 10.0f;
    v.y *= 10.0f;
    v.z *= 10.0f;

    if ((t->rvaTemplate()->rvaC8() & 0x80) || (t->rvaTemplate()->uCC & 0x08000000))
        if (!(t->rvaTemplate()->uD8 & 0x00200000))
            RVA_CALL(Rva3E3B20,this,j_0000187a)(s,t,&v);

    // +1A7..720: at most two passes; the second starts with zero displacement.
    int retry = 0;
    do
    {
        RVA_CALL(Rva1C0010,t,j_00027bc9)(q);
        if (t->rvaTemplate()->uD8 & 0x00200000)
        {
            v.x = 0.0f; v.y = 0.0f; v.z = 0.0f;
        }
        q->x += v.x;
        q->y += v.y;
        q->z += v.z;
        if (!center)
        {
            q->x += 5.0f;
            q->y += 5.0f;
        }
        ICoord2D c;
        if (RVA_CALL(Rva3D7EC0,this,j_000171e8)(q,&c)) return false;
        int layer = RVA_CALL(Rva1A7C20,*(void**)0x012EF4CC,j_0001c675)(s,q);
        PathfindCell *destCell = rvaCell((PathfindLayerEnum)layer,c);
        // C15 is intentional: retail converts the source position twice.
        ICoord2D unusedCell;
        RVA_CALL(Rva3D7EC0,this,j_000171e8)(&a,&unusedCell);
        int sourceLayer = RVA_CALL(Rva1BEC20,s,j_0003a391)();
        ICoord2D c2;
        RVA_CALL(Rva3D7EC0,this,j_000171e8)(&a,&c2);
        PathfindCell *sourceCell = rvaCell((PathfindLayerEnum)sourceLayer,c2);
        if (!sourceCell) return false;

        if (t->rvaTemplate()->uCC & 0x08000000)
            if (!(t->rvaTemplate()->uD8 & 0x00200000)) layer = 1;
        int u444 = s->rvaTemplate()->u444;
        bool u4CC = s->rvaTemplate()->u4CC;
        bool u1BE410 = RVA_CALL(Rva1BE410,s,j_00010ea1)();
        Rva003E8E10Profile m;
        m.u00 = l->u10;
        m.u04 = !u4CC;
        m.u05 = u1BE410;
        m.u08 = u444 - 1;

        void *zones = (char*)this + 0xC9C;
        unsigned int zone = RVA_CALL(Rva4033E0,zones,j_0004375c)(&m,(unsigned int)*(unsigned short*)((char*)sourceCell+8));
        bool sourceSpecial = false;
        if (sourceCell->getRawType() == 4)
        {
            sourceSpecial = true;
            unsigned short z = RVA_CALL(Rva403390,zones,j_0004596c)(&m,zone);
            zone = RVA_CALL(Rva4033E0,zones,j_0004375c)(&m,(unsigned int)z);
        }
        if (zone == RVA_CALL(Rva4033E0,zones,j_0004375c)(&m,(unsigned int)*(unsigned short*)((char*)destCell+8)))
        {
            PathfindCell *cellOut;
            if (Rva003DF580Call(this,s,c.x,c.y,layer,radius,center,&cellOut,false))
            {
                bool zero = cellOut == 0;
                if (zero && RVA_CALL(Rva1E6930,w,j_0003a4e5)(s,&s->position,t,q,0.0f))
                    return true;
            }
        }

        bool special = false;
        if (t->rvaTemplate()->uD0 & 0x10000000)
        {
            typedef void *(__cdecl *C31)(Rva003E8E10Object*);
            void *u1F8AB0 = ((C31)j_0002fc7a)(t);
            // Retail EH has ONE cleanup: resetting this static's init flag.
            // No stack destructor is present. Native /EHsc static init is required.
            static int key = RVA_CALL(Rva08FFC0,*(void**)0x012ED600,j_0003add7)("SiegeDeploySpecialPower");
            void *module = RVA_CALL(Rva1BEE60,t,j_0002ae23)(key);
            if (u1F8AB0 && module && RVA_CALL(Rva266340,module,j_00048112)()) special = true;
        }

        // +584..6BF: first context initialized inline, second via C37 (ret 0x30).
        Rva003D5670Context k1;
        Rva003D5670Inline(&k1,this,&m,s,t,w,radius,center,sourceSpecial,zone,layer,q,special);
        ICoord2D searchCell;
        typedef bool (Rva003E8E10CallReceiver::*Search)(ICoord2D*,int,ICoord2D*,Rva003D5670Context*,int);
        Search search = Rva003E8E10Pmf<Search>(j_00036994);
        if ((((Rva003E8E10CallReceiver*)this)->*search)(&c,50,&searchCell,&k1,1)) return true;

        if ((t->rvaTemplate()->uD8 & 0x00200000) && layer != 1)
        {
            Rva003D5670Context k2;
            if ((((Rva003E8E10CallReceiver*)this)->*search)(&c,100,&searchCell,
                Rva003D5670Call(&k2,this,&m,s,t,w,radius,center,sourceSpecial,zone,1,q,special),1))
                return true;
        }
        // The unordered x87 result follows the false-return path too.
        if (!(v.x*v.x + v.y*v.y > 1.0f)) return false;
        ++retry;
        v.x = 0.0f; v.y = 0.0f; v.z = 0.0f;
    } while (retry < 2);
    return false;
}
