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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
private:
	unsigned char m_data[16];
};

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

void __cdecl BfmeElementConstruct(void *destination, const W3DAnimationInfo &value);

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
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
