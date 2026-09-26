// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// The two out-of-line __uninitialized_copy bodies of this family, over the two
// element types the ProductionPrerequisite vectors hold:
//
//   0x003AB7A0  45B  __uninitialized_copy<const PrereqUnitRec *, PrereqUnitRec *>
//   0x003ABB40  45B  __uninitialized_copy<const ProductionPrerequisite *, ProductionPrerequisite *>
//
// Their 5-byte incremental-link thunks at 0x000178B4 and 0x0001FFEB live
// elsewhere and reach these; the dup_ rows at 0x005827C0 and 0x00784DF0 are
// byte-identical copies of these bodies at other addresses and ride with them.
//
// In both, the per-element _Construct is DECLARED WITHOUT A BODY so that it
// stays out of line, exactly as retail calls it. That is the load-bearing part
// of both files and it is now written once.
//
// THESE MERGE WHERE THE _Construct PAIR COULD NOT, and the difference is worth
// keeping because the two pairs look identical from outside. Both pairs are a
// ProductionPrerequisite file and a PrereqUnitRec file, same flags, same shape,
// each hand-writing an _STL template and then explicitly instantiating it. The
// Construct pair cannot share a TU because the two files define the SAME
// template, _STL::_Construct<T, U>, with DIFFERENT bodies -- one forwarding to
// ProductionPrerequisiteConstructShim and one to PrereqUnitRecConstructShim --
// and one TU cannot hold two definitions of one template. Here the shared
// template's body is character-for-character the same in both files, so one
// definition serves both instantiations.
//
// So the test for this shape is not "are these two files alike" but "do they
// give the shared template the same body". The Construct pair also spelled
// ProductionPrerequisite as a NAMESPACE where this one spells it a class, which
// is a second, independent reason that pair stays apart.
//
// The family has a third pair of the same appearance and the test settles it
// too. ProductionPrerequisiteAllocateAndCopyBody.cpp and
// PrereqUnitRecAllocateAndCopyBody.cpp share
// vector<T, allocator<T> >::_M_allocate_and_copy, and their two copies of it are
// identical except for the name of the per-element construct helper it calls --
// BfmeProductionPrerequisiteConstruct against BfmeElementConstruct. Those two
// names are separately PINNED, to different ILTs: 0x000027A2 and 0x0003C1A0.
// So the shared template cannot be written once, because its body has to name
// one helper or the other, and renaming either to unify them moves that call off
// its pin. Not mergeable, and for a subtler reason than the Construct pair --
// there the two bodies forward to differently-named shims, here they call
// differently-named pinned helpers, but the consequence is the same.
//
// Three visually identical pairs, then, and only this one merges. The
// difference is never how alike the files look; it is whether the template they
// share can have one body.
//
// One consequence of merging: ProductionPrerequisite is 24 bytes here and
// PrereqUnitRec is 12, stated together for the first time. The 24 is a third
// witness to a size the two __copy rows already agree on while disagreeing
// about what fills it -- ProductionPrerequisiteCopyBody.cpp reads that element
// as a string at +0 with a byte at +4, ProductionPrerequisiteConstCopyBody.cpp
// as a vptr at +0 that the assignment never touches with a dword at +4. Both
// byte-verify, so at most one of them is named for the class it copies; the
// question is with whoever holds 0x00753280's callers, and the size at least is
// not in doubt.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	int m_raw[6];							// 24 bytes

	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
	struct PrereqUnitRec
	{
		int m_raw[3];						// 12 bytes
	};
};

namespace _STL
{
struct __false_type
{
};

// No body on purpose: retail calls this out of line, once per element.
template <class T1, class T2>
void _Construct(T1 *destination, const T2 &value);

template <class In, class Out>
Out __uninitialized_copy(In first, In last, Out result, const __false_type &)
{
	Out current = result;
	while (first != last)
	{
		_Construct(current, *first);
		++first;
		++current;
	}
	return current;
}

// ??$__uninitialized_copy@PBUPrereqUnitRec@ProductionPrerequisite@@PAU12@@_STL@@...
template ProductionPrerequisite::PrereqUnitRec *__uninitialized_copy<const ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *>(
    const ProductionPrerequisite::PrereqUnitRec *, const ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, const __false_type &);

// ??$__uninitialized_copy@PBVProductionPrerequisite@@PAV1@@_STL@@...
template ProductionPrerequisite *__uninitialized_copy<const ProductionPrerequisite *, ProductionPrerequisite *>(
    const ProductionPrerequisite *, const ProductionPrerequisite *, ProductionPrerequisite *, const __false_type &);
}
