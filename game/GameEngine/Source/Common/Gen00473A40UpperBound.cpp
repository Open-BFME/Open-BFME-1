// cl: /O2

// STLport __upper_bound over 16-byte records, comparing the first dword.
// Retail 0x00473A40, 72 bytes.

struct Gen00473A40Elem
{
	int key;
	char pad[12];
};

struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const
	{
		return value < elem.key;
	}
};

Gen00473A40Elem *Gen00473A40(Gen00473A40Elem *first, Gen00473A40Elem *last,
	const int &value, Gen00473A40Less, int *)
{
	int length = last - first;
	while (length > 0)
	{
		int half = length >> 1;
		Gen00473A40Elem *middle = first + half;
		if (value < middle->key)
			length = half;
		else
		{
			first = middle + 1;
			length -= half + 1;
		}
	}
	return first;
}
