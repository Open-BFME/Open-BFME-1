// Twenty-four 33-byte __thiscall members of the shape
//
//     test ecx,ecx / je L
//     mov [ecx+OFF],DIR32 / mov [ecx],DIR32 / ret
//   L: xor eax,eax / mov [eax],DIR32 / mov [ecx],DIR32 / ret
//
// WHAT THE BYTES SHOW.  The null path is not a guard -- it stores through the
// null pointer it just made and then through ecx as well, so it would fault
// either way.  It is the optimiser cloning the tail of `p = ecx ? ecx+OFF : 0`
// into both arms and folding the addend into the addressing mode on the
// non-null arm.  That null-checked add is MSVC's derived-to-base pointer
// adjustment, and it fires for a NAMED base-pointer conversion of `this` while
// an ordinary inherited-member access does NOT: the probe pair
//
//     WideSlot *s = this; s->m_a = &A;    ->  33 bytes, exactly retail
//     m_a = &A;                           ->  14 bytes, no null check
//
// is what decides this body.  So the source names the base subobject through
// its own pointer before storing, and the second store goes to the leading
// subobject at offset 0.  THE ORDER OF THE TWO STORES IS SOURCE ORDER: base
// slot first, offset-0 slot second.
//
// TWO AXES: the base subobject offset (4 for twelve members, 8 for the other
// twelve) and the two stored addresses.  The addresses are DIR32 sites, read
// from retail rather than asserted; retail's are a five-entry table of code
// pointers at offset 0 (0x00D11D20 for the offset-4 members, 0x00D11D90 for
// the offset-8 ones) and one of six descriptor blocks for the base slot.  The
// pairing of table with offset is consistent across all twenty-four, which is
// what makes the two-axis reading real rather than over-fitted.
//
// IDENTITY IS NOT RECOVERED. Names are address-derived, the stored blocks are
// existing vtables, and a member that stores `this`-relative slots asserts
// less than a constructor would.

class WideDesc;

extern "C" const WideDesc __identifier("??_7PolymorphicVptrBase0110F978@@6B@");
extern "C" const WideDesc __identifier("??_7PolymorphicVptrBase01073760@@6B@");
extern "C" const WideDesc __identifier("??_7BigMiNarrowC@@6B@");
extern "C" const WideDesc __identifier("??_7BigMiNarrowD@@6B@");
extern "C" const WideDesc __identifier("??_7BigMiNarrowE@@6B@");
extern "C" const WideDesc __identifier("??_7BigMiWide@@6B@");
extern "C" const WideDesc __identifier("??_7PolymorphicVptrBase01111D20@@6B@");
extern "C" const WideDesc __identifier("??_7BigMiHead@@6B@");

#define WideA005E9480 __identifier("??_7PolymorphicVptrBase0110F978@@6B@")
#define WideB005E9480 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E94E0 __identifier("??_7PolymorphicVptrBase0110F978@@6B@")
#define WideB005E94E0 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E96C0 __identifier("??_7PolymorphicVptrBase01073760@@6B@")
#define WideB005E96C0 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E9720 __identifier("??_7PolymorphicVptrBase01073760@@6B@")
#define WideB005E9720 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E98E0 __identifier("??_7BigMiNarrowC@@6B@")
#define WideB005E98E0 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E9940 __identifier("??_7BigMiNarrowC@@6B@")
#define WideB005E9940 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E9B30 __identifier("??_7BigMiNarrowD@@6B@")
#define WideB005E9B30 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E9B90 __identifier("??_7BigMiNarrowD@@6B@")
#define WideB005E9B90 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E9D50 __identifier("??_7BigMiNarrowE@@6B@")
#define WideB005E9D50 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E9DB0 __identifier("??_7BigMiNarrowE@@6B@")
#define WideB005E9DB0 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E9F90 __identifier("??_7BigMiWide@@6B@")
#define WideB005E9F90 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005E9FF0 __identifier("??_7BigMiWide@@6B@")
#define WideB005E9FF0 __identifier("??_7PolymorphicVptrBase01111D20@@6B@")
#define WideA005EA4A0 __identifier("??_7PolymorphicVptrBase0110F978@@6B@")
#define WideB005EA4A0 __identifier("??_7BigMiHead@@6B@")
#define WideA005EA500 __identifier("??_7PolymorphicVptrBase0110F978@@6B@")
#define WideB005EA500 __identifier("??_7BigMiHead@@6B@")
#define WideA005EA760 __identifier("??_7PolymorphicVptrBase01073760@@6B@")
#define WideB005EA760 __identifier("??_7BigMiHead@@6B@")
#define WideA005EA7C0 __identifier("??_7PolymorphicVptrBase01073760@@6B@")
#define WideB005EA7C0 __identifier("??_7BigMiHead@@6B@")
#define WideA005EA980 __identifier("??_7BigMiNarrowC@@6B@")
#define WideB005EA980 __identifier("??_7BigMiHead@@6B@")
#define WideA005EAA20 __identifier("??_7BigMiNarrowC@@6B@")
#define WideB005EAA20 __identifier("??_7BigMiHead@@6B@")
#define WideA005EAC20 __identifier("??_7BigMiNarrowD@@6B@")
#define WideB005EAC20 __identifier("??_7BigMiHead@@6B@")
#define WideA005EAC80 __identifier("??_7BigMiNarrowD@@6B@")
#define WideB005EAC80 __identifier("??_7BigMiHead@@6B@")
#define WideA005EAE40 __identifier("??_7BigMiNarrowE@@6B@")
#define WideB005EAE40 __identifier("??_7BigMiHead@@6B@")
#define WideA005EAEE0 __identifier("??_7BigMiNarrowE@@6B@")
#define WideB005EAEE0 __identifier("??_7BigMiHead@@6B@")
#define WideA005EB100 __identifier("??_7BigMiWide@@6B@")
#define WideB005EB100 __identifier("??_7BigMiHead@@6B@")
#define WideA005EB160 __identifier("??_7BigMiWide@@6B@")
#define WideB005EB160 __identifier("??_7BigMiHead@@6B@")

class WideLead4
{
public:
	const WideDesc *m_b;
};

class WideLead8
{
public:
	const WideDesc *m_b;
	void *m_pad;
};

class WideSlot
{
public:
	const WideDesc *m_a;
};

#define WIDE_SLOT_SETUP( NAME, LEAD )                                     	                                    	                                    	class Rva##NAME : public LEAD, public WideSlot                        	{                                                                     	public:                                                               		void setup();                                                     	};                                                                    	void Rva##NAME::setup()                                               	{                                                                     		WideSlot *slot = this;                                            		slot->m_a = &WideA##NAME;                                         		m_b = &WideB##NAME;                                               	}

WIDE_SLOT_SETUP( 005E9480, WideLead4 )
WIDE_SLOT_SETUP( 005E94E0, WideLead4 )
WIDE_SLOT_SETUP( 005E96C0, WideLead4 )
WIDE_SLOT_SETUP( 005E9720, WideLead4 )
WIDE_SLOT_SETUP( 005E98E0, WideLead4 )
WIDE_SLOT_SETUP( 005E9940, WideLead4 )
WIDE_SLOT_SETUP( 005E9B30, WideLead4 )
WIDE_SLOT_SETUP( 005E9B90, WideLead4 )
WIDE_SLOT_SETUP( 005E9D50, WideLead4 )
WIDE_SLOT_SETUP( 005E9DB0, WideLead4 )
WIDE_SLOT_SETUP( 005E9F90, WideLead4 )
WIDE_SLOT_SETUP( 005E9FF0, WideLead4 )
WIDE_SLOT_SETUP( 005EA4A0, WideLead8 )
WIDE_SLOT_SETUP( 005EA500, WideLead8 )
WIDE_SLOT_SETUP( 005EA760, WideLead8 )
WIDE_SLOT_SETUP( 005EA7C0, WideLead8 )
WIDE_SLOT_SETUP( 005EA980, WideLead8 )
WIDE_SLOT_SETUP( 005EAA20, WideLead8 )
WIDE_SLOT_SETUP( 005EAC20, WideLead8 )
WIDE_SLOT_SETUP( 005EAC80, WideLead8 )
WIDE_SLOT_SETUP( 005EAE40, WideLead8 )
WIDE_SLOT_SETUP( 005EAEE0, WideLead8 )
WIDE_SLOT_SETUP( 005EB100, WideLead8 )
WIDE_SLOT_SETUP( 005EB160, WideLead8 )
