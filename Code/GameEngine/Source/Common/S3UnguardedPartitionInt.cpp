// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: the four-byte-scalar STL unguarded partition at retail
// 0x005124A0.  Its three arguments and return value are fixed by the body;
// the surrounding sort specialization has not yielded the original scalar
// typedef, so the function name remains address-derived.

int *BfmeUnguardedPartition005124A0(int *first, int *last, int pivot)
{
	for (;;)
	{
		while (*first < pivot)
			++first;

		--last;
		while (pivot < *last)
			--last;

		if (!(first < last))
			return first;

		int value = *first;
		*first = *last;
		*last = value;
		++first;
	}
}
