// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport HideShowSubObjInfo vector allocation and copy helper,
// retail 0x003B4C80, 94 bytes. The name sat on the 5-byte incremental-link
// thunk at 0x00030D69 and the body it jumps to carried only a machine
// byte-dump row.
//
// The element is the same eight bytes the _M_insert_overflow sibling models
// (shl eax, 3 for the byte count, and the loop strides by 8).
//
// The per-element call goes through the ILT at 0x00033FF0, which jumps to the
// 78-byte _Construct at 0x003A9110 -- not the 23-byte _Construct the ledger
// pins under the HideShowSubObjInfo name, which the ILT at 0x0004A818 reaches
// at 0x0069C300. Those are two different bodies, so the helper is named apart
// rather than putting one symbol on both.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct HideShowSubObjInfo
	{
	private:
		unsigned char m_data[8];
	};
};

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

void __cdecl BfmeHideShowSubObjInfoConstruct(void *destination, const ModelConditionInfo::HideShowSubObjInfo &value);

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
			BfmeHideShowSubObjInfoConstruct((Type *)((char *)first + offset), *first);
			++first;
		}
		while (first != last);
	}
	return result;
}

template ModelConditionInfo::HideShowSubObjInfo *vector<
	ModelConditionInfo::HideShowSubObjInfo,
	allocator<ModelConditionInfo::HideShowSubObjInfo>
>::_M_allocate_and_copy<const ModelConditionInfo::HideShowSubObjInfo *>(
	unsigned int, const ModelConditionInfo::HideShowSubObjInfo *, const ModelConditionInfo::HideShowSubObjInfo *);
}
