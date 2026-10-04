// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport W3DAnimationInfo vector allocation and copy helper, retail
// 0x003B5000, 94 bytes. The name sat on the 5-byte incremental-link thunk at
// 0x0003D3C5 and the body it jumps to carried only a machine byte-dump row.
//
// The element is 16 bytes, which is what the byte count the allocator sees
// is scaled by and what the copy loop strides. The per-element call goes
// through the ILT at 0x0000927D; the helper is named apart from _STL::_Construct
// so this call site pins to that ILT without disturbing the _Construct name
// the ledger already pins elsewhere.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
private:
	unsigned char m_data[16];
};

// Declared before the friend declarations below so they name this function
// and not a fresh _STL-scope declaration.
void j_0003D3C5(void);

namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

void __cdecl BfmeElementConstruct(void *destination, const W3DAnimationInfo &value);

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
	// The thunk below needs this member's address, and taking it from outside
	// the class would force public access, which changes the mangled name to
	// the ?QAE form instead of retail's ?IAE one. The qualified friend form is
	// the one MSVC 7.1 binds to the global declaration.
	friend void ::j_0003D3C5(void);
protected:
	template <class Iterator>
	Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(
	unsigned int count, Iterator first, Iterator last)
{
	Type *result;
	if (count)
	{
		unsigned int bytes = count * sizeof(Type);
		if (bytes > 128)
			result = (Type *)vectorLargeAllocate(bytes);
		else
			result = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		result = 0;
	}

	if (first != last)
	{
		int offset = (char *)result - (char *)first;
		do
		{
			BfmeElementConstruct((Type *)((char *)first + offset), *first);
			++first;
		}
		while (first != last);
	}
	return result;
}

template W3DAnimationInfo *vector<W3DAnimationInfo, allocator<W3DAnimationInfo> >::_M_allocate_and_copy<const W3DAnimationInfo *>(
	unsigned int, const W3DAnimationInfo *, const W3DAnimationInfo *);
}

typedef _STL::vector<W3DAnimationInfo, _STL::allocator<W3DAnimationInfo> > W3DAnimationInfoVector;
typedef W3DAnimationInfo *(W3DAnimationInfoVector::*AllocateAndCopyMemberFn)(
	unsigned int, const W3DAnimationInfo *, const W3DAnimationInfo *);

// The retail thunk at 0x0003D3C5 is a bare tail jump to this TU's own
// _M_allocate_and_copy, so it carries that member's address in a
// function-local union and tail-calls it through the void() view: exactly the
// five bytes the ledger verifies, with no linker alias involved.
union W3DAnimationInfoAllocateAndCopyEntry
{
	void (__cdecl *thunk)();
	AllocateAndCopyMemberFn body;
};

void j_0003D3C5(void)
{
	W3DAnimationInfoAllocateAndCopyEntry entry;
	entry.body = &W3DAnimationInfoVector::_M_allocate_and_copy<const W3DAnimationInfo *>;
	entry.thunk();
}
