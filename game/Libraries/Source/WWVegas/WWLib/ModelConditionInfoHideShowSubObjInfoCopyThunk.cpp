// Focused incremental-link thunk for the non-const HideShowSubObjInfo copy
// specialization.  W3DModelDraw's __copy_ptrs and vector::erase both call the
// retail thunk; its target is the already recovered specialization at
// 0x0033A990.

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

class ModelConditionInfoCopyShim
{
public:
	static void *copy(void *first, void *last, void *result,
		const random_access_iterator_tag &tag, int *distance);
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &tag,
	Distance *distance)
{
	return static_cast<OutputIterator>(ModelConditionInfoCopyShim::copy(
		first, last, result, tag, distance));
}

template ModelConditionInfo::HideShowSubObjInfo *__copy<
	ModelConditionInfo::HideShowSubObjInfo *,
	ModelConditionInfo::HideShowSubObjInfo *, int>(
	ModelConditionInfo::HideShowSubObjInfo *,
	ModelConditionInfo::HideShowSubObjInfo *,
	ModelConditionInfo::HideShowSubObjInfo *,
	const random_access_iterator_tag &, int *);
}
