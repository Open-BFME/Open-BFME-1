// cl: /O2

struct BfmePod16WR
{
	char m_b[16];
};

struct BfmeTagWR
{
};

// Retail reaches the 16-byte __copy (pin 0x0003F369) and the fill-insert
// (pin 0x00012EFE) only through five-byte ILT thunks, defined as
// ?j_0003f369@@YAXXZ (thunks_030.cpp) and ?j_00012efe@@YAXXZ (thunks_008.cpp).
// Both are called through a function / thiscall member pointer of the real
// shape, as BfmeConv1816.cpp does.
extern void j_0003f369();
extern void j_00012efe();

typedef BfmePod16WR *(__cdecl *BfmeCopyWRThunk)(BfmePod16WR *first, BfmePod16WR *last, BfmePod16WR *result, const BfmeTagWR &, int *);

class BfmeVecWR
{
public:
	BfmePod16WR *begin() { return m_start; }
	BfmePod16WR *end() { return m_finish; }
	unsigned size() const { return (unsigned)(m_finish - m_start); }

	void resize(unsigned n, BfmePod16WR value);
	void resize(unsigned n);
	// fillInsert() is reached through the ILT thunk, not declared here.

	BfmePod16WR *m_start;
	BfmePod16WR *m_finish;
	BfmePod16WR *m_end;
};

typedef void (BfmeVecWR::*BfmeFillInsertThunk)(BfmePod16WR *pos, unsigned n, const BfmePod16WR &value);

union BfmeFillInsertCast
{
	void (__cdecl *freeFunction)();
	BfmeFillInsertThunk memberFunction;
};

void BfmeVecWR::resize(unsigned n, BfmePod16WR value)
{
	if (n < size())
	{
		BfmePod16WR *dest = m_start + n;
		m_finish = ((BfmeCopyWRThunk)&::j_0003f369)(end(), end(), dest, *reinterpret_cast<BfmeTagWR *>(&n), (int *)0);
	}
	else
		{
		BfmeFillInsertCast cast;
		cast.freeFunction = &::j_00012efe;
		(this->*cast.memberFunction)(end(), n - size(), value);
	}
}

// ?resize@BfmeVecWR@@QAEXI@Z 0x0074E790
void BfmeVecWR::resize(unsigned n)
{
	BfmePod16WR value = BfmePod16WR();
	if (n < size())
	{
		BfmePod16WR *dest = m_start + n;
		m_finish = ((BfmeCopyWRThunk)&::j_0003f369)(end(), end(), dest,
			*reinterpret_cast<BfmeTagWR *>(&n), (int *)0);
	}
	else
		{
		BfmeFillInsertCast cast;
		cast.freeFunction = &::j_00012efe;
		(this->*cast.memberFunction)(end(), n - size(), value);
	}
}
