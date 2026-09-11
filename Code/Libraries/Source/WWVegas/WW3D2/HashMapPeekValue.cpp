// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x008FF850: hash map find wrapper returning mapped pointer or null.

#include <map>

typedef _STL::map<int, void *, _STL::less<unsigned int> > HashMap008FF850;
typedef HashMap008FF850::iterator HashIter008FF850;

extern HashMap008FF850 g_map008FF850;

void *PeekHashMapValue008FF850(int key)
{
	HashIter008FF850 it = g_map008FF850.find(key);
	if (it == g_map008FF850.end())
		return 0;
	return (*it).second;
}
