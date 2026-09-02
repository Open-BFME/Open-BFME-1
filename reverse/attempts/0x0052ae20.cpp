// ?bfmeFindNthPred@@YAHH@Z
// partial score=0.9 date=2026-09-02
// stlport
// cl: /EHs-c-

class Glo012F1028Type
{
public:
	int count();
	bool pred(int index);
};

extern Glo012F1028Type *Glo012F1028;

// Return the index of the n-th entry accepted by the global collection's
// predicate, or -1 when the collection is absent or has too few matches.
// ?bfmeFindNthPred@@YAHH@Z
int bfmeFindNthPred(int n)
{
	register int count;
	register int i;
	int remain = n;

	if (Glo012F1028 == 0)
		return -1;

	count = Glo012F1028->count();
	for (i = 0; i < count; ++i)
	{
		if (Glo012F1028->pred(i))
		{
			if (remain <= 0)
				return i;
			--remain;
		}
	}
	return -1;
}
