// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail RVA 0x009EC5B0, 434 bytes. Identity is address-derived: the only
// caller is the Q1Receiver0134FAAC refresh body at 0x009EFF50 (call at
// +0x09B5), which passes a receiver-local copy of the 20-byte set wrapper at
// receiver +0x190 as ECX and the wrapper at receiver +0x1A4 as the argument.
// The body removes from this set every key the other set also holds, marks
// the +0x10 flag when anything was collected, and returns *this.
//
// The set instantiation reuses the ledger's ABI name for the erase(first,
// last) body at 0x009EC370; its key is one 4-byte word compared unsigned.
// The collected keys live in vector<unsigned int>, whose growth path is the
// ILT at 0x0001CBFC; erase reads each key straight out of that storage.

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

typedef _STL::set<Gen_t_00134aa0_m4pod> Rva009EC5B0Tree;

class Rva009EC5B0Set
{
public:
	Rva009EC5B0Set &subtract(const Rva009EC5B0Set &other);

private:
	Rva009EC5B0Tree m_set;
	int dword_C;
	bool m_changed;
};

// ?subtract@Rva009EC5B0Set@@QAEAAV1@ABV1@@Z
Rva009EC5B0Set &Rva009EC5B0Set::subtract(const Rva009EC5B0Set &other)
{
	_STL::vector<unsigned int> found;
	for (Rva009EC5B0Tree::iterator it = m_set.begin(); it != m_set.end(); ++it)
	{
		if (other.m_set.find(*it) != other.m_set.end())
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
