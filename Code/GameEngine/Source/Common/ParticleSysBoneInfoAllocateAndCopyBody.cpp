// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport ParticleSysBoneInfo vector allocation and copy helper, retail
// 0x000A7E00, 94 bytes. The name sat on the 5-byte incremental-link thunk at
// 0x000286AA and the body it jumps to carried only a machine byte-dump row.
//
// The element is 8 bytes, which is what the byte count the allocator sees
// is scaled by and what the copy loop strides. The per-element call goes
// through the ILT at 0x00044675; the helper is named apart from _STL::_Construct
// so this call site pins to that ILT without disturbing the _Construct name
// the ledger already pins elsewhere.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ParticleSysBoneInfo
{
private:
	unsigned char m_data[8];
};

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

void __cdecl BfmeElementConstruct(void *destination, const ParticleSysBoneInfo &value);

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

template ParticleSysBoneInfo *vector<ParticleSysBoneInfo, allocator<ParticleSysBoneInfo> >::_M_allocate_and_copy<const ParticleSysBoneInfo *>(
	unsigned int, const ParticleSysBoneInfo *, const ParticleSysBoneInfo *);
}
