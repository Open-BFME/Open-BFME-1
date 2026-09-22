// ?bfmeStopCO@BfmeHostCO@@QAEXD@Z
// partial score=0.97 date=2026-09-21
// cl: /DNDEBUG /MD
// ?bfmeStopCO@BfmeHostCO@@QAEXD@Z  rva=0x00267D00 size=102
// partial: 99/102, ONE differing instruction pair, everything after it shifted 3 bytes.
//
// NEW this session -- the callee contract.  The banked 0.93/0.97 source named its
// four callees BfmeUnitCO::bfmeWakeCO, BfmeHostCO::bfmeHaltCO, BfmeAgentCO::bfmeBusyCO
// and BfmeAgentCO::bfmeSendCO; NONE of those decorated names exists in
// reverse/functions.csv or reverse/symbols.csv, so that body could never have linked
// and probe never noticed because it masks relocations.  Decoded from the image and
// checked against the ledger, the four REL32 targets are:
//   +0x22 -> ILT 0x0002191D  ?notifyModelConditionChanged@Object@@QAEXXZ   (body 0x001BE1C0)
//   +0x33 -> ILT 0x00020847  UNPINNED, routes to the 390-byte sibling dump 0x00267B10
//   +0x47 -> ILT 0x00011F77  ?isEmpty@FXList@@QBE_NXZ                      (body 0x0042DAA0)
//   +0x5c -> ILT 0x0001BB21  ?doFXPos@FXList@@QBEXPBUCoord3D@@PBVMatrix3D@@M0@Z (body 0x004280D0)
// Three of the four now resolve; `bfmeHaltCO` is address-derived and still needs a
// pin at 0x00020847 with route=0x00267B10 before this row can land.
//
// That contract also identifies the receiver: `this` is a Generals ObjectModule --
// m_moduleData at +4 and m_object at +8 -- because [edi+8] is passed as the `this`
// of Object::notifyModelConditionChanged and [edi+4]+0x264 is the FXList the body
// calls isEmpty/doFXPos on.  Object+0x38 is the Coord3D handed to doFXPos as the
// primary position; Object+0x130 is the status word whose bit 11 (0x800) is tested
// and cleared.  Neither Object offset is witnessed by tools/name_oracle.py
// (nearest below 0x130 is m_shroudRange at +0x12C), so both keep offset names.
//
// Remaining divergence, +0x12, three bytes, unchanged from five earlier seats:
//   retail  mov ecx,eax / and ecx,0xfffff7ff / mov [esi+0x130],ecx / mov ecx,esi
//   ours    and eax,0xfffff7ff / mov ecx,esi / mov [esi+0x130],eax
// Retail copies the loaded status into a second register before masking; VC7.1 masks
// the CSE in place, and the `mov ecx,esi` then floats above the store.  It is ONE
// decision (which register receives the masked value); the store order is its
// consequence.  Levers tried and rejected this session, none of them moving it:
// re-reading the member instead of caching it, `&=`, a named cleared local, an
// inline value setter, an inline testStatus/clearStatus/setStatus(bit,set) pair
// (104 bytes, shr/test cl replaces `test ah,8`), a real enum member, an enum member
// behind an enum-returning accessor (shape_levers.md line 67), the literal
// 0xFFFFF7FF mask, an Int& alias, a two-statement copy-then-mask, a Bool test
// temp (104 bytes), a static clearBit(value,bit) helper, an inline
// Object::clearStatusIfSet(bit) that owns the whole test/clear/notify block, and a
// one-field struct assigned whole (shape_levers.md line 62's materialise-before-the-
// store lever).  Flags swept with the same result: /Ox /O1 /Og+/Ot /Og+/Os /Oy-
// /G5 /G7 /EHsc /Gy /Ob1 /Oi- /Op.

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D;

class FXList
{
public:
	Bool isEmpty(void) const;
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primaryScale, const Coord3D *secondary) const;
};

class Object
{
public:
	void notifyModelConditionChanged(void);

	unsigned char m_bfmeHeadCO[0x38];
	Coord3D m_coord038;
	unsigned char m_bfmeMidCO[0x130 - 0x44];
	Int m_bfmeFlagsCO;
};

class BfmeDataCO
{
public:
	unsigned char m_bfmeHeadCO[0x264];
	const FXList *m_fx264;
};

class BfmeHostCO
{
public:
	void bfmeStopCO(char quiet);
	void bfmeHaltCO(Int mode);

	unsigned char m_bfmeHeadCO[4];
	const BfmeDataCO *m_moduleData;
	Object *m_object;
};

void BfmeHostCO::bfmeStopCO(char quiet)
{
	Object *obj = m_object;
	Int status = obj->m_bfmeFlagsCO;

	if ((status & 0x800) == 0)
		return;

	obj->m_bfmeFlagsCO = status & ~0x800;
	obj->notifyModelConditionChanged();

	if (quiet != 0)
		return;

	bfmeHaltCO(1);

	const FXList *fx = m_moduleData->m_fx264;

	if (fx == 0)
		return;

	if (fx->isEmpty())
		return;

	fx->doFXPos(&obj->m_coord038, 0, 0.0f, 0);
}
