// Three more repeated bodies, every copy converted here under its own name: a
// four-byte number taken through a guarded window and turned around, and two
// counted runs of fixed-width slots copied across.
//
// The 0xEC-wide pair carried a six-byte-short ledger bound: the dump rows put
// both bodies at seventy-seven bytes, but the count<=0 arm that hands the
// destination straight back runs to eighty-three, with padding after it in
// both places. The rows are claimed at their true length.

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);

const unsigned char *bfmeReadKJ(const unsigned char *at, unsigned long *out, const unsigned char *end)
{
	unsigned long raw;

	if (end == 0 || (at <= end && at + 4 <= end))
	{
		raw = *(const unsigned long *)at;

		at += 4;
	}

	*out = htonl(raw);

	return at;
}

const unsigned char *bfmeReadKM(const unsigned char *at, unsigned long *out, const unsigned char *end)
{
	unsigned long raw;

	if (end == 0 || (at <= end && at + 4 <= end))
	{
		raw = *(const unsigned long *)at;

		at += 4;
	}

	*out = htonl(raw);

	return at;
}

struct BfmeElemKK
{
	int m_bfmeWords[7];			// 0x00
};

BfmeElemKK *bfmeCopyKK(const BfmeElemKK *first, const BfmeElemKK *last, BfmeElemKK *out)
{
	int count = (int)(last - first);

	while (count > 0)
	{
		*out = *first;

		++first;
		++out;
		--count;
	}

	return out;
}

struct BfmeElemKL
{
	char m_bfmeBytes[0xec];			// 0x00
};

BfmeElemKL *bfmeCopyKL(const BfmeElemKL *first, const BfmeElemKL *last, BfmeElemKL *out)
{
	int count = (int)(last - first);

	while (count > 0)
	{
		*out = *first;

		++first;
		++out;
		--count;
	}

	return out;
}

struct BfmeElemKN
{
	int m_bfmeWords[7];			// 0x00
};

BfmeElemKN *bfmeCopyKN(const BfmeElemKN *first, const BfmeElemKN *last, BfmeElemKN *out)
{
	int count = (int)(last - first);

	while (count > 0)
	{
		*out = *first;

		++first;
		++out;
		--count;
	}

	return out;
}

struct BfmeElemKO
{
	int m_bfmeWords[7];			// 0x00
};

BfmeElemKO *bfmeCopyKO(const BfmeElemKO *first, const BfmeElemKO *last, BfmeElemKO *out)
{
	int count = (int)(last - first);

	while (count > 0)
	{
		*out = *first;

		++first;
		++out;
		--count;
	}

	return out;
}

struct BfmeElemKP
{
	char m_bfmeBytes[0xec];			// 0x00
};

BfmeElemKP *bfmeCopyKP(const BfmeElemKP *first, const BfmeElemKP *last, BfmeElemKP *out)
{
	int count = (int)(last - first);

	while (count > 0)
	{
		*out = *first;

		++first;
		++out;
		--count;
	}

	return out;
}
