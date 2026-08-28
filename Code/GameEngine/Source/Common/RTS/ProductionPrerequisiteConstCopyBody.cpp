// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: _STL::__copy<const ProductionPrerequisite *, ProductionPrerequisite *, int>,
// retail 0x003B6100, 92 bytes. The name sat on a 5-byte incremental-link
// thunk at 0x000078E7; the body it jumps to carried no ledger row.
//
// The element is the same 0x18 bytes its vector<> siblings model, but this
// body pins the layout down: the inlined assignment stores a dword at +4 and
// a byte at +8, then calls a member operator= on +0xC, and never touches +0.
// The untouched +0 is the vptr -- the compiler-generated operator= copies the
// members and leaves the vtable pointer alone -- which is the same virtual
// destructor _M_clear proves the element has.
//
// The member at +0xC is 12 bytes with an out-of-line operator=, and the
// target it calls (0x00064E90 through the ILT at 0x00048013) is an
// _Rb_tree<int, ...>::operator=, so it is a map keyed by Int.
//
// The address is taken rather than called so MSVC emits the inline template
// out of line without an inline_depth pragma, which would also stop the
// element's assignment from folding into the loop the way retail has it.
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

class BfmeIntMap
{
public:
	BfmeIntMap &operator=(const BfmeIntMap &other);		// retail 0x00064E90

private:
	int m_bfmeBody[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	virtual ~ProductionPrerequisite();

	int m_bfmeA;						// +0x04
	bool m_bfmeB;						// +0x08
	BfmeIntMap m_bfmeMap;					// +0x0C
};

typedef ProductionPrerequisite *(*BfmeProductionPrerequisiteCopyFn)(
	const ProductionPrerequisite *, const ProductionPrerequisite *,
	ProductionPrerequisite *, const _STL::random_access_iterator_tag &, int *);

BfmeProductionPrerequisiteCopyFn BfmeProductionPrerequisiteConstCopyAnchor =
	&_STL::__copy<const ProductionPrerequisite *, ProductionPrerequisite *, int>;
