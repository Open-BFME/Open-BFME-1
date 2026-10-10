// cl: /O2 /Ob0 /G6
// stlport

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include <vector>

struct Rva0087FDC0Element;
extern template class _STL::vector<Rva0087FDC0Element>;
extern "C" void __identifier("?releaseBuffer@?$StringBase@D@@AAEXXZ")();

struct BfmeTail60
{
	char *m_p;
	void release();
};

struct BfmeElem60
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTail60 m_1C;
	char m_20;
	char m_pad[3];
};

class BfmeVec60
{
public:
	void resize(unsigned n, BfmeElem60 value);
	BfmeElem60 *erase(BfmeElem60 *first, BfmeElem60 *last);
	void insert(BfmeElem60 *pos, unsigned count, const BfmeElem60 &value);

	BfmeElem60 *_M_start;
	BfmeElem60 *_M_finish;
	BfmeElem60 *_M_end_of_storage;
};

void BfmeVec60::resize(unsigned n, BfmeElem60 value)
{
	union { void (*raw)(); void (BfmeTail60::*member)(); } release;
	release.raw = __identifier("?releaseBuffer@?$StringBase@D@@AAEXXZ");
	if (n < (unsigned)(_M_finish - _M_start))
	{
		erase(_M_start + n, _M_finish);
		(value.m_1C.*release.member)();
	}
	else
	{
		reinterpret_cast<_STL::vector<Rva0087FDC0Element> *>(this)->_M_fill_insert(
			reinterpret_cast<Rva0087FDC0Element *>(_M_finish),
			n - (unsigned)(_M_finish - _M_start),
			*reinterpret_cast<const Rva0087FDC0Element *>(&value));
		(value.m_1C.*release.member)();
	}
}
