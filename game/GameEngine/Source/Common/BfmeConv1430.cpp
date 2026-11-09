// cl: /Od /Ob1

struct BfmeRIterVMG
{
	BfmeRIterVMG() {}
	const char *m_current;
};

inline bool bfmeIterEqVMG(const BfmeRIterVMG &a, const BfmeRIterVMG &b)
{
	return a.m_current == b.m_current;
}

inline bool bfmeIterNeVMG(BfmeRIterVMG a, const BfmeRIterVMG &b)
{
	return !bfmeIterEqVMG(a, b);
}

inline const char &bfmeDerefVMG(BfmeRIterVMG a)
{
	--a.m_current;
	return *a.m_current;
}

inline bool bfmeEqVMG(const char &a, const char &b)
{
	return a == b;
}

BfmeRIterVMG bfmeFindFirstOfVMG(BfmeRIterVMG first1, BfmeRIterVMG last1, const char *first2, const char *last2)
{
	for (; bfmeIterNeVMG(first1, last1); --first1.m_current)
	{
		for (const char *n1 = first2; n1 != last2; ++n1)
		{
			if (bfmeEqVMG(bfmeDerefVMG(first1), *n1))
				return first1;
		}
	}
	return last1;
}
