// ?rva002350c0@Rva002350C0@@QAE?AVRectClass@@H@Z
// partial score=0.91 date=2026-09-25
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Best current body for served RVA 0x002350C0: 99 bytes with 8 non-relocation
// differences beginning at +0x2F. The call at 0x00233F30 has ECX plus two
// stack pointers and returns its output pointer in EAX; the exact source-level
// return type is not established, and the remaining register/store order is
// not byte-exact. The vector-at-+0x12C view is still address-derived.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
struct Coord2D { float x; float y; };
struct BfmeRva44E60Record
{
	int m_value;
	int m_first;
	int m_second;
	int m_unused;
	BfmeRva44E60Record();
	BfmeRva44E60Record(const BfmeRva44E60Record &other);
};
class RectClass { public: RectClass(const RectClass &other); };
class Rva002350C0
{
public:
	char gap00[4]; void *settings04; void *object08; char gap0C[0x120];
	_STL::vector<BfmeRva44E60Record> records12C;
	Coord2D *rva00233f30(Coord2D *out, const Coord2D *direction);
	RectClass rva002350c0(int index);
};
RectClass Rva002350C0::rva002350c0(int index)
{
	BfmeRva44E60Record local;
	Coord2D offset;
	Coord2D *computed = rva00233f30(&offset, (const Coord2D *)&records12C[index].m_first);
	unsigned int x = *(unsigned int *)&computed->x;
	float distance = *(volatile float *)&records12C[index].m_unused;
	unsigned int y = *(unsigned int *)&computed->y;
	*(float *)((char *)&local + 12) = distance;
	*(unsigned int *)((char *)&local + 4) = x;
	*(unsigned int *)((char *)&local + 8) = y;
	return *(RectClass *)&local;
}
