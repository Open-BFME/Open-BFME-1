// cl: /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

struct PrereqUnitRecCopyABI
{
	void *unit;
	int flags;
	AsciiString name;
};

struct PrereqRandomAccessIteratorTagABI {};

extern "C" PrereqUnitRecCopyABI *__cdecl bfme_PrereqUnitRecCopy_E4AE0(
	PrereqUnitRecCopyABI *first,
	PrereqUnitRecCopyABI *last,
	PrereqUnitRecCopyABI *result,
	const PrereqRandomAccessIteratorTagABI &,
	int *)
{
	for (int count = last - first; count > 0; --count) {
		result->unit = first->unit;
		result->flags = first->flags;
		result->name.set(first->name);
		++first;
		++result;
	}
	return result;
}
