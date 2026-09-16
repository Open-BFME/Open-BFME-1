// cl: /O2 /Ob2 /G6
//
// Address-derived bounds-checked erase at retail RVA 0x00364210.  The sole
// call reaches the independently matched STLport vector<Gen003627D0>::erase
// body at 0x003636F0 through ILT 0x0001620C.  That callee's 0xB4-byte element
// stride and this body's +0x30 vector offset establish the operation without
// inventing a semantic owner or method name.

struct Gen003627D0
{
	virtual ~Gen003627D0();
	unsigned char m_raw[0xB0];
	Gen003627D0();
	Gen003627D0(const Gen003627D0 &);
	Gen003627D0 &operator=(const Gen003627D0 &);
};

namespace _STL
{
	template <class T> class allocator {};

	template <class T, class Allocator = allocator<T> >
	class vector : private Allocator
	{
	public:
		typedef T *iterator;

		unsigned int size() const { return (unsigned int)(m_finish - m_start); }
		iterator begin() { return m_start; }
		iterator erase(iterator position);

	private:
		iterator m_start;
		iterator m_finish;
	};
}

class Rva00364210Owner
{
public:
	void rva00364210(int index);

private:
	unsigned char m_head[0x30];
	_STL::vector<Gen003627D0> m_items;
};

void Rva00364210Owner::rva00364210(int index)
{
	if (index < 0)
		return;
	if ((unsigned int)index >= m_items.size())
		return;
	m_items.erase(m_items.begin() + index);
}
