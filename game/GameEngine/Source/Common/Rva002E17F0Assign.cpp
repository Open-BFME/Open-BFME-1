// cl: /O2 /Ob0 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>

struct Gen_t_002e13b0_p12cd;

// ILT 0x00033640 forwards to the matched vector assignment at 0x002E13B0.
extern template class _STL::vector<Gen_t_002e13b0_p12cd>;

class Rva002E9E70Mid
{
private:
	void *m_item;
};

class Rva002E17F0
{
	virtual void handle();
	char m_04;
	Rva002E9E70Mid m_08;

public:
	void operator=(const Rva002E17F0 &other);
};

void Rva002E17F0::operator=(const Rva002E17F0 &other)
{
	*reinterpret_cast<_STL::vector<Gen_t_002e13b0_p12cd> *>(&m_08) =
		*reinterpret_cast<const _STL::vector<Gen_t_002e13b0_p12cd> *>(&other.m_08);
	m_04 = other.m_04;
}
