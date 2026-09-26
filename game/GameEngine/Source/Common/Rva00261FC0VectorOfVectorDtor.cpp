// cl: -GX
// stlport
//
// Open-BFME7: fuzzy twin of R5VectorDtorEHFramed.cpp's
// _STL::vector<_STL::vector<int> > destructor family (same -GX exception
// frame shape: three push fs:[0] frame, EH state 0 across the destroy loop,
// -1 once the elements are gone and only the outer buffer is left to free).
// Retail 0x00261FC0, 188 bytes. The outer element stride is 16 bytes (add
// esi,0x10), one word larger than a bare vector<int> (12 bytes), so the
// element is a small struct with a leading 4-byte field ahead of the nested
// vector<int> (begin/finish/end_of_storage at +4/+8/+0xC) -- only that
// leading field's own destructor work is absent (POD), matching the callee
// set (only ??3@YAXPAX@Z and the width-4 node-alloc _M_deallocate, no
// element-specific dtor call).
//
// IDENTITY IS NOT RECOVERED: no caller names this destructor. The element
// type is a stand-in carrying only the size and the nested vector<int>.

#include <vector>

struct Gen00261FC0Elem
{
	int m_leading;
	_STL::vector<int> m_inner;
};

template class _STL::vector<Gen00261FC0Elem>;
