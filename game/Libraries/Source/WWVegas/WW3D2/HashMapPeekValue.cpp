// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x008FF850: hash map find wrapper returning mapped pointer or null.

#include <map>

typedef _STL::map<int, void *, _STL::less<unsigned int> > HashMap008FF850;
typedef HashMap008FF850::iterator HashIter008FF850;

// The map storage at VA 0x0133F468 is owned by data row g_bfmeList1016; view it
// as this map through that pinned spelling.
class BfmeList1016;
extern BfmeList1016 g_bfmeList1016;
#define g_map008FF850 (*(HashMap008FF850 *)&g_bfmeList1016)

void *PeekHashMapValue008FF850(int key)
{
	HashIter008FF850 it = g_map008FF850.find(key);
	if (it == g_map008FF850.end())
		return 0;
	return (*it).second;
}

// This wrapper exposes the tree's iterator returned by the native map lookup.
class Rva008FF7C0Find
{
	HashMap008FF850 m_map;

public:
	HashIter008FF850 find(const int &key);
};

HashIter008FF850 Rva008FF7C0Find::find(const int &key)
{
	return m_map.find(key);
}
