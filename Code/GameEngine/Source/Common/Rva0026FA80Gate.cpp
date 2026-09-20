// Retail 0x0026FA80: a thiscall predicate over this->[+0x08] (the "engaged"
// object) and one stack int. Five guarded checks run in sequence -- a shared
// query, a four-slot acceptance test, two derived byte flags fetched off the
// query result, a per-player field, and two direct flags on the engaged
// object itself -- and the function returns TRUE (blocked) the moment any
// one of them fails; only when every guard passes does it return FALSE
// (allowed). The owning class and the engaged object's real identity were
// not recovered across two prior passes, so every name below is
// address-derived. Every callee is reached through the same pinned/thunk
// route its landed neighbours already use:
//   0x00009C41 -> pinned ?bfmeAskCLE@BfmeSubCLE@@QAEPAVBfmeXCLE@@H@Z
//   0x0002E85C -> pinned ?bfmeAccepts@BfmeFourSlotEntry@@QAE_NPAVBfmeFourSlotSource@@HH@Z
//   0x00028F74 -> pinned ?bfmeAEQT@BfmeSubEQT@@QAEDXZ (thunk target 0x001E1770,
//       the DispByteFieldGetters family's disp-0x4ED byte)
//   0x0000CCD4 -> thunk to the landed Rva001E1780ByteField::get() (disp 0x4EE),
//       the adjacent byte in that same family -- reused here under its
//       already-matched name rather than re-pinned
//   0x00020824 -> pinned ?bfmeCur1094@BfmeK1094@@QAEPAVBfmeR1094@@XZ

class BfmeXCLE;

class BfmeSubCLE
{
public:
	BfmeXCLE *bfmeAskCLE(int value);
};

class BfmeFourSlotSource;

class BfmeFourSlotEntry
{
public:
	bool bfmeAccepts(BfmeFourSlotSource *source, int value, int mode);
};

class BfmeSubEQT
{
public:
	char bfmeAEQT();
};

class Rva001E1780ByteField
{
public:
	unsigned char get() const;
};

class BfmeR1094;

class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094(void);
};

// The object returned by bfmeAskCLE: only the +0x04 pointer used by the
// next two guards is witnessed.
class Rva0026FA80Query
{
public:
	unsigned char m_unmodelled_000[4];
	void *m_sub;
};

// The far tail of the engaged object: only the two witnessed flags and the
// pointer between them are named, everything else is unmodelled gap.
class Rva0026FA80Extra
{
public:
	unsigned char m_unmodelled_000[0x32f];
	unsigned char m_flag32f;
};

class Rva0026FA80Engaged
{
public:
	unsigned char m_unmodelled_000[0x1f5];
	unsigned char m_flag1f5;
	unsigned char m_unmodelled_1f6[0x204 - 0x1f6];
	Rva0026FA80Extra *m_extra;
};

class Rva0026FA80
{
public:
	bool evaluate(int value);

private:
	unsigned char m_unmodelled_000[8];
	Rva0026FA80Engaged *m_engaged;
};

bool Rva0026FA80::evaluate(int value)
{
	BfmeXCLE *x;
	Rva0026FA80Query *query;
	BfmeR1094 *player;

	x = reinterpret_cast<BfmeSubCLE *>(m_engaged)->bfmeAskCLE(0);
	if (x)
	{
		if (!reinterpret_cast<BfmeFourSlotEntry *>(x)->bfmeAccepts(
				reinterpret_cast<BfmeFourSlotSource *>(m_engaged), value, 0))
		{
			query = reinterpret_cast<Rva0026FA80Query *>(x);

			if (!reinterpret_cast<BfmeSubEQT *>(query->m_sub)->bfmeAEQT())
			{
				if (!reinterpret_cast<Rva001E1780ByteField *>(query->m_sub)->get())
				{
					player = reinterpret_cast<BfmeK1094 *>(m_engaged)->bfmeCur1094();

					if (!*reinterpret_cast<int *>(reinterpret_cast<char *>(player) + 0x2c))
					{
						if (m_engaged->m_extra)
						{
							if (!m_engaged->m_extra->m_flag32f)
							{
								if (!m_engaged->m_flag1f5)
									return false;
							}
						}
					}
				}
			}
		}
	}

	return true;
}
