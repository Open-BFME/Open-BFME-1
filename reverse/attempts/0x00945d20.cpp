// ?probe@Rva00945D20@@QAEEPAUArg00945D20@@@Z
// partial score=0.91 date=2026-09-04
// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Retail 0x00945D20 (55B): if m_atD8 is null return 1; else unsigned
// (m_atD8[+0xC] - m_atDC) >= 3*(*arg[+0x9C])*(arg[+0x24]) via sbb/inc.
// Retail overwrites the arg register with the lhs before the lea *3.

struct Node00945D20
{
	char m_pad[0x0C];
	int m_at0C;								///< +0x0C
};

struct Arg00945D20
{
	char m_pad00[0x24];
	int m_at24;								///< +0x24
	char m_pad28[0x9C - 0x28];
	int *m_at9C;							///< +0x9C
};

class Rva00945D20
{
public:
	unsigned char probe(Arg00945D20 *arg);

private:
	char m_pad[0xD8];
	Node00945D20 *m_node;					///< +0xD8
	int m_atDC;								///< +0xDC
};

// ?probe@Rva00945D20@@QAEEPAUArg00945D20@@@Z
unsigned char Rva00945D20::probe(Arg00945D20 *arg)
{
	Node00945D20 *node = m_node;
	if (!node)
		return 1;
	int scale = (*arg->m_at9C) * arg->m_at24;
	int lhs = node->m_at0C;
	lhs -= m_atDC;
	scale += scale << 1;
	return (unsigned)lhs >= (unsigned)scale;
}
