// cl: /O2 /Ob1 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "string_base.h"
#include <vector>

struct Gen_t_002e13b0_p12cd;

// Retail ILT 0x00033640 reaches this existing vector assignment.
extern template class _STL::vector<Gen_t_002e13b0_p12cd>;

struct BfmeSubA100
{
	char m_bfmeBytes[12];
};

struct BfmeElemA100
{
	StringBase<char> m_bfmeKey;
	unsigned char m_bfmeFlag;
	char m_bfmePad[3];
	BfmeSubA100 m_bfmeSub;
};

BfmeElemA100 *bfmeCopyA100(const BfmeElemA100 *first, const BfmeElemA100 *last, BfmeElemA100 *dest)
{
	if (last - first > 0)
	{
		int count = last - first;

		do
		{
			dest->m_bfmeKey.set(first->m_bfmeKey);
			dest->m_bfmeFlag = first->m_bfmeFlag;
			*reinterpret_cast<_STL::vector<Gen_t_002e13b0_p12cd> *>(&dest->m_bfmeSub) =
				*reinterpret_cast<const _STL::vector<Gen_t_002e13b0_p12cd> *>(&first->m_bfmeSub);
			++first;
			++dest;
		}
		while (--count);
	}

	return dest;
}
