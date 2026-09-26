struct S4SortElem12
{
	bool BfmeLess0052E880(const S4SortElem12 &o) const;
};

const S4SortElem12 &bfmeMedianXE(const S4SortElem12 &a, const S4SortElem12 &b, const S4SortElem12 &c)
{
	if (a.BfmeLess0052E880(b))
		if (b.BfmeLess0052E880(c))
			return b;
		else if (a.BfmeLess0052E880(c))
			return c;
		else
			return a;
	else if (a.BfmeLess0052E880(c))
		return a;
	else if (b.BfmeLess0052E880(c))
		return c;
	else
		return b;
}
