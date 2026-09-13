// cl: /O2 /EHsc /Ireference/shims/stringinline
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

	void clear()
	{
		erase(m_start, m_finish);
	}

	T *erase(T *first, T *last);

private:
	T *volatile m_start;
	T *volatile m_finish;
	T *m_end;
};
}

#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003A99D0@@V?$allocator@UGen003A99D0@@@_STL@@@_STL@@QAEPAUGen003A99D0@@PAU3@0@Z=?j_00020928@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003A9B60@@V?$allocator@UGen003A9B60@@@_STL@@@_STL@@QAEPAUGen003A9B60@@PAU3@0@Z=?j_000450ca@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003A9C30@@V?$allocator@UGen003A9C30@@@_STL@@@_STL@@QAEPAUGen003A9C30@@PAU3@0@Z=?j_00048c48@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003A9CF0@@V?$allocator@UGen003A9CF0@@@_STL@@@_STL@@QAEPAUGen003A9CF0@@PAU3@0@Z=?j_00037821@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003A9DC0@@V?$allocator@UGen003A9DC0@@@_STL@@@_STL@@QAEPAUGen003A9DC0@@PAU3@0@Z=?j_00026611@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003AA300@@V?$allocator@UGen003AA300@@@_STL@@@_STL@@QAEPAUGen003AA300@@PAU3@0@Z=?j_0002dfc4@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003AA1A0@@V?$allocator@UGen003AA1A0@@@_STL@@@_STL@@QAEPAUGen003AA1A0@@PAU3@0@Z=?j_0003578d@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003AA010@@V?$allocator@UGen003AA010@@@_STL@@@_STL@@QAEPAUGen003AA010@@PAU3@0@Z=?j_0003d3ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen003AA0D0@@V?$allocator@UGen003AA0D0@@@_STL@@@_STL@@QAEPAUGen003AA0D0@@PAU3@0@Z=?j_0003cae2@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@?$vector@UGen_t_003ab360_p12cd@@V?$allocator@UGen_t_003ab360_p12cd@@@_STL@@@_STL@@QAEPAUGen_t_003ab360_p12cd@@PAU3@0@Z=?j_00011e28@@YAXXZ")

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
