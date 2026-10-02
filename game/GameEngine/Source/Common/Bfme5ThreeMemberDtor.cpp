// stlport
// A three-member destructor.
//
// The body is one statement -- clear the first list -- and everything after it
// is the three members going away in reverse declaration order, then the
// base's vftable going back in as it is destroyed inline.
//
// The state word counts the members: three while the body runs, then two, one
// and zero as each is destroyed, and those later stores are byte-wide because
// only the low byte changes. The first and last cleanup calls share a target;
// the middle call uses another retail instance of the list-base destructor.

#include <list>

// The three cleanup calls use the existing retail list-base destructor.
namespace _STL
{
	template <> _List_base<int, allocator<int> >::~_List_base();
}

class BfmeBaseE
{
public:
	virtual ~BfmeBaseE(void) {}
};

class Gen_000F8A40 : public BfmeBaseE
{
public:
	virtual ~Gen_000F8A40(void);

private:
	_STL::list<int> m_bfmeFirst;				// +0x04
	_STL::list<int> m_bfmeSecond;				// +0x08
	_STL::list<int> m_bfmeThird;				// +0x0C
};

// ??1Gen_000F8A40@@UAE@XZ
Gen_000F8A40::~Gen_000F8A40(void)
{
	m_bfmeFirst.clear();
}
