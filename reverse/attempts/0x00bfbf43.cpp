// ?d_00bfbf43@@YAXXZ
// partial score=0.9 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// PARTIAL -- Unwind@00ffbf43 retail 0x00BFBF43 size 11:
//   mov ecx, dword ptr [ebp + 4]
//   add ecx, 4
//   jmp 0x41570d          ; ILT -> ??1Gen_uw_0001570d -> tg_00066fe0
//     tg_00066fe0 is object-symbol ??1?$_Vector_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ
//     (STLport _Vector_base<int, allocator<int>>::~_Vector_base), matching
//     the REAL match for that same destructor at 0x0081D920
//     (Code/Libraries/Source/WWVegas/WWLib/stlport_vector_base_int_dtor.cpp).
//
// This TU reproduces the funclet skeleton exactly (same 3 instructions, same
// `add ecx,4` member offset, same jmp-to-vector_base-dtor target) by giving a
// host object a 4-byte member ahead of a `vector<int>` member ahead of a
// member whose constructor can throw -- same shape as the $L314 precedent at
// 0x00C1FC1D (Rva00C1FC1DVecDtor.cpp). tools/probe.py's $L4236 funclet for
// this TU is byte-identical to retail except ONE byte: the spilled-this
// load's displacement is `f0` (ebp-0x10) here vs retail's `04` (ebp+4).
//
// Every sibling funclet in retail's own table immediately around 0x00BFBF43
// (0x00BFBF30..0x00BFBF52, dis_retail 0x00BFBF20 0x60) spills `this` at
// [ebp-0x10] like ours does; only this funclet (and the operator-delete
// funclet at 0x00BFBF75, already a separate ledger row) uses [ebp+4]. That
// means 0x00BFBF43's real parent is a DIFFERENT, smaller-framed function than
// the [ebp-0x10] group -- adjacency in the retail table is not proof of a
// shared parent, and AGENTS.md forbids inferring the parent from adjacency,
// so this TU cannot legitimately go further without real FuncInfo/parent
// evidence for THIS specific funclet. The `ebp+4` vs `ebp-0x10` gap is a
// frame-shape question (how MSVC 7.1 anchors its implicit funclet EBP
// relative to the EstablisherFrame, driven by the real parent's total local
// frame size / register pressure), not a wrong-shape one: three distinct
// levers were tried (plain /EHsc, /EHsc /O2, and tools/eh_levers.py's
// throw/ehsc/stlp/nodelete combinations via tools/shape_search.py) and none
// moved the displacement. Logged `partial` via tools/re_log.py rather than
// landed. t=30min model=sonnet
#include <vector>

class BfmeThrowerBFBF43
{
public:
	BfmeThrowerBFBF43();
};

class Rva00BFBF43Host
{
public:
	Rva00BFBF43Host();
private:
	int m_before;
	_STL::vector<int> m_ints;
	BfmeThrowerBFBF43 m_tail;
};

Rva00BFBF43Host::Rva00BFBF43Host()
{
}
