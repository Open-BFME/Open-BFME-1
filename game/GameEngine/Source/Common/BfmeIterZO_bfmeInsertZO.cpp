// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00452230 is the STLport list insertion body for BfmeIterZO.
// The iterator owns a pointer to its list, and the list stores an eight-byte
// BfmeValZO payload in a sixteen-byte node.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct BfmeValZO
{
	void *m_bfmeAZO;
	void *m_bfmeBZO;
};

class BfmeIterZO
{
public:
	void bfmeInsertZO(const BfmeValZO *v);

private:
	_STL::list<BfmeValZO> *m_bfmeListZO;
};

void BfmeIterZO::bfmeInsertZO(const BfmeValZO *v)
{
	m_bfmeListZO->push_back(*v);
}
