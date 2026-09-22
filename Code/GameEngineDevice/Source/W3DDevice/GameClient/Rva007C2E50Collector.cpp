// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// The recursive collector at retail 0x007C2E50, a complete carved extent.
//
// WHAT THE BYTES SHOW.  `this` in ecx saved to the frame, two stack arguments
// and `ret 8`.  The first argument is the STLport vector the body push_backs
// into -- the overflow path calls
// ?_M_insert_overflow@?$vector@PAVObject@@... by name, which is what fixes the
// element type as Object* -- and the second is a polymorphic node.
//
// The node's virtual slots are read straight off the call sites: +0x0C decides
// the branch, +0x14 supplies the value pushed when +0x0C is null, +0x6C gives a
// child count and +0x74 takes an index and returns a child.  The recursion is
// the ILT at 0x0002A2F2, which routes back to this same body with the same
// vector and the child.  Each child is released with the inline
// `if (--m_refCount == 0) slot0()` shape -- the count is at +4, which puts the
// vptr at 0 -- and that release runs only for children the index call actually
// returned.
//
// The loop counts DOWN: the count is fetched once and the index passed to +0x74
// is the pre-decremented value, so the last child is visited first.
//
// IDENTITY IS NOT RECOVERED.  Every class name here is derived from the address.
#include <vector>

class Object;

class Rva007C2E50Node
{
public:
	virtual void releaseSelf();
	virtual void s04();
	virtual void s08();
	virtual void *s0c();
	virtual void s10();
	virtual Object *s14();
	virtual void s18();
	virtual void s1c();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2c();
	virtual void s30();
	virtual void s34();
	virtual void s38();
	virtual void s3c();
	virtual void s40();
	virtual void s44();
	virtual void s48();
	virtual void s4c();
	virtual void s50();
	virtual void s54();
	virtual void s58();
	virtual void s5c();
	virtual void s60();
	virtual void s64();
	virtual void s68();
	virtual int s6c();
	virtual void s70();
	virtual Rva007C2E50Node *s74(int index);

	void releaseRef()
	{
		if (--m_refCount == 0)
			releaseSelf();
	}

	int m_refCount;
};

class Rva007C2E50Collector
{
public:
	void collect(_STL::vector<Object *> *out, Rva007C2E50Node *node);
};

// ?collect@Rva007C2E50Collector@@QAEXPAV?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAVRva007C2E50Node@@@Z
void Rva007C2E50Collector::collect(_STL::vector<Object *> *out, Rva007C2E50Node *node)
{
	if (node->s0c() == 0)
	{
		out->push_back(node->s14());
		return;
	}

	int count = node->s6c();
	while (count > 0)
	{
		--count;
		Rva007C2E50Node *child = node->s74(count);
		if (child != 0)
		{
			collect(out, child);
			child->releaseRef();
		}
	}
}
