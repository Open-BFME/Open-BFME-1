// ?_M_fill_insert@?$vector@URva0087FDC0Element@@V?$allocator@URva0087FDC0Element@@@_STL@@@_STL@@QAEXPAURva0087FDC0Element@@IABU3@@Z
// cl: /O2 /Ob1 /G6 /GX-
// stlport

#include <vector>

class BFMERetailAsciiString
{
public:
	void releaseBuffer() throw();
	BFMERetailAsciiString &operator=(const BFMERetailAsciiString &);
private:
	void *m_data;
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	int m_minorRadius;
	int scalar10;
	int scalar14;
	float m_offsetZ;
	BFMERetailAsciiString m_name;
	bool m_enabled;
	char padding[3];

	GeometryShape(const GeometryShape &) throw();
	~GeometryShape() throw() { m_name.releaseBuffer(); }
	GeometryShape &operator=(const GeometryShape &) throw();
};

struct Rva0087FDC0Element : GeometryShape
{
	Rva0087FDC0Element(const Rva0087FDC0Element &other) throw()
		: GeometryShape(other) {}
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

// ?bfmeFillBE@@YAPAUBfmeElemBE@@PAU1@IABU1@ABUBfmeFalseBE@@@Z present-unmatched
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


