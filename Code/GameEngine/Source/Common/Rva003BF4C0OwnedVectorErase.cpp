// cl: /O2 /Ob1 /EHs-c- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// The retail body searches the pointer range at +0x50/+0x54, deletes the
// matching object through its virtual destructor, moves the tail down, and
// decrements the finish pointer. The class and method stay address-derived
// because the retail body has no named caller or declaration.

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(
	void *destination, const void *source, unsigned int bytes);

#include <algorithm>
#include <stl/_iterator_base.h>

#pragma comment(linker, "/alternatename:??$__find@PAPAVRva003BF4C0Item@@PAV1@@_STL@@YAPAPAVRva003BF4C0Item@@PAPAV1@0ABQAV1@ABUrandom_access_iterator_tag@0@@Z=?j_0000d6d9@@YAXXZ")

class Rva003BF4C0Item
{
public:
	virtual ~Rva003BF4C0Item();
};

class Rva003BF4C0Owner
{
public:
	void remove(Rva003BF4C0Item *item);

private:
	char m_padding00[0x50];
	Rva003BF4C0Item **m_begin;
	Rva003BF4C0Item **m_finish;
};

void Rva003BF4C0Owner::remove(Rva003BF4C0Item *item)
{
	Rva003BF4C0Item *const key = item;
	_STL::random_access_iterator_tag tag;
	Rva003BF4C0Item **found = _STL::__find(
		m_begin, m_finish, key, tag);
	if (found == m_finish)
		return;

	if (*found)
		delete *found;

	Rva003BF4C0Item **next = found + 1;
	if (m_finish != next)
		BfmeMemMove(found, next,
			(unsigned int)((char *)m_finish - (char *)next));

	--m_finish;
}
