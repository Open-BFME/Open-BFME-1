// Open-BFME5 conversions.

// The +4 string member is retail's StringBase<char> (4-byte Header*), and the
// per-element copy at 0x00887C90 is the matched StringBase<char>::set body
// (StringBase.cpp), so this TU calls that body under its own name.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// Retail 0x002DFC60 is STLport's _STL::__copy_backward for the (dword, string,
// byte) record S4SortElem12: its only proven caller, __linear_insert
// 0x002E0FE0 (stlport_linear_insert_s4sortelem12.cpp), reaches it through
// ILT 0x00002289 with STLport's five arguments (first, last, result, tag,
// distance*). The body reads only the first three. The element layout is the
// one identity_evidence/00532740-s4sortelem12-layout-split.md keeps under
// S4SortElem12.
struct S4SortElem12
{
	int m_bfme00;
	StringBase<char> m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
};

namespace _STL
{

struct random_access_iterator_tag
{
};

// The element type is a placeholder, so the STL template spelling cannot be
// checked against retail's thunk table; the function keeps the address-scoped
// name its caller and the ILT pin already use.
S4SortElem12 *BfmeCopyBackward002DFC60(S4SortElem12 *first, S4SortElem12 *last,
	S4SortElem12 *result, const random_access_iterator_tag &, int *)
{
	int n = last - first;

	if (n > 0)
	{
		int i = n;

		do
		{
			--last;
			--result;
			result->m_bfme00 = last->m_bfme00;
			result->m_bfme04.set(last->m_bfme04);
			result->m_bfme08 = last->m_bfme08;
		} while (--i);
	}
	return result;
}

}
