// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0010FE90, 204 bytes. The callback at 0x00110790 proves the
// receiver and two-argument thiscall ABI; the owner's semantic name is unknown.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <string.h>

struct Rva0010EBE0Element
{
	int m_body;
	Rva0010EBE0Element(void *body) : m_body((int)body) {}
};

struct Rva0010ECA0Elem
{
	void *m_a;
	void *m_b;
};

// Keep STLport's real push_front visible, but out of line as in retail.
// Its 47 bytes also match 0x0010EBE0. Visibility proves that it copies the
// argument without retaining its address, preserving the caller's arg home.
template <> __declspec(noinline)
void _STL::list<Rva0010EBE0Element, _STL::allocator<Rva0010EBE0Element> >::push_front(
	const Rva0010EBE0Element &value)
{
	insert(begin(), value);
}

class Rva0010ECA0List
{
public:
	void push_back(Rva0010ECA0Elem const &value);
	_STL::list<Rva0010ECA0Elem> m_list;
};

class Rva0010FE90Named
{
public:
	virtual void v00();
	virtual void v04();
	virtual const char *name();
};

class Rva00110790Receiver
{
public:
	void rva0010fe90(void *item, void *value);
private:
	unsigned char m_unmodelled_00[0x48];
	_STL::list<Rva0010EBE0Element> m_items; // +0x48
	Rva0010ECA0List m_pairs;               // +0x4C
};

void Rva00110790Receiver::rva0010fe90(void *item, void *value)
{
	if (item == 0)
		return;

	const char *name = ((Rva0010FE90Named *)item)->name();
	if (name != 0)
	{
		if (strcmp(name, "Object") == 0)
		{
			// Retail passes the address of the original four-byte argument.
			m_items.push_front(reinterpret_cast<const Rva0010EBE0Element &>(item));
			Rva0010ECA0Elem pair;
			pair.m_a = item;
			pair.m_b = value;
			m_pairs.push_back(pair);
			return;
		}
		if (strcmp(name, "Weapon") == 0)
			return;
	}

	m_items.push_back(Rva0010EBE0Element(item));
	Rva0010ECA0Elem pair;
	pair.m_a = item;
	pair.m_b = value;
	m_pairs.m_list.push_back(pair);
}
