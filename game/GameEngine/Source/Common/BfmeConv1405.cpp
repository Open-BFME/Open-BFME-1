// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5 conversions.

#include <vector>

extern "C" void *memcpy(void *d, const void *s, unsigned n);
#pragma intrinsic(memcpy)

struct BfmeElemVKN
{
	char m_bfmePad[0xec];
};

extern template void _STL::vector<BfmeElemVKN>::_M_insert_overflow(
	BfmeElemVKN *, const BfmeElemVKN &, const _STL::__false_type &, unsigned int, bool);

class BfmeVecVKN : public _STL::vector<BfmeElemVKN>
{
public:
	void bfmePushVKN(const BfmeElemVKN *e);
};

void BfmeVecVKN::bfmePushVKN(const BfmeElemVKN *e)
{
	BfmeElemVKN *cur = this->_M_finish;
	if (cur != this->_M_end_of_storage._M_data)
	{
		if (cur)
			memcpy(cur, e, 0xec);
		++this->_M_finish;
		return;
	}
	this->_M_insert_overflow(cur, *e,
		reinterpret_cast<const _STL::__false_type &>(e), 1, true);
}
