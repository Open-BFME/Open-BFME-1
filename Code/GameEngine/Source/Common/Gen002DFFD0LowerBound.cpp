// cl: /O2

// STLport __lower_bound over 12-byte records, comparing the first dword.
// Retail 0x002DFFD0, 80 bytes. Magic 0x2AAAAAAB / sar 1 is a 12-byte stride.
// The value is a const int; the comparator and distance dummy are unused
// beyond occupying the STLport 5-argument helper slots.

struct Gen002DFFD0Elem
{
	int key;
	char pad[8];
};

struct Gen002DFFD0Less
{
	bool operator()(const Gen002DFFD0Elem &elem, const int &value) const
	{
		return elem.key < value;
	}
};

Gen002DFFD0Elem *Gen002DFFD0(Gen002DFFD0Elem *first, Gen002DFFD0Elem *last,
	const int &value, Gen002DFFD0Less, int *)
{
	int length = last - first;
	while (length > 0)
	{
		int half = length >> 1;
		Gen002DFFD0Elem *middle = first + half;
		if (middle->key < value)
		{
			first = middle + 1;
			length -= half + 1;
		}
		else
			length = half;
	}
	return first;
}
