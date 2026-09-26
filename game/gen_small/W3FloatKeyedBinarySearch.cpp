// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the lower_bound / upper_bound pair over a 0x10-byte element with
// a float first member, out of d_0001466e.asm.
//
// Both are __cdecl free functions taking (first, last, value) and both open by
// turning the range into a COUNT: `sub / sar 4` is an exact pointer difference,
// which fixes the element at 0x10 bytes -- an exact `sar` is only valid for a
// power-of-two size. The step is `sar edx,1`, a bare arithmetic shift with no
// rounding fixup, so the source wrote `len >> 1` and not `len / 2`.
//
// The two differ in ONE thing: which side of the comparison the sought value is
// on. 0x00069DF0 does `fld [value] / fcomp [middle]` and 0x00069E60 does
// `fld [middle] / fcomp [value]`. That is the textbook upper_bound / lower_bound
// split -- `value < *middle` versus `*middle < value` -- and it is also why the
// two blocks after the branch are swapped between them.
//
// The comparison is on the FIRST four bytes of the element only, so the ordering
// is by that float; the remaining twelve bytes are never read.
//
// Identity is address-derived.

struct Rva00069DF0Element
{
	float m_key;										///< element+0x00
	int m_unreconstructed_04[3];						///< element+0x04
};

inline bool operator<(const Rva00069DF0Element &left, const Rva00069DF0Element &right)
{
	return left.m_key < right.m_key;
}

// ?Rva00069DF0UpperBound@@YAPAURva00069DF0Element@@PAU1@0ABU1@@Z
Rva00069DF0Element *Rva00069DF0UpperBound(Rva00069DF0Element *first,
	Rva00069DF0Element *last, const Rva00069DF0Element &value)
{
	int length = last - first;

	while (length > 0)
	{
		int half = length >> 1;
		Rva00069DF0Element *middle = first + half;

		if (value < *middle)
		{
			length = half;
		}
		else
		{
			first = middle + 1;
			length -= half + 1;
		}
	}

	return first;
}

// ?Rva00069E60LowerBound@@YAPAURva00069DF0Element@@PAU1@0ABU1@@Z
Rva00069DF0Element *Rva00069E60LowerBound(Rva00069DF0Element *first,
	Rva00069DF0Element *last, const Rva00069DF0Element &value)
{
	int length = last - first;

	while (length > 0)
	{
		int half = length >> 1;
		Rva00069DF0Element *middle = first + half;

		if (*middle < value)
		{
			first = middle + 1;
			length -= half + 1;
		}
		else
		{
			length = half;
		}
	}

	return first;
}
