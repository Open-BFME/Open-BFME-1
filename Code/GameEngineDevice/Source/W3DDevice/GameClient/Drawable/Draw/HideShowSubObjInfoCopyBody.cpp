// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: the out-of-line body of _STL::__copy over
// ModelConditionInfo::HideShowSubObjInfo, retail 0x003B3250, 61 bytes. The name
// sat on the 5-byte incremental-link thunk at 0x0003DB1D and the body it jumps
// to carried only a machine byte-dump row.
//
// The element is eight bytes and the loop reads its count as a signed
// shift-by-three, so the empty range returns the result argument straight from
// the stack rather than falling through the loop.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct HideShowSubObjInfo
	{
		// Retail's per-element assignment touches only the name: the leading
		// dword is left where it is, so the assignment is written out rather
		// than left to the compiler.
		HideShowSubObjInfo &operator=(const HideShowSubObjInfo &that)
		{
			subObjName = that.subObjName;
			return *this;
		}

		int hide;
		AsciiString subObjName;
	};
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template ModelConditionInfo::HideShowSubObjInfo *__copy<const ModelConditionInfo::HideShowSubObjInfo *, ModelConditionInfo::HideShowSubObjInfo *, int>(
	const ModelConditionInfo::HideShowSubObjInfo *, const ModelConditionInfo::HideShowSubObjInfo *,
	ModelConditionInfo::HideShowSubObjInfo *, const random_access_iterator_tag &, int *);
}
