// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the 20-byte kind-of test at 0x001DCC80, address-derived name.
// Converted out of Code/gen_asm/d_001db160.asm.
//
// IDENTITY IS NOT ASSERTED. The class name is the address of the body. What
// the bytes say is only the shape: a __thiscall predicate that takes one
// Thing * and forwards two of its own KindOf masks -- at this+0x08 and
// this+0x20 -- to Thing::isKindOfMulti as (mustBeSet, mustBeClear).
//
// Relocation note (this file exists as a measurement, see re_attempts
// "reloc-gating-sample-of-16"): the single REL32 here targets ILT thunk
// 0x0003DCCB, whose body 0x00132B20 is the already-matched
// ?isKindOfMulti@Thing@@... row. build.py's build_call_thunks discovers the
// thunk from the image itself and adds it as a candidate for that name, so
// naming the callee in C++ was enough -- no symbols.csv pin, no dependency
// on any other unconverted row.

class Thing;

template <int NUMBITS> class BitFlags
{
public:
	char m_bits[16];
};

typedef BitFlags<116> KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const;
};

class Gen_001dcc80
{
public:
	bool test(Thing *thing) const;

private:
	char m_unknown00[8];
	KindOfMaskType m_mustBeSet;			// +0x08
	char m_unknown18[8];
	KindOfMaskType m_mustBeClear;			// +0x20
};

bool Gen_001dcc80::test(Thing *thing) const
{
	return thing->isKindOfMulti(m_mustBeSet, m_mustBeClear);
}
