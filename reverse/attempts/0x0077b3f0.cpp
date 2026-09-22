// ?d_0077b3f0@@YAXXZ
// partial score=0.9859387923904053 date=2026-09-22
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// Hub RVA 0077B3F0, 1209 bytes. Analyst reconstruction; NOT a matched claim.
// Symbol: ?method@Rva0077B3F0@@QAEXPBVMatrix3D@@@Z
// See ANALYSIS.md for every branch/call and the independently checked ABIs.
// The retail prologue has a 0x4C frame, conditional ESI/EBP/EBX/EDI saves,
// no EH registration, and ret 4. Native local lifetimes target that frame.
// No asm, emit, synthetic instruction padding, or omitted calls.
#include "matrix3d.h"
#include "ascii_string.h"
#include <stddef.h>

typedef unsigned int U32;
typedef unsigned char U8;

struct Rva0077B3F0Coord { float x, y, z; };
class Rva0077B3F0Particle
{
public:
    void rva005BDE00(const Rva0077B3F0Coord *); // ILT 00021832
    void rva005BDD90();                       // ILT 0000FFD3
    void rva005C1FB0();                       // ILT 0000E525
};
Rva0077B3F0Particle *rva005CFF50();             // ILT 00001B18

class Rva0077B3F0HandleBase
{
public:
    Rva0077B3F0HandleBase &rva005C21D0(const Rva0077B3F0HandleBase &) throw();
    void rva005C2240() throw();
    Rva0077B3F0Particle *p00;
    Rva0077B3F0HandleBase *p04, *p08;
};
class Rva0077B3F0Handle : public Rva0077B3F0HandleBase
{
public:
    ~Rva0077B3F0Handle() throw(); // ILT 00013994 -> 001DA440
    operator bool() const { return p00 != 0; }
    Rva0077B3F0Particle *operator->() const
    {
        if (!p00) return rva005CFF50();
        return p00;
    }
};
struct Rva0077B3F0Template;
class Rva0077B3F0Manager
{
public:
    Rva0077B3F0Template *rva005C9F90(const AsciiString &) const;
    Rva0077B3F0Handle rva005C3A30(const Rva0077B3F0Template *, bool) throw();
};

// Virtual slot names are address-derived. No unrelated virtual identities.
#define SLOT(n) virtual void slot##n();
#define SLOTS_00_0C SLOT(00) SLOT(04) SLOT(08) SLOT(0C)
#define SLOTS_10_1C SLOT(10) SLOT(14) SLOT(18) SLOT(1C)
#define SLOTS_20_2C SLOT(20) SLOT(24) SLOT(28) SLOT(2C)
#define SLOTS_30_3C SLOT(30) SLOT(34) SLOT(38) SLOT(3C)
#define SLOTS_40_4C SLOT(40) SLOT(44) SLOT(48) SLOT(4C)
#define SLOTS_50_5C SLOT(50) SLOT(54) SLOT(58) SLOT(5C)
#define SLOTS_60_6C SLOT(60) SLOT(64) SLOT(68) SLOT(6C)
#define SLOTS_70_7C SLOT(70) SLOT(74) SLOT(78) SLOT(7C)
#define SLOTS_80_8C SLOT(80) SLOT(84) SLOT(88) SLOT(8C)
#define SLOTS_90_9C SLOT(90) SLOT(94) SLOT(98) SLOT(9C)
#define SLOTS_A0_AC SLOT(A0) SLOT(A4) SLOT(A8) SLOT(AC)
#define SLOTS_B0_BC SLOT(B0) SLOT(B4) SLOT(B8) SLOT(BC)
#define SLOTS_C0_CC SLOT(C0) SLOT(C4) SLOT(C8) SLOT(CC)
#define SLOTS_D0_DC SLOT(D0) SLOT(D4) SLOT(D8) SLOT(DC)

class Rva0077B3F0Terrain
{
public:
    SLOTS_00_0C SLOTS_10_1C SLOTS_20_2C SLOTS_30_3C
    SLOT(40) SLOT(44) SLOT(48)
    virtual bool slot4C(float, float, float *, float *);
};
class Rva0077B3F0Render
{
public:
    SLOTS_00_0C SLOTS_10_1C SLOTS_20_2C SLOTS_30_3C SLOTS_40_4C SLOT(50)
    virtual void slot54(const Matrix3D &);
};
class Rva0077B3F0Secondary
{
public:
    SLOTS_00_0C SLOTS_10_1C SLOTS_20_2C SLOTS_30_3C SLOTS_40_4C SLOTS_50_5C
    SLOT(60) SLOT(64)
    virtual bool slot68(int); // base -> 00762F40, real ret4
    SLOT(6C)
    virtual void slot70();    // base -> 00764290
};
class Rva0077B3F0Primary
{
public:
    SLOTS_00_0C SLOTS_10_1C SLOTS_20_2C SLOTS_30_3C SLOTS_40_4C SLOTS_50_5C
    SLOTS_60_6C SLOTS_70_7C SLOTS_80_8C SLOTS_90_9C SLOTS_A0_AC SLOTS_B0_BC
    SLOTS_C0_CC SLOTS_D0_DC SLOT(E0) SLOT(E4) SLOT(E8)
    virtual void slotEC();    // base -> 0075CC80
};
class Rva0077B3F0Contain
{
public:
    SLOTS_00_0C SLOTS_10_1C SLOT(20)
    virtual bool slot24();
};
struct Rva0077B3F0Object
{
    U8 unknown000[0x1fc];
    Rva0077B3F0Contain *p1fc;
    U8 unknown200[0x14];
    Rva0077B3F0Object *p214;
    U8 unknown218[0x344-0x218];
    U8 b344;
};
class Rva0077B3F0Tint
{
public:
    Rva0077B3F0Tint &rva0075EF90(const Rva0077B3F0Tint &);
};
class Rva0077B3F0Drawable
{
public:
    void rva00411EF0();
    void rva00421830(void *); // not BitFlags; one unused stack arg, ret4
    U8 unknown000[0x68];
    Rva0077B3F0Tint *p068;
    U8 unknown06c[0xfc-0x6c];
    Rva0077B3F0Object *p0fc;
};
class Rva0077B3F0Client
{
public:
    SLOTS_00_0C SLOTS_10_1C SLOT(20) SLOT(24) SLOT(28)
    virtual Rva0077B3F0Drawable *slot2C(U32);
    SLOTS_30_3C SLOTS_40_4C SLOTS_50_5C SLOT(60) SLOT(64)
    virtual U32 slot68();
};
struct Rva0077B3F0Logic { U8 unknown000[0x10c]; int i10c; };
struct Rva0077B3F0Shadow
{
    U32 unknown000;
    bool b004;
    U8 unknown005[0x34-5];
    int i034;
};
struct Rva0077B3F0Node
{
    U32 unknown000;
    Rva0077B3F0Node *p004, *p008, *p00c;
    U32 value010;
};
Rva0077B3F0Node *rva0082B870(Rva0077B3F0Node *);
bool rva007397E0(Rva0077B3F0Render *, float, float, float);
class Rva0077B3F0Radius
{
public:
    void rva004585F0();
    U8 unknown[0x98];
};
struct Rva0077B3F0Data
{
    U8 unknown000[0x14];
    AsciiString WadingParticleSys;
    U8 unknown018[0x69-0x18];
    bool NoRotate;
    U8 unknown06a[0xdc-0x6a];
    bool ParticlesAttachedToAnimatedBones;
    U8 unknown0dd[0x10a-0xdd];
    bool ShowShadowWhileContained;
    U8 unknown10b[0x131-0x10b];
    bool MultiPlayerOnly;
    U8 unknown132;
    bool HighDetailOnly;
};

extern Rva0077B3F0Logic *g_va012F0898;
extern Rva0077B3F0Terrain *g_va012EF4CC;
extern Rva0077B3F0Manager *g_va012F64BC;
extern U32 g_va012F8064;
extern Rva0077B3F0Client *g_va012F1464;

// Retain the reference-return min shape: retail selects either argument home
// or H+214 by address before loading the unsigned scalar.
inline const U32 &rva0077B3F0Min(const U32 &a, const U32 &b)
{
    return a < b ? a : b;
}
inline bool rva0077B3F0NameNotEmpty(const AsciiString &s)
{
    const U8 *data = *(const U8 *const *)&s;
    return data && *(const unsigned short *)(data+4) != 0;
}

class Rva0077B3F0
{
public:
    void method(const Matrix3D *transform);
    void rva0076C080();
    void rva007629F0(Matrix3D &);
    void rva0075F400();
    void rva00779F10();
    void rva0076EFF0();
    void rva0075C9F0(Rva0077B3F0Render *);
    void rva0075F810();

    void *p000;
    Rva0077B3F0Data *p004;
    Rva0077B3F0Drawable *p008;
    Rva0077B3F0Secondary s00c;
    U32 unknown010;
    void *p014;
    Rva0077B3F0Handle h018;
    U8 unknown024[0x2e-0x24];
    bool b02e, b02f;
    U8 unknown030[4];
    Rva0077B3F0Render *p034;
    U32 unknown038;
    Rva0077B3F0Shadow *p03c;
    U8 unknown040[0xc];
    void *p04c, *p050;
    U32 unknown054;
    void *p058, *p05c;
    U8 unknown060[0x24];
    bool b084;
    U8 unknown085[3];
    U32 u088;
    Rva0077B3F0Node *p08c;
    U32 u090, unknown094, unknown098, u09c, u0a0;
    U8 unknown0a4[0x164-0xa4];
    U8 b164;
    U8 unknown165[0x170-0x165];
    bool b170, b171;
    U8 unknown172[6];
    Rva0077B3F0Radius s178;
    bool b210;
    U8 unknown211[3];
    U32 u214, u218, u21c;
    float f220, f224, f228;
};
typedef char check_handle_size[sizeof(Rva0077B3F0Handle)==12 ? 1 : -1];
typedef char check_matrix_size[sizeof(Matrix3D)==48 ? 1 : -1];
typedef char check_config_131[offsetof(Rva0077B3F0Data,MultiPlayerOnly)==0x131 ? 1 : -1];
typedef char check_owner_018[offsetof(Rva0077B3F0,h018)==0x18 ? 1 : -1];
typedef char check_owner_034[offsetof(Rva0077B3F0,p034)==0x34 ? 1 : -1];
typedef char check_owner_178[offsetof(Rva0077B3F0,s178)==0x178 ? 1 : -1];
typedef char check_owner_210[offsetof(Rva0077B3F0,b210)==0x210 ? 1 : -1];

void Rva0077B3F0::method(const Matrix3D *transform)
{
    if (!b084 && u088) return;
    const Rva0077B3F0Data *data = p004;
    if (data->MultiPlayerOnly && g_va012F0898->i10c != 1 && g_va012F0898->i10c != 5)
        return;
    if (data->HighDetailOnly && u0a0) return;
    b084 = false;

    if ((b164 & 0x10) && rva0077B3F0NameNotEmpty(data->WadingParticleSys))
    {
        const Vector3 translation = transform->Get_Translation();
        Rva0077B3F0Coord pos;
        pos.x = translation.X;
        pos.y = translation.Y;
        pos.z = translation.Z;
        g_va012EF4CC->slot4C(pos.x, pos.y, &pos.z, 0);
        if (h018)
            h018->rva005BDE00(&pos);
        else
        {
            Rva0077B3F0Template *t = g_va012F64BC->rva005C9F90(data->WadingParticleSys);
            if (t)
            {
                h018.rva005C21D0(g_va012F64BC->rva005C3A30(t,true));
                if (h018)
                {
                    h018->rva005BDE00(&pos);
                    h018->rva005BDD90();
                }
            }
        }
    }
    else if (h018)
    {
        h018->rva005C1FB0();
        h018.rva005C2240();
    }

    if (g_va012F8064 != u09c) rva0076C080();
    if (p034)
    {
        Matrix3D mtx(true);
        if (data->NoRotate) mtx.Set_Translation(transform->Get_Translation());
        else mtx = *transform;
        rva007629F0(mtx);
        p034->slot54(mtx);
        if (b210)
        {
            U32 now = g_va012F1464->slot68();
            U32 delta = now - u21c;
            u21c = now;
            u218 = rva0077B3F0Min(u218 + delta,u214);
            float fraction = float(u218) / float(u214);
            rva007397E0(p034, fraction*f220, fraction*f224, fraction*f228);
            if (u218 >= u214) b210 = false;
        }
    }
    rva0075F400();
    rva00779F10();
    if (data->ParticlesAttachedToAnimatedBones) s00c.slot68(0);
    if (u090)
    {
        for (Rva0077B3F0Node *n=p08c->p008; n!=p08c; n=rva0082B870(n))
        {
            Rva0077B3F0Drawable *child = g_va012F1464->slot2C(n->value010);
            if (child)
            {
                if (p008->p068 && child->p068)
                    child->p068->rva0075EF90(*p008->p068);
                child->rva00411EF0();
                child->rva00421830(0);
            }
        }
    }
    ((Rva0077B3F0Primary*)this)->slotEC();
    rva0076EFF0();
    Rva0077B3F0Object *object=p008->p0fc;
    Rva0077B3F0Object *containing;
    if (object && (containing=object->p214) && !data->ShowShadowWhileContained &&
        !containing->p1fc->slot24())
    {
        if (!b02f) b02f=true;
    }
    else if (b02e && b02f) b02f=false;
    if (object && p03c && p03c->i034==1 && (object->b344 & 1))
    {
        b02f=true;
        p03c->b004=false;
    }
    if ((p058!=p05c && b171) || (p04c!=p050 && b170)) s00c.slot70();
    rva0075C9F0(p034);
    s178.rva004585F0();
    rva0075F810();
}
