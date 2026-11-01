// cl: /DNDEBUG /MD /EHsc
// 0x00C70980 (10 bytes): an unreferenced teardown in the run of static
// atexit-style forwarders near the end of .text,
//
//     mov ecx,0x012F820C / jmp ILT 0x00043CCF
//
// that destroys the Rva006F2910 custom-allocator vector held in the global at
// 0x012F820C through its out-of-line destructor (0x006F2910, defined in
// Rva006F2910VectorDtor.cpp). Only the destructor declaration is given here,
// so the call stays a tail jump as in retail. IDENTITY IS NOT RECOVERED: the
// function and the global keep address-derived names.

struct Rva006F2910Element;
template <class T> class Rva006F2910Allocator;

namespace _STL
{
template <class _Tp, class _Alloc> class vector
{
public:
	~vector();
};
}

extern _STL::vector<Rva006F2910Element, Rva006F2910Allocator<Rva006F2910Element> > g_Va012F820C;

void Rva00C70980Teardown()
{
	g_Va012F820C.~vector();
}
