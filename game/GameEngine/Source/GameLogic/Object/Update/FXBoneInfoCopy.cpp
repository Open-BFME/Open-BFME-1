// cl: /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
struct FXBoneInfo
{
	const void *particleSystemTemplate;
	AsciiString boneName;
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

template FXBoneInfo *__copy<FXBoneInfo *, FXBoneInfo *, int>(FXBoneInfo *, FXBoneInfo *,
	FXBoneInfo *, const random_access_iterator_tag &, int *);
}
