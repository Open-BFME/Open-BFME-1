// cl: /O2 /Ob0

struct BfmeElemFC
{
	char m[0x5C];
	void copyFrom(BfmeElemFC *src);
};

BfmeElemFC *bfmeCopyFC(BfmeElemFC *first, BfmeElemFC *last, BfmeElemFC *dest)
{
	BfmeElemFC *d = dest;
	while (first != last)
	{
		if (d)
			d->copyFrom(first);
		first++;
		d++;
	}
	return d;
}
