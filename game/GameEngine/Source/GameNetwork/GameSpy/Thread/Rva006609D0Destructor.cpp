// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x006609D0 (197 B) of a 0xB4-byte network
// results object: after a clearing member call (0x0065F100) the members
// unwind in reverse -- the owning holder of a mutex lock at +0xB0 (its inline
// destructor is the eighth EH state) -- a
// GameResultsCounter at +0xA8 a red-black tree at +0x74 two deques at +0x44
// and +0x1C and three GameResultsCounters at +0x14 +0xC and +4 -- and the
// base vtable is restored.  Member types are opaque address-derived shells
// sized from the offsets with out-of-line destructors.

class GameResultsCounter
{
public:
	~GameResultsCounter();

private:
	char m_body[ 8 ];
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		~LockClass();

	private:
		char m_body[ 4 ];
	};
};

// Declaration-only retail STLport specializations. Member extents are
// independently fixed by this object's +1C/+44/+74/+80 layout.
struct Gen_t_00660470_p12cd;
struct Gen_t_00660610_p12cd;
struct Gen_t_0064c290_p12cd;
namespace _STL
{
template <class T> class allocator;
template <class T> struct less;
template <class T> struct _Select1st;
template <class A, class B> struct pair;
template <class K, class V, class Extract, class Compare, class Alloc> class _Rb_tree;
template <class T, class Alloc> class deque;

template <> class deque<Gen_t_00660470_p12cd, allocator<Gen_t_00660470_p12cd> >
{
public:
	~deque();
	char m_body[0x28];
};
template <> class deque<Gen_t_00660610_p12cd, allocator<Gen_t_00660610_p12cd> >
{
public:
	~deque();
	char m_body[0x28];
};
template <> class _Rb_tree<int, _STL::pair<const int, Gen_t_0064c290_p12cd>, _STL::_Select1st<_STL::pair<const int, Gen_t_0064c290_p12cd> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Gen_t_0064c290_p12cd> > >
{
public:
	~_Rb_tree();
	char m_body[0x0C];
};
}

class BfmeThingVHX
{
public:
	void bfmeClearVHX();
};

struct Rva006609D0LockHolder
{
	~Rva006609D0LockHolder()
	{
		if( m_lock )
			delete m_lock;
	}

	MutexClass::LockClass *m_lock;
};

class Rva006609D0Base
{
public:
	virtual ~Rva006609D0Base() {}
};

class Rva006609D0 : public Rva006609D0Base
{
public:
	virtual ~Rva006609D0();

private:
	GameResultsCounter m_counter04;
	GameResultsCounter m_counter0C;
	GameResultsCounter m_counter14;
	_STL::deque<Gen_t_00660470_p12cd, _STL::allocator<Gen_t_00660470_p12cd> > m_deque1C;
	_STL::deque<Gen_t_00660610_p12cd, _STL::allocator<Gen_t_00660610_p12cd> > m_deque44;
	char m_unreconstructed6C[ 8 ];
	_STL::_Rb_tree<int, _STL::pair<const int, Gen_t_0064c290_p12cd>, _STL::_Select1st<_STL::pair<const int, Gen_t_0064c290_p12cd> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Gen_t_0064c290_p12cd> > > m_tree74;
	char m_unreconstructed80[ 0xA8 - 0x80 ];
	GameResultsCounter m_counterA8;
	Rva006609D0LockHolder m_lockB0;
};

// ??1Rva006609D0@@UAE@XZ
Rva006609D0::~Rva006609D0()
{
	reinterpret_cast<BfmeThingVHX *>(this)->bfmeClearVHX();
}
