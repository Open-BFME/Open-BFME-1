// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00170200, 261 bytes: STLport 4.5.3's
// _STL::vector<T>::operator=(const vector<T>&) for a 4-byte trivially
// copyable T.  The extent is the WHOLE body, not the 221 bytes the lift was
// anchored at: 0x001701D0's row ends at 0x001701F4 and int3 padding runs to
// 0x001701FF, so 0x00170200 is the 16-aligned start; the function's last
// instruction is the `pop esi; pop ebx; ret 4` at 0x00170300..0x00170304,
// giving 0x00170200 + 261 = 0x00170305.  Ghidra's own inventory agrees
// (ghidra_functions.csv: 0x170200,261,FUN_00570200), and the 0x28 bytes at
// 0x00170200..0x00170228 that the old row started at are the head of this
// same body (self-assign test, then _M_start/_M_finish loads), with no
// ret/jmp of their own.
//
// The element is 4 bytes and trivially copyable, read off the body itself
// (`sar`/`lea ... *4` throughout, no per-element ctor/dtor calls).  The name
// is address-derived on purpose: the one ILT entry that reaches this body,
// the five-byte thunk at 0x0000D8A5, is called from exactly three sites --
// Rva0018B8B0Holder::apply (0x0018B8F1), Rva00181EE0Owner::setFrom
// (0x00181F28) and BfmeThingCDF::bfmeGoCDF (0x00171E4F) -- and the first two
// are matched real C++ that type the assigned member as `_STL::vector<ObjectID>`
// / an int triplet, NOT as a science list.  The ScienceType name the lift
// carried belongs to a different retail copy of this same template body:
// 0x00018A70 (jmp 0x000BC4B0), which the ledger's own pin note ties to the
// PlayerTemplate science-vector assignment call site, and 0x000BC4B0 is the
// 261-byte p4pod instantiation landed as
// `??4?$vector@UGen_t_000bc4b0_p4pod@@...` in game/gen_small/tgrid_102.cpp.
// The AI CDF id list is not a ScienceVec, so the ScienceType spelling is not
// asserted here.
//
// Only the assignment member is claimed from this template instantiation.

#include <vector>

struct Rva00170200Elem
{
	int m_value;
};

// MSVC 7.1 cannot parse an explicit instantiation declarator for `operator=`
// (it reads the `=` as an initializer, C2556/C3190), so the class is
// instantiated the way every other landed p4pod container in this tree is and
// the row claims the one member the explicit instantiation is there for.
template class _STL::vector<Rva00170200Elem>;
