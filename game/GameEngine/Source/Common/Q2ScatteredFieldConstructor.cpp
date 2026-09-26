// One 23-byte constructor that sets three dwords in an order that is NOT the
// order they sit in:
//
//   mov eax,ecx                    ; a constructor returns this
//   mov [eax+4],0xFFFFFFFF
//   mov [eax],  <TABLE ADDRESS>
//   mov [eax+8],0
//   ret
//
// WHY IT IS HERE ALONE.  This body was grouped with the eleven two-base
// constructors at 0x005EE6B0 because with every immediate blanked the opcodes
// are the same three `mov [reg+disp],imm32` stores.  They are not the same
// thing.  Those store three VTABLE addresses; this one stores -1, an address,
// and 0.
//
// THE FIRST DWORD IS NOT A VPTR, and the store order is what says so.  MSVC
// writes a class's vptr before ANY member initialiser, without exception, and
// here the offset-0 store is the SECOND of the three -- so offset 0 is an
// ordinary member holding an address.  (The address does land on a run of code
// pointers in .rdata, which is what a vtable looks like from the outside; the
// bytes say only that this class stores its address, not that this class uses
// it as a vtable.)
//
// THE ORDER ALSO RULES OUT AN INITIALISER LIST.  A member-initialiser list is
// emitted in DECLARATION order, which for members at 0, 4 and 8 means
// [eax] then [eax+4] then [eax+8]; writing this constructor that way produces
// the same 23 bytes with the first two stores swapped.  Only assignments in
// the constructor BODY keep source order, so these three lines are statements,
// in this order.
//
// 19 of the 23 bytes are concrete; only the table address comes from the
// target.
//
// WHAT THE BYTES DO NOT DECIDE.  The types: -1 and 0 are int-width and could
// be enumerators, and the -1 is only "all bits set".  Whether the class has
// more members past offset 8.  What the table is.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

extern void *g_Rva00789720Table[];					///< retail 0x01126CB0

class Rva00789720
{
public:
	Rva00789720();

	void *m_table;									///< retail this+0x00
	int m_unreconstructed_04;						///< set to -1
	int m_unreconstructed_08;						///< set to 0
};

Rva00789720::Rva00789720()
{
	m_unreconstructed_04 = -1;
	m_table = g_Rva00789720Table;
	m_unreconstructed_08 = 0;
}
