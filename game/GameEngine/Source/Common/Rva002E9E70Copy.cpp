// cl: /O2 /Ob0
// stlport

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include <vector>

struct Gen_t_002e13b0_p12cd;
extern template class _STL::vector<Gen_t_002e13b0_p12cd>;

class Rva0036CA00Str
{
private:
	void *m_item;
};

class Rva002E9E70Mid
{
private:
	void *m_item[3];
};

class Rva002E9E70
{
	Rva0036CA00Str m_00;
	char m_04;
	Rva002E9E70Mid m_08;

public:
	Rva002E9E70(const Rva002E9E70 &other);
};

Rva002E9E70::Rva002E9E70(const Rva002E9E70 &other)
{
	reinterpret_cast<StringBase<char> *>(&m_00)->set(
		*reinterpret_cast<const StringBase<char> *>(&other.m_00));
	m_04 = other.m_04;
	*reinterpret_cast<_STL::vector<Gen_t_002e13b0_p12cd> *>(&m_08) =
		*reinterpret_cast<const _STL::vector<Gen_t_002e13b0_p12cd> *>(&other.m_08);
}
