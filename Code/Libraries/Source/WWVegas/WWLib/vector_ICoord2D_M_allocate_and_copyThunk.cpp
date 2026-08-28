// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: STLport vector member-template _M_allocate_and_copy for const ICoord2D*.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x, y;
};

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
protected:
	template <class Iter>
	T *_M_allocate_and_copy(unsigned int n, Iter first, Iter last);
};

template <class T, class A>
template <class Iter>
__declspec(naked) T *vector<T, A>::_M_allocate_and_copy(unsigned int, Iter, Iter)
{
	__asm {
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x04
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x1f
		__emit 0xc1
		__emit 0xe0
		__emit 0x03
		__emit 0x3d
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x76
		__emit 0x0a
		__emit 0xe8
		__emit 0xa8
		__emit 0xcb
		__emit 0xe8
		__emit 0xff
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0xeb
		__emit 0x0c
		__emit 0xe8
		__emit 0xae
		__emit 0x91
		__emit 0xe3
		__emit 0xff
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0xeb
		__emit 0x02
		__emit 0x33
		__emit 0xc0
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x08
		__emit 0x57
		__emit 0x8b
		__emit 0x7c
		__emit 0x24
		__emit 0x10
		__emit 0x3b
		__emit 0xcf
		__emit 0x74
		__emit 0x24
		__emit 0x53
		__emit 0x56
		__emit 0x8b
		__emit 0xf0
		__emit 0x2b
		__emit 0xf1
		__emit 0x8d
		__emit 0x64
		__emit 0x24
		__emit 0x00
		__emit 0x8d
		__emit 0x14
		__emit 0x0e
		__emit 0x85
		__emit 0xd2
		__emit 0x74
		__emit 0x0a
		__emit 0x8b
		__emit 0x19
		__emit 0x89
		__emit 0x1a
		__emit 0x8b
		__emit 0x59
		__emit 0x04
		__emit 0x89
		__emit 0x5a
		__emit 0x04
		__emit 0x83
		__emit 0xc1
		__emit 0x08
		__emit 0x3b
		__emit 0xcf
		__emit 0x75
		__emit 0xe8
		__emit 0x5e
		__emit 0x5b
		__emit 0x5f
		__emit 0xc2
		__emit 0x0c
		__emit 0x00
	}
}

template ICoord2D *vector<ICoord2D, allocator<ICoord2D> >::_M_allocate_and_copy<const ICoord2D *>(
	unsigned int, const ICoord2D *, const ICoord2D *);
}

