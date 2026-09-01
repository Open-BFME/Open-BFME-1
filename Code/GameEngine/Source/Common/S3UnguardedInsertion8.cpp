// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: the eight-byte-element STLport unguarded insertion pass at
// 0x009F30B0.  Its caller at 0x009F3D30 is the matched final-insertion split:
// first+16 and last are passed here with STLport's dead value-type pointer and
// an empty comparator.  The body moves both dwords and compares the float at
// +4, shifting while the saved value is greater than its predecessor.

struct S3Elem009F30B0
{
	int m_value;
	float m_key;
};

struct S3Greater009F30B0
{
	bool operator()(const S3Elem009F30B0 &left,
		const S3Elem009F30B0 &right) const
	{
		return left.m_key > right.m_key;
	}
};

void Gen009F30B0(S3Elem009F30B0 *first, S3Elem009F30B0 *last,
	S3Elem009F30B0 *, S3Greater009F30B0 comp)
{
	for (S3Elem009F30B0 *i = first; i != last; ++i)
	{
		S3Elem009F30B0 value = *i;
		S3Elem009F30B0 *cur = i;
		S3Elem009F30B0 *next = i - 1;
		while (comp(value, *next))
		{
			*cur = *next;
			cur = next;
			--next;
		}
		*cur = value;
	}
}
