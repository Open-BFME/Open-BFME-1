// ?reverseRangeLessEqual@@YA_NPBD000@Z
// partial score=0.88 date=2026-08-31
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef char Byte;

bool __cdecl reverseRangeLessEqual(
	const Byte *first,
	const Byte *firstEnd,
	const Byte *second,
	const Byte *secondEnd)
{
	if (first == firstEnd) {
		return true;
	}

	if (second == secondEnd) {
		return false;
	}

	--firstEnd;
	--secondEnd;
	while (first != firstEnd && *firstEnd == *second) {
		--firstEnd;
		if (second != secondEnd) {
			++second;
		}
	}

	return *firstEnd <= *second;
}
