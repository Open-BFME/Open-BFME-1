// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: _STL::__copy<const W3DAnimationInfo *, W3DAnimationInfo *, int>,
// retail 0x003B3800, 99 bytes. The name sat on the 5-byte incremental-link
// thunk at 0x000417EF; the body it jumps to carried no ledger row.
//
// The element is the sixteen bytes its _M_allocate_and_copy sibling measures,
// and this body splits them: the assignment calls StringBase<char>::set on +0,
// which is the AsciiString name, then copies +4 through +0x0F as three plain
// dwords. That block is a nested POD whose compiler-generated operator= folds
// into the loop -- hence the two hoisted +4 cursors retail keeps in ebx/ebp.
//
// The address is taken rather than called so MSVC emits the inline template
// out of line without an inline_depth pragma, which would also stop the
// element's assignment from folding into the loop.
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

template <class T>
class StringBase
{
public:
	StringBase &operator=(const StringBase &other) { set(other); return *this; }

	void set(const StringBase &other);			// retail 0x00887C90

private:
	T *m_data;
};

struct BfmeW3DAnimationInfoTail
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
public:
	StringBase<char> m_bfmeName;				// +0x00
	BfmeW3DAnimationInfoTail m_bfmeTail;			// +0x04
};

typedef W3DAnimationInfo *(*BfmeW3DAnimationInfoCopyFn)(
	const W3DAnimationInfo *, const W3DAnimationInfo *,
	W3DAnimationInfo *, const _STL::random_access_iterator_tag &, int *);

BfmeW3DAnimationInfoCopyFn BfmeW3DAnimationInfoConstCopyAnchor =
	&_STL::__copy<const W3DAnimationInfo *, W3DAnimationInfo *, int>;
