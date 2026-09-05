// ?method@Rva003A3770Obj@@QAEXPAX@Z
// partial score=0.02 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: partial reconstruction of the 474 B dump body at 0x003A3770.
// NOT byte-exact -- banked as a partial for whoever draws this body next.
//
// From a capstone disassembly of the retail dump bytes (Code/gen_asm/d_0039d230.asm,
// PROC ?d_003a3770@@YAXXZ):
//
//   Full SEH frame (fs:[0] push/pop of a 3-scope handler chain, EH cookie
//   0x0101cf39) around a ~0xD0-byte local frame -- so the real function
//   almost certainly contains a `catch`/local destructor requiring one, not
//   just object code inflation.
//
//   ecx (this) -> eax = this->+0x30 (saved before frame alloc); edi = this+0x2c
//   (a sub-object -- the pinned callee at 0x1D3EA is
//   ?handle@Gen0001D3EA@@QAEXHH@Z, an address-derived provisional name, called
//   as edi->handle(this_orig_begin_ptr, this_orig+0x30_value) BEFORE the vector
//   fields are otherwise touched -- looks like a reset/rebind on a handle
//   wrapping the vector's old begin/end).
//
//   Then, if a `this` parameter (mov ebp,[esp+0xe8], i.e. an incoming arg
//   spilled past the frame) is NULL, skip straight to a single-shot cleanup
//   call (0x36241, an ICF-shared trivial destructor -- symbols.csv pins it
//   under several unrelated class names, so it does NOT prove class identity
//   here despite one of those names being FlightDeckBehavior::RunwayInfo;
//   that vector's element is 0x88 B in the BFME header, not the 0xB8 this
//   body's vector advances by, so that lead is refuted) then unwind.
//
//   Otherwise: two calls through j_00022f0c/j_00029f19 look like
//   begin()/end() plumbing (0x0002798F is already pinned as
//   `_M_insert_overflow<Rva003A35A0Element>`, the SAME 0xB8-wide element as
//   the landed RvaVectorPushBack.cpp/U6StlAllocatorWidths.cpp instantiations,
//   so this function's vector at edi (this+0x2c) is that same
//   vector<Rva003A35A0Element> family, just still unidentified by class).
//   If the vector is empty (edi[1]==edi[2], i.e. begin==end) it takes the
//   push_back-style overflow path (0x2798F) with a value built from
//   ebp+0x14/+0x18 fields (an incoming record) padded with two literal 1s;
//   otherwise it loops: for each element, compute a squared distance from
//   three floats at ebp+0xc/+0x10/+0x14 to the element's own first three
//   floats, compare against the squared-radius constant at 0x0107FAC4, and
//   if within range call bfmeAssign@BfmeCopyElementD (0x00024BA9, already
//   pinned, a real element-copy loop callee) to compact the element out,
//   else advance to the next element (`add eax/ecx, 0xb8`) and repeat via
//   j_00029f19 again. Falls out of the loop either by exhausting the vector
//   (calls 0x2798F to insert-overflow-append ebp's record, same shape as the
//   empty-vector path) or by finding a distance match.
//
// Nothing above proves the owning class -- 0x0001D3EA, 0x00022F0C,
// 0x00029F19 and 0x0001F573 are all address-derived provisional pins with
// no independent class evidence, and the vector element (0xB8 B) is the
// same still-unidentified family as target 0x003A2070's vector in this same
// dump file (RvaVectorPushBack.cpp / U6StlAllocatorWidths.cpp both say
// "identity is not recovered"). Landing the real name needs whichever body
// eventually claims that 0xB8-element vector's owning class; this body and
// 0x003A2070 are almost certainly the same class's methods (same vector,
// same edi = this+0x2c sub-object pattern) and should be converted together
// once one of them gets a name.
//
// Only the very first few bytes (SEH prologue) are attempted here; the loop
// body, the two vector-empty/non-empty branches and the floating point
// compare are NOT implemented. This is a documentation-heavy partial, not a
// near-miss.

extern "C" void Rva003A3770_handle_1D3EA( void *thisPtr, int a, int b ); // ?handle@Gen0001D3EA@@QAEXHH@Z, 0x0001D3EA (pinned)

struct Rva003A3770Vec
{
	char *m_begin;
	char *m_end;
	char *m_capEnd;
};

class Rva003A3770Obj
{
public:
	void method( void *arg );

private:
	char             m_pad[ 0x2C ];
	Rva003A3770Vec   m_vec;   // +0x2C/+0x30/+0x34, element width 0xB8, same family as
	                          // RvaVectorPushBack.cpp's Rva003A35A0Element
};

void Rva003A3770Obj::method( void *arg )
{
	// SEH-frame + the single handle() reset call is as far as this stash goes;
	// see the header comment for the rest of the retail control flow.
	(void)arg;
}
