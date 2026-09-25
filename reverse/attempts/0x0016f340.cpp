// ?d_0016f340@@YAXXZ
// partial score=0.357143 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath
#include "coord3d.h"
inline void Coord3D::set(const Coord3DBase *source)
{ x=source->x; y=source->y; z=source->z; }
// Retail predicate at 0x0016F340. Owner's +0x1c holder owns the receiver
// at +0x10. All fields remain byte typed where retail reads one byte.
typedef unsigned char U8;
typedef float Real;
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

extern void *j_0000e570();
extern void *j_00012b57();
extern Real j_00043ced();

class Rva0016F340Holder { public: char pad[0x10]; void *object; };

// The target resolves these through its actual vtable byte offsets. Keep the
// slots numeric instead of assigning unproved virtual method names.
class Rva0016F340Receiver {};
template<class R, class A1> static __forceinline R callExternal1(void *raw, void *p, A1 a1)
{
    typedef R (Rva0016F340Receiver::*Fn)(A1);
    union { void (*raw)(); Fn method; } u;
    u.raw = (void (*)())raw;
    return (((Rva0016F340Receiver *)p)->*u.method)(a1);
}
template<class R> static __forceinline R callExternal0(void *raw, void *p)
{
    typedef R (Rva0016F340Receiver::*Fn)();
    union { void (*raw)(); Fn method; } u;
    u.raw = (void (*)())raw;
    return (((Rva0016F340Receiver *)p)->*u.method)();
}
template<class R, class A1, class A2, class A3> static __forceinline R callExternal3(void *raw, void *p, A1 a1, A2 a2, A3 a3)
{
    typedef R (Rva0016F340Receiver::*Fn)(A1, A2, A3);
    union { void (*raw)(); Fn method; } u;
    u.raw = (void (*)())raw;
    return (((Rva0016F340Receiver *)p)->*u.method)(a1, a2, a3);
}

// Partial vtable views: reserved declarations only preserve slot indices;
// their signatures are not inferred and they are never called here.
class Rva0016F340AI {
public:
 virtual void reserved00();
 virtual void reserved04();
 virtual void reserved08();
 virtual void reserved0C();
 virtual void reserved10();
 virtual void reserved14();
 virtual void reserved18();
 virtual void reserved1C();
 virtual void reserved20();
 virtual void reserved24();
 virtual void reserved28();
 virtual void reserved2C();
 virtual void reserved30();
 virtual void reserved34();
 virtual void reserved38();
 virtual void reserved3C();
 virtual void reserved40();
 virtual void reserved44();
 virtual void reserved48();
 virtual void reserved4C();
 virtual void reserved50();
 virtual void reserved54();
 virtual void reserved58();
 virtual void reserved5C();
 virtual void reserved60();
 virtual void reserved64();
 virtual void reserved68();
 virtual void reserved6C();
 virtual void reserved70();
 virtual void reserved74();
 virtual void reserved78();
 virtual void reserved7C();
 virtual void reserved80();
 virtual void reserved84();
 virtual void reserved88();
 virtual void reserved8C();
 virtual void reserved90();
 virtual void reserved94();
 virtual void reserved98();
 virtual void reserved9C();
 virtual void reservedA0();
 virtual void reservedA4();
 virtual void reservedA8();
 virtual void reservedAC();
 virtual void reservedB0();
 virtual void reservedB4();
 virtual void reservedB8();
 virtual void reservedBC();
 virtual void reservedC0();
 virtual void reservedC4();
 virtual void reservedC8();
 virtual void reservedCC();
 virtual void reservedD0();
 virtual void reservedD4();
 virtual void reservedD8();
 virtual void reservedDC();
 virtual void reservedE0();
 virtual void reservedE4();
 virtual void reservedE8();
 virtual void reservedEC();
 virtual void reservedF0();
 virtual void reservedF4();
 virtual void reservedF8();
 virtual void reservedFC();
 virtual void reserved100();
 virtual void reserved104();
 virtual void reserved108();
 virtual void reserved10C();
 virtual void reserved110();
 virtual void reserved114();
 virtual void reserved118();
 virtual void reserved11C();
 virtual void reserved120();
 virtual void reserved124();
 virtual void reserved128();
 virtual void reserved12C();
 virtual void reserved130();
 virtual void reserved134();
 virtual void reserved138();
 virtual void reserved13C();
 virtual void reserved140();
 virtual void reserved144();
 virtual void reserved148();
 virtual void reserved14C();
 virtual void reserved150();
 virtual void reserved154();
 virtual void reserved158();
 virtual void reserved15C();
 virtual void reserved160();
 virtual void reserved164();
 virtual void reserved168();
 virtual void reserved16C();
 virtual void reserved170();
 virtual void reserved174();
 virtual void reserved178();
 virtual void reserved17C();
 virtual void reserved180();
 virtual void reserved184();
 virtual void reserved188();
 virtual void reserved18C();
 virtual void reserved190();
 virtual void reserved194();
 virtual void reserved198();
 virtual void reserved19C();
 virtual void reserved1A0();
 virtual void reserved1A4();
 virtual void reserved1A8();
 virtual void reserved1AC();
 virtual void reserved1B0();
 virtual void reserved1B4();
 virtual void reserved1B8();
 virtual void reserved1BC();
 virtual void reserved1C0();
 virtual void reserved1C4();
 virtual void reserved1C8();
 virtual void reserved1CC();
 virtual void reserved1D0();
 virtual void reserved1D4();
 virtual void reserved1D8();
 virtual void reserved1DC();
 virtual void reserved1E0();
 virtual void reserved1E4();
 virtual void reserved1E8();
 virtual void reserved1EC();
 virtual void reserved1F0();
 virtual void reserved1F4();
 virtual void reserved1F8();
 virtual void reserved1FC();
 virtual unsigned rvaSlot200();
};
class Rva0016F340Contain {
public:
 virtual void reserved00();
 virtual void reserved04();
 virtual void reserved08();
 virtual void reserved0C();
 virtual void reserved10();
 virtual void reserved14();
 virtual void reserved18();
 virtual void reserved1C();
 virtual void reserved20();
 virtual void reserved24();
 virtual void reserved28();
 virtual void reserved2C();
 virtual void reserved30();
 virtual void reserved34();
 virtual void reserved38();
 virtual void reserved3C();
 virtual void reserved40();
 virtual void reserved44();
 virtual void reserved48();
 virtual void reserved4C();
 virtual void reserved50();
 virtual void reserved54();
 virtual void reserved58();
 virtual void reserved5C();
 virtual void reserved60();
 virtual void reserved64();
 virtual void *rvaSlot68();
};
class Rva0016F340Child {
public:
 virtual void reserved00();
 virtual void reserved04();
 virtual void reserved08();
 virtual void reserved0C();
 virtual void reserved10();
 virtual void reserved14();
 virtual void reserved18();
 virtual void reserved1C();
 virtual void reserved20();
 virtual void reserved24();
 virtual void reserved28();
 virtual void reserved2C();
 virtual void reserved30();
 virtual void reserved34();
 virtual void reserved38();
 virtual void reserved3C();
 virtual void reserved40();
 virtual void reserved44();
 virtual void reserved48();
 virtual void reserved4C();
 virtual void reserved50();
 virtual void reserved54();
 virtual void reserved58();
 virtual void reserved5C();
 virtual void reserved60();
 virtual void reserved64();
 virtual void reserved68();
 virtual void reserved6C();
 virtual void rvaSlot70(void *,void *,void *);
 virtual void reserved74();
 virtual void reserved78();
 virtual void reserved7C();
 virtual void reserved80();
 virtual void reserved84();
 virtual void reserved88();
 virtual void reserved8C();
 virtual void reserved90();
 virtual void reserved94();
 virtual void reserved98();
 virtual void reserved9C();
 virtual void reservedA0();
 virtual void reservedA4();
 virtual void reservedA8();
 virtual void reservedAC();
 virtual void reservedB0();
 virtual void reservedB4();
 virtual void reservedB8();
 virtual void reservedBC();
 virtual void reservedC0();
 virtual void reservedC4();
 virtual void reservedC8();
 virtual void reservedCC();
 virtual void reservedD0();
 virtual void reservedD4();
 virtual void reservedD8();
 virtual void reservedDC();
 virtual void reservedE0();
 virtual void reservedE4();
 virtual void reservedE8();
 virtual void reservedEC();
 virtual void reservedF0();
 virtual void *rvaSlotF4();
};
class Rva0016F340Object { public: char pad[0x38]; Coord3DBase position; const Coord3DBase *getPosition() const { return &position; } };
class Rva0016F340 { public: char pad[0x1c]; Rva0016F340Holder *holder; unsigned m_unknown20; Coord3D m_goalPosition; int predicate(); };

int Rva0016F340::predicate()
{
    void *object = this->holder->object;
    void *goal = callExternal0<void *>((void *)&j_0000e570, this->holder);
    if ((*(U8 *)((char *)object + 0x344) & 1) || !goal ||
        (*(U8 *)((char *)goal + 0x344) & 1))
        return -2;

    unsigned aiMethod = (*(Rva0016F340AI **)((char *)object+0x204))->rvaSlot200();
    U8 canEnter = callExternal3<U8>((void *)&j_00012b57, *(void **)0x012ED700, object, goal, (void *)aiMethod);
    if (!canEnter)
        return -2;

    m_goalPosition.set(((Rva0016F340Object *)goal)->getPosition());

    Real distance = callExternal1<Real>((void *)&j_00043ced, object, goal);
    if (!(distance < *(const Real *)0x010977E8) ||
        !((Real)fabs(*(Real *)((char *)goal + 0x40) - *(Real *)((char *)object + 0x40)) <
            *(const Real *)0x01075C74))
        return 0;

    void *contain = *(void **)((char *)object + 0x1fc);
    void *child = 0;
    void *containerObject = goal;
    if (contain)
        child = ((Rva0016F340Contain *)contain)->rvaSlot68();
    if (!child) {
        contain = *(void **)((char *)goal + 0x1fc);
        if (!contain)
            return 0;
        child = ((Rva0016F340Contain *)contain)->rvaSlot68();
        containerObject = object;
        if (!child)
            return 0;
    }
    void *accepted = ((Rva0016F340Child *)child)->rvaSlotF4();
    if (!accepted)
        return 0;
    ((Rva0016F340Child *)child)->rvaSlot70(containerObject,accepted,0);
    return 0;
}
