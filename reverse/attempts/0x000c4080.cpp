// ?rva000C4080Compare@@YG_NPAVRvaC4390Second@@0PAX@Z
// partial score=0.60 date=2026-09-21
// cl: /O2 /Ob0
// Retail 0x000C4080 (?d_000c4080@@YAXXZ, dump d_000bb0e0.asm). __stdcall
// free function, 3 stack params (ret 0xC), only the first two used.
// Full control-flow decode (tools/dis_retail.py):
//   a = arg0->resolve(0); b = arg1->resolve(0);      (matched RvaC4390Second
//                                                      ::resolve, RvaC4390Second_resolve.cpp)
//   if (a == b) return false;
//   if (a != 0 && b == 0) { z = ((Object*)a)->unidentified_001BFE20(); arg = arg1; }
//   else                  { z = ((Object*)b)->unidentified_001BFE20(); arg = arg0; }
//   if (z == 0) return false;
//   return ((interface*)z)->vtbl[0x6c](arg);
// unidentified_001BFE20 is the matched Object member in ObjectTeamAndPlayer.cpp
// (returns a HordeContain interface pointer); its vtable slot 0x6c (index 27)
// is address-derived only, called here with one pointer argument returning
// bool. No named caller; identity of the two operands and the vtable slot
// are unproven, only the shape and the two real callees are.
//
// RESIDUE (45/113 bytes): the shared early-exit guard and the ra==rb guard
// now byte-match exactly (they merge with a single `if (a==0||b==0)` /
// `goto returnFalse` -- two separate early ifs kept two exit blocks
// instead of retail's one). Past that point retail DUPLICATES the
// null-check on `z` (a separate `test eax,eax; je <shared-false>` inside
// EACH branch of the ra/rb if-else) while still sharing the single
// `mov edx,[eax]; ...; call [edx+0x6c]` tail (the second branch jumps back
// into the middle of the first branch's tail). A single shared `if (z==0)`
// after the if/else gives this 104/113 result (missing the duplicated
// check); moving the null check inside each branch instead duplicates the
// call too (120/113, worse). No source shape tried reproduces exactly one
// duplicated check with one shared call tail.

typedef int Int;

class RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve(Int allowLookup);
};

class Object
{
public:
	void *unidentified_001BFE20(void) const;
};

class RvaC4390Interface
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void); virtual void slot26(void);
	virtual bool slot27(void *arg);
};

bool __stdcall rva000C4080Compare(RvaC4390Second *a, RvaC4390Second *b, void *unused)
{
	if (a == 0 || b == 0)
		return false;

	RvaC4390First *ra = a->resolve(0);
	RvaC4390First *rb = b->resolve(0);

	if (ra == rb)
		goto returnFalse;

	void *z;
	void *arg;

	if (ra != 0 && rb == 0)
	{
		z = ((Object *)ra)->unidentified_001BFE20();
		arg = b;
	}
	else
	{
		z = ((Object *)rb)->unidentified_001BFE20();
		arg = a;
	}

	if (z == 0)
		goto returnFalse;

	return ((RvaC4390Interface *)z)->slot27(arg);

returnFalse:
	return false;
}
