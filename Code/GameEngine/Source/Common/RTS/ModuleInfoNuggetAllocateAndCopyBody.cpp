// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport ModuleInfo::Nugget vector allocation and copy helper, retail
// 0x0076B3B0, 97 bytes. The name sat on the 5-byte incremental-link thunk at
// 0x000313AE and the body it jumps to carried only a machine byte-dump row.
//
// The element is 20 bytes, which is what the byte count the allocator sees
// is scaled by and what the copy loop strides. The per-element call goes
// through the ILT at 0x00016626; the helper is named apart from _STL::_Construct
// so this call site pins to that ILT without disturbing the _Construct name
// the ledger already pins elsewhere.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ModuleInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
	struct Nugget
	{
	private:
		unsigned char m_data[20];
	};
};

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

void __cdecl BfmeElementConstruct(void *destination, const ModuleInfo::Nugget &value);

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

template ModuleInfo::Nugget *vector<ModuleInfo::Nugget, allocator<ModuleInfo::Nugget> >::_M_allocate_and_copy<const ModuleInfo::Nugget *>(
	unsigned int, const ModuleInfo::Nugget *, const ModuleInfo::Nugget *);
}
