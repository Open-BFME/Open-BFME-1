// ?_M_fill_insert@?$vector@URva0087FDC0Element@@V?$allocator@URva0087FDC0Element@@@_STL@@@_STL@@QAEXPAURva0087FDC0Element@@IABU3@@Z
// partial score=0.99 date=2026-09-26
// cl: /O2 /Ob1 /G6 /GX-
// stlport

#include <vector>

class BFMERetailAsciiString
{
public:
	void releaseBuffer() throw();
	BFMERetailAsciiString &operator=(const BFMERetailAsciiString &);
};

struct Rva0087FDC0Element
{
	int type;
	float height;
	float majorRadius;
	int scalar0C;
	int scalar10;
	int scalar14;
	float offsetZ;
	BFMERetailAsciiString name;
	bool enabled;
	char padding[3];

	Rva0087FDC0Element(const Rva0087FDC0Element &) throw();
	~Rva0087FDC0Element() throw() { name.releaseBuffer(); }
	Rva0087FDC0Element &operator=(const Rva0087FDC0Element &) throw();
};

struct BfmeFalseBE {};

struct BfmeTailBE
{
	void *data;
	BfmeTailBE(const BfmeTailBE &);
};

struct BfmeElemBE
{
	int fields[7];
	BfmeTailBE name;
	char enabled;
	char padding[3];
};

__declspec(noinline) BfmeElemBE *bfmeFillBE(BfmeElemBE *first, unsigned count,
	const BfmeElemBE &value, const BfmeFalseBE &)
{
	for (; count > 0; --count, ++first)
		if (first != 0)
			new (first) BfmeElemBE(value);
	return first;
}

namespace _STL
{
	template <>
	__forceinline Rva0087FDC0Element *uninitialized_fill_n(
		Rva0087FDC0Element *first, unsigned count, const Rva0087FDC0Element &value)
	{
		BfmeFalseBE tag;
		return (Rva0087FDC0Element *)bfmeFillBE((BfmeElemBE *)first, count,
			*(const BfmeElemBE *)&value, tag);
	}
}

template void _STL::vector<Rva0087FDC0Element>::_M_fill_insert(
	Rva0087FDC0Element *, unsigned, const Rva0087FDC0Element &);
