// ?Rva0003DB1DCopyThunk@@YAPAUHideShowSubObjInfo@ModelConditionInfo@@PBU12@0PAU12@ABUrandom_access_iterator_tag@_STL@@PAH@Z
// Retail 0x0003DB1D jumps to the matched STLport copy body at 0x003B3250.

class ModelConditionInfo
{
public:
	struct HideShowSubObjInfo
	{
	};
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &tag,
	Distance *distance);

extern template ModelConditionInfo::HideShowSubObjInfo *__copy<
	const ModelConditionInfo::HideShowSubObjInfo *,
	ModelConditionInfo::HideShowSubObjInfo *, int>(
	const ModelConditionInfo::HideShowSubObjInfo *,
	const ModelConditionInfo::HideShowSubObjInfo *,
	ModelConditionInfo::HideShowSubObjInfo *,
	const random_access_iterator_tag &, int *);
}

ModelConditionInfo::HideShowSubObjInfo *Rva0003DB1DCopyThunk(
	const ModelConditionInfo::HideShowSubObjInfo *first,
	const ModelConditionInfo::HideShowSubObjInfo *last,
	ModelConditionInfo::HideShowSubObjInfo *result,
	const _STL::random_access_iterator_tag &tag, int *distance )
{
	return _STL::__copy( first, last, result, tag, distance );
}
