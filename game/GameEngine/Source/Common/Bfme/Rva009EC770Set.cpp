// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail RVA 0x009EC770, 434 bytes. The name keeps the address because the
// body proves a set wrapper, but it does not prove a semantic class name.
// Q1Receiver::refresh calls this at +0x094C with a temporary wrapper in ECX
// and the wrapper at receiver +0x190 as its stack argument.
// The body collects keys absent from the argument, erases them from the
// temporary set, sets its +0x10 flag, and returns the temporary wrapper.
// The erase target at 0x009EC370 names the key as Gen_t_00134aa0_m4pod.
// The temporary vector holds four-byte keys and uses the pinned overflow
// helper at 0x0001CBFC.

#include <set>
#include <vector>

struct Gen_t_00134aa0_m4pod
{
	unsigned int a;
};

inline bool operator<(const Gen_t_00134aa0_m4pod &left,
	const Gen_t_00134aa0_m4pod &right)
{
	return left.a < right.a;
}

typedef _STL::set<Gen_t_00134aa0_m4pod> Rva009EC770Tree;

class Rva009EC770Set
{
public:
	Rva009EC770Set &rva009EC770(const Rva009EC770Set &other);

private:
	Rva009EC770Tree m_set;
	int dword_C;
	bool m_changed;
};

// ?rva009EC770@Rva009EC770Set@@QAEAAV1@ABV1@@Z
Rva009EC770Set &Rva009EC770Set::rva009EC770(const Rva009EC770Set &other)
{
	_STL::vector<unsigned int> found;
	for (Rva009EC770Tree::iterator it = m_set.begin(); it != m_set.end(); ++it)
	{
		if (other.m_set.find(*it) == other.m_set.end())
			found.push_back(it->a);
	}
	if (!found.empty())
	{
		for (_STL::vector<unsigned int>::iterator v = found.begin();
			v != found.end(); ++v)
		{
			m_set.erase(reinterpret_cast<const Gen_t_00134aa0_m4pod &>(*v));
		}
		m_changed = true;
	}
	return *this;
}
