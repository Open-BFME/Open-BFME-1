// cl: /Od /Ob1

inline bool bfmeEqVMD(const char &a, const char &b)
{
	return a == b;
}

const char *bfmeFindFirstOfVMD(const char *first1, const char *last1, const char *first2, const char *last2)
{
	for (; first1 != last1; ++first1)
	{
		for (const char *n1 = first2; n1 != last2; ++n1)
		{
			if (bfmeEqVMD(*first1, *n1))
				return first1;
		}
	}
	return last1;
}
