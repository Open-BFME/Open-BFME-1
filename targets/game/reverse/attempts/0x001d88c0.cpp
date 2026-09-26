// ?d_001d88c0@@YAXXZ
// partial score=0.15140845070422537 date=2026-09-22
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /FAsc /Fabuild/hub_001d88c0/body.cod
// stlport
// Complete source reconstruction of retail RVA 0x001D88C0, 2556 bytes.
// This is an experiment, not a matched source. See ANALYSIS.md and PROGRESS.md.
// Hidden vector result + five explicit arguments; retail ret 0x18.
// Retail frame: FS registration, sub esp,0x198, EBX/EBP/ESI/EDI saves.
// No guessed semantic hub or private-callee names, no assembly, no pins.
// This variant reproduces the complete real prologue and every local stack slot.
// First remaining masked divergence: +0x97, state-5 store scheduling.
// It has all nine EH states; it is NOT byte-exact or link-validated.
// Out-of-line STL specialization bindings are specified in ANALYSIS.md.

#include <vector>
#include <list>
#include "ascii_string.h"
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"

// The covered string declaration is reused. Retail inlines this forwarding
// destructor at +79; the out-of-line StringBase release owns the operation.
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

extern void j_00028560();
extern void j_00020824();
extern void j_000179bd();
extern void j_0004494a();
extern void j_0000d990();
extern void j_0000ae5c();
extern void j_00045561();
extern void j_000364ad();
extern void j_000050c9();
extern void j_00037f83();
extern void j_00001bae();
extern void j_00022336();
extern void j_00048d79();
extern void j_0002d439();
extern void j_0000c752();
extern void j_0003a391();
extern void j_00035e0e();
extern void j_0002cca5();
extern void j_00026c4c();
extern void j_0002c660();
extern void j_0004a12e();
extern void j_00025306();
extern void j_00019a6a();
extern void j_0003251f();
extern void j_00046a1f();
extern void j_0003f288();
extern void j_00026f35();

// Same single-inheritance ABI adapter used by the landed 0x001D8850 caller.
// The address is an EXISTING ILT symbol, never a proposed semantic pin.
template<class F> __forceinline F rvaCode(void (__cdecl *p)())
{
    union { void (__cdecl *raw)(); F typed; } u;
    u.raw = p;
    return u.typed;
}
template<class T> __forceinline T &rvaField(void *p, unsigned int offset)
{ return *(T *)((char *)p + offset); }
template<class T> __forceinline const T &rvaField(const void *p, unsigned int offset)
{ return *(const T *)((const char *)p + offset); }
template<class F> __forceinline F rvaVirtual(const void *p, unsigned int offset)
{ return rvaCode<F>((void (__cdecl *)())(*(void ***)p)[offset/4]); }

struct Rva001D88C0Object;
struct Rva001D88C0Template;
struct Rva001D88C0Player;
struct Rva001D88C0Drawable;
struct Rva001D88C0Contain;
struct Rva001D88C0Interface;
struct Rva001D88C0Terrain;
struct Rva001D88C0Coord { float x,y,z; };
// Retail calls these specializations out of line. Physical bindings:
// CEDA0 base ctor; 1D9540 vector copy; D0210/CC930 base destruction;
// 18B670 erase; 18B910 push; CEBD0 list-base destruction.
// Their original template names are NOT proved by byte masking.
// Declarations preserve the real call boundaries in this compile-only draft.
// The zero-instruction allocator barrier retains retail unwind states 3/4;
// changing it to an empty body collapses the map to seven states.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
namespace _STL {
template<> inline allocator<Rva001D88C0Object *>::~allocator() { _ReadWriteBarrier(); }
template<> _Vector_base<Rva001D88C0Object *,allocator<Rva001D88C0Object *> >::_Vector_base(const allocator<Rva001D88C0Object *> &);
template<> vector<Rva001D88C0Object *,allocator<Rva001D88C0Object *> >::vector(const vector<Rva001D88C0Object *,allocator<Rva001D88C0Object *> > &);
template<> _Vector_base<Rva001D88C0Object *,allocator<Rva001D88C0Object *> >::~_Vector_base();
template<> Rva001D88C0Object **vector<Rva001D88C0Object *,allocator<Rva001D88C0Object *> >::erase(Rva001D88C0Object **,Rva001D88C0Object **);
template<> void vector<Rva001D88C0Object *,allocator<Rva001D88C0Object *> >::push_back(Rva001D88C0Object *const &);
template<> _List_base<Rva001D88C0Object *,allocator<Rva001D88C0Object *> >::~_List_base();
}
typedef std::vector<Rva001D88C0Object *> Rva001D88C0Vector;
typedef std::list<Rva001D88C0Object *> Rva001D88C0List;

struct Rva001D88C0Flags
{
    unsigned int word[3];
    Rva001D88C0Flags() { word[0]=word[1]=word[2]=0; }
};
struct Rva001D88C0Options
{
    unsigned int flags;
    float minRadius, maxRadius, startAngle, maxZDelta;
    void *ignoreObject, *sourceToPathToDest, *relationshipObject;
    __forceinline Rva001D88C0Options()
    {
        flags=0; minRadius=0; maxRadius=0;
        startAngle=-99999.9f; maxZDelta=1e10f;
        ignoreObject=0; sourceToPathToDest=0; relationshipObject=0;
    }
};
struct Rva001D88C0Factory
{
    __forceinline const Rva001D88C0Template *find(const AsciiString &s)
    {
        typedef const Rva001D88C0Template *(Rva001D88C0Factory::*F)(const AsciiString &);
        return (this->*rvaCode<F>(j_00028560))(s);
    }
    __forceinline Rva001D88C0Object *make(const Rva001D88C0Template *t, void *team,
        const Rva001D88C0Flags &flags, unsigned int extra)
    {
        typedef Rva001D88C0Object *(Rva001D88C0Factory::*F)(const Rva001D88C0Template *,void *,const Rva001D88C0Flags &,unsigned int);
        return (this->*rvaCode<F>(j_0004494a))(t,team,flags,extra);
    }
};
#define RvaFactory (*(Rva001D88C0Factory **)0x012EF1D8)
#define RvaTerrain (*(Rva001D88C0Terrain **)0x012EF4CC)

struct Rva001D88C0Player
{
    __forceinline bool active() const
    {
        typedef bool (Rva001D88C0Player::*F)() const;
        return (this->*rvaCode<F>(j_000179bd))();
    }
    __forceinline bool callC7CD0(const Rva001D88C0Template *t, int one)
    {
        typedef bool (Rva001D88C0Player::*F)(const Rva001D88C0Template *,int);
        return (((Rva001D88C0Player *)((char *)this+0x30))->*rvaCode<F>(j_00022336))(t,one);
    }
    __forceinline void count(int n,const Rva001D88C0Template *const *t,bool one,unsigned int *out,void *zero)
    {
        typedef void (Rva001D88C0Player::*F)(int,const Rva001D88C0Template *const *,bool,unsigned int *,void *);
        (this->*rvaCode<F>(j_00048d79))(n,t,one,out,zero);
    }
};
struct Rva001D88C0Drawable
{
    __forceinline void call41AA90(bool b)
    {
        typedef void (Rva001D88C0Drawable::*F)(bool);
        (this->*rvaCode<F>(j_0002d439))(b);
    }
    __forceinline void call410D80(unsigned int frames)
    {
        typedef void (Rva001D88C0Drawable::*F)(unsigned int);
        (this->*rvaCode<F>(j_00046a1f))(frames);
    }
    __forceinline void call410D30(unsigned int frames)
    {
        typedef void (Rva001D88C0Drawable::*F)(unsigned int);
        (this->*rvaCode<F>(j_0003f288))(frames);
    }
};
// Vtable shape only. Uncalled reserved slots assert no semantic identity.
typedef void (Rva001D88C0Drawable::*Rva001D88C0FadeMethod)(unsigned int);
struct Rva001D88C0Interface
{
    virtual void reserved00()=0;
    virtual void slot04()=0;
    virtual void reserved08()=0;
    virtual void reserved0C()=0;
    virtual void reserved10()=0;
    virtual void reserved14()=0;
    virtual void reserved18()=0;
    virtual void reserved1C()=0;
    virtual void reserved20()=0;
    virtual void reserved24()=0;
    virtual void reserved28()=0;
    virtual void reserved2C()=0;
    virtual void reserved30()=0;
    virtual void reserved34()=0;
    virtual void reserved38()=0;
    virtual void reserved3C()=0;
    virtual void reserved40()=0;
    virtual void reserved44()=0;
    virtual void reserved48()=0;
    virtual void reserved4C()=0;
    virtual void reserved50()=0;
    virtual void reserved54()=0;
    virtual void reserved58()=0;
    virtual void reserved5C()=0;
    virtual void reserved60()=0;
    virtual void reserved64()=0;
    virtual void reserved68()=0;
    virtual void reserved6C()=0;
    virtual void reserved70()=0;
    virtual void reserved74()=0;
    virtual void reserved78()=0;
    virtual void reserved7C()=0;
    virtual void reserved80()=0;
    virtual void reserved84()=0;
    virtual void reserved88()=0;
    virtual void reserved8C()=0;
    virtual void reserved90()=0;
    virtual void reserved94()=0;
    virtual void reserved98()=0;
    virtual void reserved9C()=0;
    virtual void reservedA0()=0;
    virtual void reservedA4()=0;
    virtual void reservedA8()=0;
    virtual void reservedAC()=0;
    virtual void reservedB0()=0;
    virtual void reservedB4()=0;
    virtual void reservedB8()=0;
    virtual void reservedBC()=0;
    virtual void reservedC0()=0;
    virtual void reservedC4()=0;
    virtual void reservedC8()=0;
    virtual void reservedCC()=0;
    virtual void reservedD0()=0;
    virtual void reservedD4()=0;
    virtual void reservedD8()=0;
    virtual void reservedDC()=0;
    virtual void reservedE0()=0;
    virtual void reservedE4()=0;
    virtual void reservedE8()=0;
    virtual const Rva001D88C0List &slotEC()=0;
};
// Vtable shape only. Uncalled reserved slots assert no semantic identity.
struct Rva001D88C0Contain
{
    virtual void reserved00()=0;
    virtual void reserved04()=0;
    virtual void reserved08()=0;
    virtual void reserved0C()=0;
    virtual void reserved10()=0;
    virtual void reserved14()=0;
    virtual void reserved18()=0;
    virtual void reserved1C()=0;
    virtual void reserved20()=0;
    virtual void reserved24()=0;
    virtual void reserved28()=0;
    virtual void reserved2C()=0;
    virtual void reserved30()=0;
    virtual void reserved34()=0;
    virtual void reserved38()=0;
    virtual void reserved3C()=0;
    virtual void reserved40()=0;
    virtual void reserved44()=0;
    virtual void reserved48()=0;
    virtual void reserved4C()=0;
    virtual void reserved50()=0;
    virtual void reserved54()=0;
    virtual void reserved58()=0;
    virtual void reserved5C()=0;
    virtual void reserved60()=0;
    virtual Rva001D88C0Interface *slot64()=0;
    virtual void reserved68()=0;
    virtual void reserved6C()=0;
    virtual void reserved70()=0;
    virtual void reserved74()=0;
    virtual void reserved78()=0;
    virtual void reserved7C()=0;
    virtual void reserved80()=0;
    virtual bool slot84(Rva001D88C0Object *,bool)=0;
    virtual void slot88(Rva001D88C0Object *)=0;
};
struct Rva001D88C0Object
{
    __forceinline Rva001D88C0Player *player() const
    {
        typedef Rva001D88C0Player *(Rva001D88C0Object::*F)() const;
        return (this->*rvaCode<F>(j_00020824))();
    }
    __forceinline void producer(const Rva001D88C0Object *q)
    {
        typedef void (Rva001D88C0Object::*F)(const Rva001D88C0Object *);
        (this->*rvaCode<F>(j_0000d990))(q);
    }
    virtual void reserved00()=0;
    virtual void reserved04()=0;
    virtual void reserved08()=0;
    virtual void reserved0C()=0;
    virtual void reserved10()=0;
    virtual void reserved14()=0;
    virtual void reserved18()=0;
    virtual void reserved1C()=0;
    virtual void reserved20()=0;
    virtual void reserved24()=0;
    virtual Rva001D88C0Drawable *slot28()=0;
    __forceinline int call1BEC20() const
    {
        typedef int (Rva001D88C0Object::*F)() const;
        return (this->*rvaCode<F>(j_0003a391))();
    }
    __forceinline void layer(int n)
    {
        typedef void (Rva001D88C0Object::*F)(int);
        (this->*rvaCode<F>(j_00035e0e))(n);
    }
    __forceinline bool kind(int n) const
    {
        typedef bool (Rva001D88C0Object::*F)(int) const;
        return (this->*rvaCode<F>(j_0003251f))(n);
    }
    __forceinline Rva001D88C0Contain *contain() const
    { return rvaField<Rva001D88C0Contain *>(this,0x1fc); }
};
struct Rva001D88C0Audio
{
    unsigned char storage[0x70];
    Rva001D88C0Audio(const AsciiString &s,int extra)
    {
        typedef void (Rva001D88C0Audio::*F)(const AsciiString &,int);
        (this->*rvaCode<F>(j_00025306))(s,extra);
    }
    ~Rva001D88C0Audio()
    {
        typedef void (Rva001D88C0Audio::*F)();
        (this->*rvaCode<F>(j_00026f35))();
    }
    __forceinline void objectID(unsigned int n)
    {
        typedef void (Rva001D88C0Audio::*F)(unsigned int);
        (this->*rvaCode<F>(j_00019a6a))(n);
    }
};
// Vtable shape only. Uncalled reserved slots assert no semantic identity.
struct Rva001D88C0AudioReceiver
{
    virtual void reserved00()=0;
    virtual void reserved04()=0;
    virtual void reserved08()=0;
    virtual void reserved0C()=0;
    virtual void reserved10()=0;
    virtual void reserved14()=0;
    virtual void reserved18()=0;
    virtual void reserved1C()=0;
    virtual void reserved20()=0;
    virtual void reserved24()=0;
    virtual void reserved28()=0;
    virtual void reserved2C()=0;
    virtual void reserved30()=0;
    virtual void reserved34()=0;
    virtual void reserved38()=0;
    virtual void reserved3C()=0;
    virtual void reserved40()=0;
    virtual void slot44(Rva001D88C0Audio *)=0;
};
// Vtable shape only. Uncalled reserved slots assert no semantic identity.
struct Rva001D88C0ScriptReceiver
{
    virtual void reserved00()=0;
    virtual void reserved04()=0;
    virtual void reserved08()=0;
    virtual void reserved0C()=0;
    virtual void reserved10()=0;
    virtual void reserved14()=0;
    virtual void reserved18()=0;
    virtual void reserved1C()=0;
    virtual void reserved20()=0;
    virtual void reserved24()=0;
    virtual void reserved28()=0;
    virtual void reserved2C()=0;
    virtual void reserved30()=0;
    virtual void reserved34()=0;
    virtual void reserved38()=0;
    virtual void reserved3C()=0;
    virtual void reserved40()=0;
    virtual void reserved44()=0;
    virtual void reserved48()=0;
    virtual void reserved4C()=0;
    virtual void reserved50()=0;
    virtual void reserved54()=0;
    virtual void reserved58()=0;
    virtual void reserved5C()=0;
    virtual void reserved60()=0;
    virtual void reserved64()=0;
    virtual void reserved68()=0;
    virtual void reserved6C()=0;
    virtual void reserved70()=0;
    virtual void reserved74()=0;
    virtual void reserved78()=0;
    virtual void slot7C(const AsciiString &,Rva001D88C0Object *)=0;
};
struct Rva001D88C0Terrain
{
    __forceinline void call(void (__cdecl *entry)(),const Rva001D88C0Template *t,
        const Rva001D88C0Coord *p,const Matrix3D *m,float scale)
    {
        typedef void (Rva001D88C0Terrain::*F)(const Rva001D88C0Template *,const Rva001D88C0Coord *,const Matrix3D *,float);
        (this->*rvaCode<F>(entry))(t,p,m,scale);
    }
};
// Vtable shape only. Uncalled reserved slots assert no semantic identity.
struct Rva001D88C0ModuleInterface
{
    virtual void reserved00()=0;
    virtual void reserved04()=0;
    virtual void reserved08()=0;
    virtual Rva001D88C0Interface *slot0C()=0;
};
struct Rva001D88C0Module
{
    __forceinline Rva001D88C0Interface *slot0C()
    { return ((Rva001D88C0ModuleInterface *)((char *)this+0x0c))->slot0C(); }
};
struct Rva001D88C0Tracker
{
    __forceinline bool gain(int n,bool a,bool b)
    {
        typedef bool (Rva001D88C0Tracker::*F)(int,bool,bool);
        return (this->*rvaCode<F>(j_0004a12e))(n,a,b);
    }
};

// The native default Matrix3D ctor optimizes away; retail nevertheless calls
// the compiler's Vector4 array-constructor iterator. Preserve that real call.
__forceinline void rvaRotation(Matrix3D &rot,const Matrix3D *m)
{
    typedef void (__stdcall *Ctor)(void *,unsigned int,int,void (__cdecl *)());
    rvaCode<Ctor>(j_0000ae5c)(&rot,16,3,j_00045561);
    rot[0].X=(*m)[0].X; rot[0].Y=(*m)[0].Y; rot[0].Z=(*m)[0].Z;
    rot[1].X=(*m)[1].X; rot[1].Y=(*m)[1].Y; rot[1].Z=(*m)[1].Z;
    rot[2].X=(*m)[2].X; rot[2].Y=(*m)[2].Y; rot[2].Z=(*m)[2].Z;
    rot[2].W=0; rot[1].W=0; rot[0].W=0;
}

struct Rva001D88C0Owner
{
    // No constructor is instantiated. The byte layout matches retail witnesses.
    void *unknown00;
    std::vector<AsciiString> names;                 // 04
    AsciiString putInContainer;                    // 10
    unsigned char unknown14[0x14];
    int count;                                    // 28
    unsigned char unknown2C[0x50];
    unsigned int fadeFrames;                      // 7C
    AsciiString fadeSound;                         // 80
    float minA,minB,maxRadius;                     // 84,88,8C
    unsigned char unknown90[0x74];
    bool flag104,flag105,flag106,flag107,flag108,flag109;
    bool flag10A,flag10B,flag10C,flag10D;
    unsigned char unknown10E[6];
    bool flag114,flag115,flag116,flag117,flag118,flag119;
    unsigned char unknown11A[2];
    int word11C;

    __forceinline void call1D9630(Rva001D88C0Object *o,const AsciiString &name,
        const Rva001D88C0Coord *p,const Matrix3D *m,float orientation,
        const Rva001D88C0Object *q,unsigned int lifetime,int index) const
    {
        typedef void (Rva001D88C0Owner::*F)(Rva001D88C0Object *,const AsciiString &,
            const Rva001D88C0Coord *,const Matrix3D *,float,const Rva001D88C0Object *,unsigned int,int) const;
        (this->*rvaCode<F>(j_0002c660))(o,name,p,m,orientation,q,lifetime,index);
    }
    Rva001D88C0Vector run(const Rva001D88C0Coord *p,const Matrix3D *m,float orientation,
        const Rva001D88C0Object *q,unsigned int lifetime) const;
};

Rva001D88C0Vector Rva001D88C0Owner::run(const Rva001D88C0Coord *p,const Matrix3D *m,
    float orientation,const Rva001D88C0Object *q,unsigned int lifetime) const
{
    Rva001D88C0Object *container;
    static const Rva001D88C0Template *debrisTemplate=RvaFactory->find(AsciiString("GenericDebris"));
    Rva001D88C0Vector objects;
    objects.clear();
    if (names.size()<=0) return objects;
    if (flag104 && (!q || !q->player()->active())) return objects;

    Rva001D88C0Object *debris=0;
    void *team=0;
    if (q) team=rvaField<void *>(q->player(),0x230);
    container=0;
    // Inline isEmpty witnessed at +15D; canonical header supplies the layout.
    const void *containerString=rvaField<const void *>(&putInContainer,0);
    if (containerString && rvaField<unsigned short>(containerString,4)!=0)
    {
        const Rva001D88C0Template *t=RvaFactory->find(putInContainer);
        if (t)
        {
            if (!(rvaField<unsigned char>(t,0xd4)&8) &&
                !(rvaField<unsigned int>(t,0xd0)&0x20000000) &&
                !(rvaField<unsigned int>(t,0xd0)&0x40000000))
            {
                Rva001D88C0Flags status;
                container=RvaFactory->make(t,team,status,0);
                container->producer(q);
            }
            else
            {
                Matrix3D rot;
                rvaRotation(rot,m);
                float scale=rvaField<float>(t,0x3c0);
                if (rvaField<unsigned int>(t,0xd0)&0x20000000)
                    RvaTerrain->call(j_000364ad,t,p,&rot,scale);
                else if (rvaField<unsigned int>(t,0xd0)&0x40000000)
                    RvaTerrain->call(j_000050c9,t,p,&rot,scale);
                else
                    RvaTerrain->call(j_00037f83,t,p,&rot,scale);
            }
        }
    }
    for (int n=0;n<count;++n)
    {
        typedef int (__cdecl *Random)(int,int,char *,int);
        int pick=rvaCode<Random>(j_00001bae)(0,names.size()-1,
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",0x55d);
        const Rva001D88C0Template *t;
        if (flag114)
        {
            Rva001D88C0Player *player=q->player();
            t=RvaFactory->find(names[pick]);
            if (!t) continue;
            if (!flag105 && !player->callC7CD0(t,1)) return objects;
            if (rvaField<unsigned short>(t,0x480)!=0)
            {
                unsigned int number;
                player->count(1,&t,true,&number,0);
                if (number>=rvaField<unsigned short>(t,0x480)) return objects;
            }
        }
        else
        {
            void *lod=*(void **)0x012ED5AC;
            unsigned int *counter=&rvaField<unsigned int>(lod,0x16d8);
            unsigned int mask=rvaField<unsigned int>(lod,0x16dc);
            ++*counter;
            if ((*counter&mask)!=mask) continue;
            t=debrisTemplate;
        }
        if (!t) continue;
        if (!(rvaField<unsigned char>(t,0xd4)&8) &&
            !(rvaField<unsigned int>(t,0xd0)&0x20000000) &&
            !(rvaField<unsigned int>(t,0xd0)&0x40000000))
        {
            Rva001D88C0Flags status;
            debris=RvaFactory->make(t,team,status,0);
            objects.push_back(debris);
            Rva001D88C0Drawable *draw=debris->slot28();
            if (flag106 && draw) draw->call41AA90(true);
            if (flag114 && flag107 && q)
            {
                const AsciiString &name=rvaField<AsciiString>(q,0x84);
                typedef bool (AsciiString::*Empty)() const;
                if (!(name.*rvaCode<Empty>(j_0000c752))() && count==1)
                    (*(Rva001D88C0ScriptReceiver **)0x012F076C)->slot7C(name,debris);
            }
            if (flag10A && q && !container)
            {
                int layer=q->call1BEC20();
                if (layer!=1) debris->layer(layer);
            }
            else if (container && container->contain() && container->contain()->slot84(debris,true))
                container->contain()->slot88(debris);

            if (flag117)
            {
                Rva001D88C0Coord result;
                Rva001D88C0Options options;
                typedef float (__cdecl *RandomReal)(float,float,char *,int);
                options.minRadius=rvaCode<RandomReal>(j_0002cca5)(minA,minB,
                    "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",0x5ca);
                options.maxRadius=maxRadius;
                unsigned int flags=0x80;
                if (flag10B) flags|=4;
                if (flag10D) flags|=0x20;
                if (flag10C) flags|=8;
                options.flags=flags;
                typedef bool (__cdecl *Find)(const Rva001D88C0Coord *,const Rva001D88C0Options *,Rva001D88C0Coord *);
                if (!rvaCode<Find>(j_00026c4c)(p,&options,&result))
                    result=rvaField<Rva001D88C0Coord>(q,0x38);
                call1D9630(debris,names[pick],&result,m,orientation,q,lifetime,n);
            }
            else call1D9630(debris,names[pick],p,m,orientation,q,lifetime,n);

            Rva001D88C0Module **module=rvaField<Rva001D88C0Module **>(debris,0x1f0);
            for (;*module;++module)
            {
                Rva001D88C0Interface *iface=(*module)->slot0C();
                if (iface) iface->slot04();
            }
            if (word11C>0)
                rvaField<Rva001D88C0Tracker *>(debris,0x210)->gain(word11C,true,false);
            debris->producer(q);
            if (flag118)
            {
                Rva001D88C0Audio event(fadeSound,0);
                event.objectID(rvaField<unsigned int>(q,0x74));
                (*(Rva001D88C0AudioReceiver **)0x012ED668)->slot44(&event);
                if (debris->kind(0x6c))
                {
                    if (debris->contain())
                    {
                        Rva001D88C0Interface *group=debris->contain()->slot64();
                        if (group)
                        {
                            Rva001D88C0List members(group->slotEC());
                            for (Rva001D88C0List::iterator i=members.begin();i!=members.end();++i)
                                if (*i) ((*i)->slot28()->*rvaCode<Rva001D88C0FadeMethod>(j_00046a1f))(fadeFrames);
                        }
                    }
                }
                else (debris->slot28()->*rvaCode<Rva001D88C0FadeMethod>(j_00046a1f))(fadeFrames);
            }
            if (flag119)
            {
                Rva001D88C0Audio event(fadeSound,0);
                event.objectID(rvaField<unsigned int>(q,0x74));
                (*(Rva001D88C0AudioReceiver **)0x012ED668)->slot44(&event);
                (debris->slot28()->*rvaCode<Rva001D88C0FadeMethod>(j_0003f288))(fadeFrames);
            }
        }
        else
        {
            Matrix3D rot;
            rvaRotation(rot,m);
            float scale=rvaField<float>(t,0x3c0);
            if (rvaField<unsigned int>(t,0xd0)&0x20000000)
                RvaTerrain->call(j_000364ad,t,p,&rot,scale);
            else if (rvaField<unsigned int>(t,0xd0)&0x40000000)
                RvaTerrain->call(j_000050c9,t,p,&rot,scale);
            else RvaTerrain->call(j_00037f83,t,p,&rot,scale);
        }
    }
    if (container)
    {
        call1D9630(container,*(const AsciiString *)0x01336E50,p,m,orientation,q,lifetime,0);
        container->producer(q);
    }
    return objects;
}
