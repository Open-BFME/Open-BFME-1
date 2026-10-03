// Retail's release branch calls the ILT thunk at 0x00030841, which
// game/gen_small/thunks_023.cpp owns as ?j_00030841@@YAXXZ and forwards to
// 0x000C4CF0, then hands the same pointer to operator delete. The class the
// pointer names is not reconstructed here, so the destructor is reached through
// a member-call shape over the ledger's thunk name: the ecx load before the
// call is retail's own this-pointer store, and the `p != 0` test is what
// `delete` contributes, kept explicit because `delete` is no longer spelled.
void j_00030841(void);

class Inner82Target
{
public:
	void destruct();
};
typedef void (Inner82Target::*Inner82DtorCall)();

void operator delete(void *);

class BfmeObjCF
{
public:
	unsigned char m_bfmeHeadCF[0x10];
	int m_bfmeCountCF;
};

class BfmeRefCF
{
public:
	BfmeRefCF *bfmeAssignCF(const BfmeRefCF &other);

	BfmeObjCF *m_bfmePtrCF;
};

BfmeRefCF *BfmeRefCF::bfmeAssignCF(const BfmeRefCF &other)
{
	if (this != &other)
	{
		--m_bfmePtrCF->m_bfmeCountCF;

		if (m_bfmePtrCF->m_bfmeCountCF == 0)
		{
			BfmeObjCF *p = m_bfmePtrCF;

			if (p != 0)
			{
				union
				{
					void (*raw)(void);
					Inner82DtorCall member;
				} dtor;
				dtor.raw = j_00030841;

				(reinterpret_cast<Inner82Target *>(p)->*dtor.member)();
				::operator delete(p);
			}
		}

		m_bfmePtrCF = other.m_bfmePtrCF;
		m_bfmePtrCF->m_bfmeCountCF++;
	}

	return this;
}