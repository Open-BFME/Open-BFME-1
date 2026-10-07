// Retail 0x00146270 calls ILT 0x3931 -> 0x00145070, the matched
// _STL::map<NameKeyType, float>::operator[] (callees.py), on the map at +0x340.
enum NameKeyType { NAMEKEY_INVALID = 0 };

namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class A, class B> struct pair;

template <class K, class V, class C, class A>
class map
{
public:
	V &operator[](const K &key);
};
}

typedef _STL::map<NameKeyType, float, _STL::less<NameKeyType>,
	_STL::allocator<_STL::pair<const NameKeyType, float> > > BfmeMapDST;

class BfmeSubDST
{
public:
	__forceinline void **bfmeOneDST(void **what)
	{
		return (void **)&((BfmeMapDST *)this)->operator[](*(NameKeyType *)what);
	}
};

class BfmeSubDSU
{
public:
	void **bfmeTwoDSU(void **what);
};

struct BfmeThingDST
{
	void bfmeGoDST(void *what, void *v);
	unsigned char m_bfmeHead[0x340];
	BfmeSubDST m_bfmeSub;
};

void BfmeThingDST::bfmeGoDST(void *what, void *v)
{
	*m_bfmeSub.bfmeOneDST(&what) = v;
}

struct BfmeThingDSU
{
	void bfmeGoDSU(void *what, void *v);
	unsigned char m_bfmeHead[0x120];
	BfmeSubDSU m_bfmeSub;
};

void BfmeThingDSU::bfmeGoDSU(void *what, void *v)
{
	*m_bfmeSub.bfmeTwoDSU(&what) = v;
}
