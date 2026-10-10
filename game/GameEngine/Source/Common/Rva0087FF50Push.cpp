// cl: /O2 /Ob0 /G6

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" void __identifier("??0?$StringBase@D@@AAE@ABV0@@Z")();

struct BfmeElemCD;
struct BfmeFalseCD;
class BfmeVecCD
{
public:
	void overflow(BfmeElemCD *, const BfmeElemCD &, const BfmeFalseCD &, unsigned, bool);
};

struct BfmeTail50
{
};

struct BfmeElem50
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTail50 m_0C;
};

struct BfmeFalse50
{
};

class BfmeVec50
{
public:
	void push_back(const BfmeElem50 *value);

	BfmeElem50 *_M_start;
	BfmeElem50 *_M_finish;
	BfmeElem50 *_M_end_of_storage;
};

void BfmeVec50::push_back(const BfmeElem50 *value)
{
	if (_M_finish != _M_end_of_storage)
	{
		BfmeElem50 *f = _M_finish;
		if (f)
		{
			const BfmeElem50 *v = value;
			f->m_00 = v->m_00;
			f->m_04 = v->m_04;
			f->m_08 = v->m_08;
			union { void (*raw)(); void (StringBase<char>::*member)(const StringBase<char> &); } copy;
			copy.raw = __identifier("??0?$StringBase@D@@AAE@ABV0@@Z");
			(reinterpret_cast<StringBase<char> *>(&f->m_0C)->*copy.member)(
				*reinterpret_cast<const StringBase<char> *>(&v->m_0C));
		}
		++_M_finish;
	}
	else
	{
		reinterpret_cast<BfmeVecCD *>(this)->overflow(
			reinterpret_cast<BfmeElemCD *>(_M_finish),
			*reinterpret_cast<const BfmeElemCD *>(value),
			reinterpret_cast<const BfmeFalseCD &>(value), 1, true);
	}
}
