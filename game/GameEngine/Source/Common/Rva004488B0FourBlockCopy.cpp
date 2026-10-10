// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>

struct Gen_t_00443e40_p8cd;

// ILT 0x0002E1C7 reaches the existing clear body at 0x00443E40.
template <> void _STL::_List_base<Gen_t_00443e40_p8cd,
	_STL::allocator<Gen_t_00443e40_p8cd> >::clear();

struct Rva004488B0Block
{
	void *first;
	void *second;
	void *third;
};

class BfmeSubBQC
{
};

class Rva004488B0FourBlockRecord
{
public:
	void copy(const Rva004488B0Block &a,
		const Rva004488B0Block &b, const Rva004488B0Block &c,
		const Rva004488B0Block &d);

private:
	Rva004488B0Block m_a;
	Rva004488B0Block m_b;
	Rva004488B0Block m_c;
	Rva004488B0Block m_d;
	BfmeSubBQC m_bqc;
};

void Rva004488B0FourBlockRecord::copy(
	const Rva004488B0Block &a, const Rva004488B0Block &b,
	const Rva004488B0Block &c, const Rva004488B0Block &d)
{
	m_a = b;
	m_b = a;
	m_c = c;
	m_d = d;
	reinterpret_cast<_STL::_List_base<Gen_t_00443e40_p8cd,
		_STL::allocator<Gen_t_00443e40_p8cd> > *>(&m_bqc)->clear();
}
