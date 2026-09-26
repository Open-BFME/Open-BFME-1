// cl: /EHsc /MD /O2 /GR- /EHsc- /D_STLP_USE_STATIC_LIB
// stlport

#include <cstring>

extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);

#define memmove (*bfme_memmove_ptr)
#include <vector>
#undef memmove

struct Gen_t_000bbe70_m4pod { int a[1]; };
bool operator==(const Gen_t_000bbe70_m4pod &, const Gen_t_000bbe70_m4pod &);
bool operator<(const Gen_t_000bbe70_m4pod &, const Gen_t_000bbe70_m4pod &);

namespace _STL
{
template <> struct __type_traits<Gen_t_000bbe70_m4pod> : __type_traits_aux<1> {};
}

class BfmeUniqueIntegerStoreC8C0
{
public:
	void add(int value);

private:
	char m_bfmePrefix[8];
	_STL::vector<Gen_t_000bbe70_m4pod> m_values;
};

void BfmeUniqueIntegerStoreC8C0::add(int value)
{
	Gen_t_000bbe70_m4pod *at = m_values.begin();
	Gen_t_000bbe70_m4pod *end = m_values.end();
	while (at != end)
	{
		if (at->a[0] == value)
			return;
		++at;
	}
	Gen_t_000bbe70_m4pod *item = (Gen_t_000bbe70_m4pod *)&value;
	m_values.push_back(*item);
}
