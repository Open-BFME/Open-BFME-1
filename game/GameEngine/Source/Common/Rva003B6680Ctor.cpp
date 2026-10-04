// cl: /O2 /EHsc /Iinputs/reference/shims/stringinline
// ??0Rva003B6680@@QAE@ABVAsciiString@@@Z
// Copy-constructs the string at +4 from the argument, default-inits the
// rest of the 0x010EC850 object, then clear()s every vector. Out-of-line
// erase survives only on non-trivial element types; trivial ones fold away
// after the zeros. Layout matches Rva003B16B0Dtor.cpp / Rva003B6680Assign.cpp.
// volatile on the first two vector pointers keeps those stores ahead of the
// EH state-0 write, matching retail.

#include "StringInline.h"

struct Gen003A99D0;
struct Gen003A9A90;
struct Gen003A9B60;
struct Gen003A9C30;
struct Gen003A9CF0;
struct Gen003A9DC0;
struct Gen003A9E90;
struct Gen003AA010;
struct Gen_t_003ab1b0_p12cd;
struct Gen003AA0D0;
struct Gen003AA1A0;
struct Gen003AA300;
struct Gen003AA3C0;
struct Gen_t_003ab0f0_p16cd;
struct Gen_t_003ab360_p12cd;

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	vector()
		: m_start(0), m_finish(0)
	{
		m_end = 0;
	}

	~vector();

	// Out-of-line erase of a non-trivial element type lives in another TU,
	// and retail reaches it through the incremental-link thunk its call site
	// encodes -- one thunk per element type. clear() is specialized per element
	// type below so that each body names its own thunk symbol directly instead
	// of relying on a linker alias; the out-of-line copy of every clear that
	// MSVC still emits calls that same thunk.
	typedef T * (vector::*erase_fn)(T *first, T *last);

	void clear();

	T *erase(T *first, T *last);

private:
	T *volatile m_start;
	T *volatile m_finish;
	T *m_end;
};
}


// Retail's converting ctor reaches every out-of-line vector::erase through the
// incremental-link thunk the call site encodes, one per element type.
extern void j_00020928();
extern void j_000450ca();
extern void j_00048c48();
extern void j_00037821();
extern void j_00026611();
extern void j_0002dfc4();
extern void j_0003578d();
extern void j_0003d3ac();
extern void j_0003cae2();
extern void j_00011e28();

template <class T, class A>
void _STL::vector<T, A>::clear()
{
	erase(m_start, m_finish);
}

// Each of these is the same body: the thunk address read as a pointer-to-member
// is a constant, so the indirect call folds back into a direct call to the thunk.
template <> void _STL::vector<Gen003A99D0>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_00020928 };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen003A9B60>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_000450ca };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen003A9C30>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_00048c48 };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen003A9CF0>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_00037821 };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen003A9DC0>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_00026611 };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen003AA300>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_0002dfc4 };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen003AA1A0>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_0003578d };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen003AA010>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_0003d3ac };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen003AA0D0>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_0003cae2 };
	(this->*route.at)(m_start, m_finish);
}

template <> void _STL::vector<Gen_t_003ab360_p12cd>::clear()
{
	union { void (*thunk)(); erase_fn at; } route = { j_00011e28 };
	(this->*route.at)(m_start, m_finish);
}

class Rva003B6680
{
public:
	virtual ~Rva003B6680();
	Rva003B6680(const AsciiString &name);

private:
	AsciiString m04;
	_STL::vector<Gen003A99D0> m08;
	_STL::vector<Gen003A9A90> m14;
	_STL::vector<Gen003A9B60> m20;
	_STL::vector<Gen003A9C30> m2c;
	_STL::vector<AsciiString> m38;
	_STL::vector<AsciiString> m44;
	AsciiString m50;
	_STL::vector<Gen003A9CF0> m54;
	_STL::vector<Gen003A9DC0> m60;
	_STL::vector<Gen003A9E90> m6c;
	_STL::vector<Gen003AA010> m78;
	_STL::vector<Gen003AA0D0> m84;
	_STL::vector<Gen003AA1A0> m90;
	_STL::vector<Gen003AA300> m9c;
	_STL::vector<Gen003AA3C0> ma8;
	_STL::vector<Gen_t_003ab0f0_p16cd> mb4;
	_STL::vector<Gen_t_003ab1b0_p12cd> mc0;
	_STL::vector<Gen_t_003ab360_p12cd> mcc;
	bool md8;
};

Rva003B6680::Rva003B6680(const AsciiString &name)
	: m04(name), md8(false)
{
	m08.clear();
	m20.clear();
	m2c.clear();
	m38.clear();
	m54.clear();
	m60.clear();
	m9c.clear();
	m90.clear();
	m78.clear();
	m84.clear();
	m44.clear();
	mcc.clear();
}
