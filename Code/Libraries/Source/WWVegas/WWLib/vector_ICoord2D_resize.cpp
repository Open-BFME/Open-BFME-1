// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::vector<ICoord2D>::resize(size_type), retail 0x00453DF0,
// 90 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// The one-argument resize forwards to the two-argument one with a default
// element. That element is an uninitialised local, not Type(): the frame
// reserves eight bytes and the first thing the body does is read them back out
// and copy them into the argument slot. Written as Type() this compiler zeroes
// the pair with a single xor and two stores, which is five bytes short of
// retail and the wrong instructions.
//
// The two-argument form takes the element by value, which is what that copy
// into the argument slot is.
//
// Both arms re-read the finish pointer and recompute the size rather than
// reusing the first computation, which is the shape of erase and _M_fill_insert
// being called on freshly evaluated end() and size(). The insert arm goes
// straight to _M_fill_insert: the ILT at 0x000160C2 lands on 0x00452450, which
// the ledger already names that.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

namespace _STL
{

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
public:
	typedef unsigned int size_type;
	typedef Type *iterator;

	void resize(size_type newSize);

	iterator erase(iterator first, iterator last);
	void _M_fill_insert(iterator position, size_type count, const Type &value);

private:
	iterator begin(void) { return m_start; }
	iterator end(void) { return m_finish; }
	size_type size(void) const { return (size_type)(m_finish - m_start); }

	void resize(size_type newSize, Type value);

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::resize(size_type newSize, Type value)
{
	if (newSize < size())
		erase(begin() + newSize, end());
	else
		_M_fill_insert(end(), newSize - size(), value);
}

template <class Type, class Allocator>
void vector<Type, Allocator>::resize(size_type newSize)
{
	Type value;
	resize(newSize, value);
}

template void vector<ICoord2D, allocator<ICoord2D> >::resize(size_type);

}
