// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport vector<Coord3D>::resize(size_type), retail 0x000B7D10.
// BFME's two-argument resize overload takes its 12-byte fill value by value.
// The one-argument overload therefore materializes a default Coord3D directly
// in the outgoing argument slot before forwarding to that overload.

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &) {}
	~Coord3D() {}
	float x;
	float y;
	float z;
};

namespace _STL
{
template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
public:
	void resize(unsigned int newSize, Type value);
	void resize(unsigned int newSize)
	{
		resize(newSize, Type());
	}

private:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template void vector<Coord3D, allocator<Coord3D> >::resize(unsigned int);
}
