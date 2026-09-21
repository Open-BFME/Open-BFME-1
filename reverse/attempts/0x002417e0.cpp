// ?d_002417e0@@YAXXZ
// partial score=0.28 date=2026-09-17
// Anonymous body at retail RVA 0x002417E0 (1467 bytes).
//
// The boundary is exact through ret 0xc.  The callers reach it through ILT
// 0x0001FB9A and prove a thiscall body with three stack arguments.  No caller,
// vtable slot, or Zero Hour owner proves a semantic class or method name, so
// this source deliberately keeps the address in its opaque owner name.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

struct Rva002417E0Coord
{
	Real x;
	Real y;
	Real z;
};

extern void j_00004a11();
extern void j_00008a9e();
extern void j_0000991c();
extern void j_0000ebab();
extern void j_00012486();
extern void j_000131a6();
extern void j_0001336d();
extern void j_00015d02();
extern void j_0002191d();
extern void j_000230ab();
extern void j_00024d70();
extern void j_00024f7d();
extern void j_00027ffc();
extern void j_0002910e();
extern void j_000294e2();
extern void j_0002ecad();
extern void j_0002ed16();
extern void j_0002fe0f();
extern void j_0003251f();
extern void j_0003611a();
extern void j_0003a1a7();
extern void j_0003a391();
extern void j_0003b359();
extern void j_00044774();
extern void j_00046164();

extern void *g_rva002417E0AI;
extern void *g_rva002417E0Terrain;
extern void *g_rva002417E0Logic;
extern Real g_rva002417E0Default;
extern Real g_rva002417E0Tolerance;
extern Real g_rva002417E0Height;

class Thing
{
public:
	void setOrientation(Real angle);
};

class Rva002417E0Owner
{
public:
	void rva002417E0(void *first, Rva002417E0Coord *second,
		UnsignedInt third);
};

class Rva002417E0Dispatch
{
};

typedef bool (Rva002417E0Dispatch::*Rva002417E0Bool0)();
typedef bool (Rva002417E0Dispatch::*Rva002417E0Bool1)(void *);
typedef void (Rva002417E0Dispatch::*Rva002417E0Void0)();
typedef void (Rva002417E0Dispatch::*Rva002417E0Void1)(void *);
typedef void (Rva002417E0Dispatch::*Rva002417E0Void2)(void *, void *);
typedef void (Rva002417E0Dispatch::*Rva002417E0Void3)(void *, void *, void *);
typedef void (Rva002417E0Dispatch::*Rva002417E0Void4)(void *, void *, void *, void *);
typedef Real (Rva002417E0Dispatch::*Rva002417E0Real0)();
typedef Real (Rva002417E0Dispatch::*Rva002417E0Real1)(void *);
typedef void *(Rva002417E0Dispatch::*Rva002417E0Ptr4)(void *, void *, void *, void *);

static __forceinline bool rva002417E0Bool0(void (*raw)(), void *object)
{
	union
	{
		void (*raw)();
		Rva002417E0Bool0 typed;
	} call;
	call.raw = raw;
	return (reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)();
}

static __forceinline bool rva002417E0Bool1(void (*raw)(), void *object,
	void *value)
{
	union
	{
		void (*raw)();
		Rva002417E0Bool1 typed;
	} call;
	call.raw = raw;
	return (reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)(value);
}

static __forceinline void rva002417E0Void0(void (*raw)(), void *object)
{
	union
	{
		void (*raw)();
		Rva002417E0Void0 typed;
	} call;
	call.raw = raw;
	(reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)();
}

static __forceinline void rva002417E0Void1(void (*raw)(), void *object,
	void *value)
{
	union
	{
		void (*raw)();
		Rva002417E0Void1 typed;
	} call;
	call.raw = raw;
	(reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)(value);
}

static __forceinline void rva002417E0Void2(void (*raw)(), void *object,
	void *first, void *second)
{
	union
	{
		void (*raw)();
		Rva002417E0Void2 typed;
	} call;
	call.raw = raw;
	(reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)(first, second);
}

static __forceinline void rva002417E0Void3(void (*raw)(), void *object,
	void *first, void *second, void *third)
{
	union
	{
		void (*raw)();
		Rva002417E0Void3 typed;
	} call;
	call.raw = raw;
	(reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)(first, second, third);
}

static __forceinline void rva002417E0Void4(void (*raw)(), void *object,
	void *first, void *second, void *third, void *fourth)
{
	union
	{
		void (*raw)();
		Rva002417E0Void4 typed;
	} call;
	call.raw = raw;
	(reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)(first, second, third, fourth);
}

static __forceinline Real rva002417E0Real0(void (*raw)(), void *object)
{
	union
	{
		void (*raw)();
		Rva002417E0Real0 typed;
	} call;
	call.raw = raw;
	return (reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)();
}

static __forceinline Real rva002417E0Real1(void (*raw)(), void *object,
	void *value)
{
	union
	{
		void (*raw)();
		Rva002417E0Real1 typed;
	} call;
	call.raw = raw;
	return (reinterpret_cast<Rva002417E0Dispatch *>(object)->*call.typed)(value);
}

void Rva002417E0Owner::rva002417E0(
	void *first, Rva002417E0Coord *second, UnsignedInt third)
{
	volatile UnsignedByte retailFrame[0x54];
	retailFrame[0] = 0;
	Real firstAt3c = *(Real *)((char *)first + 0x3c);
	void *firstAt204 = *(void **)((char *)first + 0x204);
	void *firstAt38 = (char *)first + 0x38;
	void *ownerObject = *(void **)((char *)this + 8);
	void *ownerAt204 = ownerObject != 0
		? *(void **)((char *)ownerObject + 0x204) : 0;
	void *firstAt40 = *(void **)((char *)first + 0x40);
	void *liveEbp = firstAt204;
	if (ownerAt204 == 0 || firstAt204 == 0)
		return;

	void *arg2At0 = *(void **)((char *)second + 0);
	void *arg2At4 = *(void **)((char *)second + 4);
	void *arg2At8 = *(void **)((char *)second + 8);
	Rva002417E0Coord delta;
	if (!rva002417E0Bool1(j_000131a6, arg2At4, first))
	{
		if ((*(UnsignedInt *)((char *)this + 0x114) & 0x10000000) == 0)
			return;
		*(UnsignedInt *)((char *)this + 0x114) &= 0xefffffff;
		rva002417E0Void0(j_0002191d, first);
		return;
	}

	if (!rva002417E0Bool0(j_00044774, first))
	{
		Real dx = *(Real *)((char *)second + 0) - *(Real *)((char *)first + 0x9c);
		Real dy = *(Real *)((char *)second + 4) - *(Real *)((char *)first + 0xa0);
		delta.x = dx;
		delta.y = dy;
		delta.z = *(Real *)((char *)second + 8) - firstAt3c;
		delta.z = rva002417E0Real0(j_0002fe0f, &delta);
		if (*(void **)((char *)first + 0x140) != 0)
		{
			rva002417E0Void3(j_00008a9e,
				*(void **)((char *)first + 0x140), ownerAt204,
				&delta, arg2At0);
			delta.z += rva002417E0Real0(j_0002ecad, second);
		}
	}

	if (*(UnsignedByte *)((char *)this + 0x1fc) == 0)
	{
		void *ownerVtable = *(void **)((char *)firstAt204 + 0);
		(void)ownerVtable;
		if (rva002417E0Bool0(j_00044774, liveEbp))
			return;
	}

	if (*(UnsignedInt *)((char *)this + 0x1d8) != 0)
	{
		Real orientation = delta.x + delta.y + delta.z;
		((Thing *)first)->setOrientation(orientation);
		(void)rva002417E0Real1(j_00024f7d, ownerAt204, first);
	}

	(void)rva002417E0Real1(j_000230ab, ownerAt204, first);
	rva002417E0Void1(j_0003a1a7, first, &second);
	rva002417E0Void1(j_0002ed16, first, &second);
	if (rva002417E0Bool0(j_0003b359, ownerAt204))
	{
		*(UnsignedInt *)((char *)first + 0x114) |= 2;
		rva002417E0Void0(j_0002191d, first);
	}

	if (*(UnsignedByte *)((char *)this + 0x1fc) != 0)
	{
		void *slot = *(void **)((char *)this + 0x1d8);
		Int index = (Int)rva002417E0Real0(j_00046164, this);
		(void)slot;
		(void)index;
		if (rva002417E0Bool0(j_00044774, first))
			*(UnsignedInt *)((char *)first + 0x114) |= 0x10000000;
	}

	if (third != 0)
	{
		rva002417E0Void2(j_0003251f, first, (void *)0x0e, (void *)third);
		if (rva002417E0Bool0(j_0003611a, liveEbp))
			rva002417E0Void0(j_0002191d, first);
	}

	if (g_rva002417E0AI != 0 && g_rva002417E0Terrain != 0)
	{
		void *ai = *(void **)((char *)g_rva002417E0AI + 0x0c);
		void *terrain = *(void **)((char *)g_rva002417E0Terrain + 0x0c);
		(void)ai;
		(void)terrain;
		(void)g_rva002417E0Logic;
		(void)g_rva002417E0Default;
		(void)g_rva002417E0Tolerance;
		(void)g_rva002417E0Height;
	}

	if (ownerObject != 0)
	{
		(void)ownerObject;
		(void)rva002417E0Bool0(j_00004a11, this);
	}
	(void)arg2At8;
	(void)j_0000991c;
	(void)j_0000ebab;
	(void)j_00012486;
	(void)j_0001336d;
	(void)j_00015d02;
	(void)j_00024d70;
	(void)j_00027ffc;
	(void)j_0002910e;
	(void)j_000294e2;
	(void)j_0003a391;
	(void)firstAt38;
	(void)firstAt40;
	(void)liveEbp;
	(void)retailFrame[0];
}
