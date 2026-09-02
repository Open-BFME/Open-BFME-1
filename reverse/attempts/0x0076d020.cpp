// ?d_0076d020@@YAXXZ
// partial score=0.45 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector-like copy constructor over 20-byte non-trivial elements,
// retail 0x0076D020, 146 bytes.
#include <memory>

struct Rva0076D020Allocator {};

struct Rva0076D020Element
{
	int value[5];
	Rva0076D020Element(const Rva0076D020Element &);
};

class Rva0076D020VectorBase
{
public:
	Rva0076D020VectorBase(unsigned int count, const Rva0076D020Allocator &allocator);
	~Rva0076D020VectorBase();
	Rva0076D020Allocator get_allocator() const;

protected:
	Rva0076D020Element *m_begin;
	Rva0076D020Element *m_end;
	Rva0076D020Element *m_capacity;
};

class Rva0076D020Vector : private Rva0076D020VectorBase
{
public:
	Rva0076D020Vector(const Rva0076D020Vector &other);
};

Rva0076D020Vector::Rva0076D020Vector(const Rva0076D020Vector &other) :
	Rva0076D020VectorBase(
		(unsigned int)(other.m_end - other.m_begin), other.get_allocator())
{
	Rva0076D020Element *source = other.m_begin;
	Rva0076D020Element *destination = m_begin;
	for (; source != other.m_end; ++source, ++destination)
		_STL::_Construct(destination, *source);
	m_end = destination;
}
