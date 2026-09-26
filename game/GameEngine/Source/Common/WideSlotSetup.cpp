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
// IDENTITY IS NOT RECOVERED.  Names are address-derived, the stored blocks are
// undefined externs, and a member that stores `this`-relative slots asserts
// less than a constructor would.

class WideDesc;

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

#define WIDE_SLOT_SETUP( NAME, LEAD )                                     	extern const WideDesc WideA##NAME;                                    	extern const WideDesc WideB##NAME;                                    	class Rva##NAME : public LEAD, public WideSlot                        	{                                                                     	public:                                                               		void setup();                                                     	};                                                                    	void Rva##NAME::setup()                                               	{                                                                     		WideSlot *slot = this;                                            		slot->m_a = &WideA##NAME;                                         		m_b = &WideB##NAME;                                               	}

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
