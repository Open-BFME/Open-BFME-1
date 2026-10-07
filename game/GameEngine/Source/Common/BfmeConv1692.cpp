// Retail calls ILT 0x00007518 -> 0x00592FE0, the matched __cdecl wrapper Rva00592FE0.
int __cdecl Rva00592FE0(int first, int second);

inline unsigned int bfmeHashFI(void *first, void *second)
{
	return (unsigned int)Rva00592FE0((int)first, (int)second);
}

class BfmeKeyFI
{
public:
	int bfmeMatchFI(BfmeKeyFI *other);

	unsigned char m_bfmeHeadFI[4];
	void *m_bfmeDataFI;
};

int BfmeKeyFI::bfmeMatchFI(BfmeKeyFI *other)
{
	void *mine = m_bfmeDataFI;
	void *theirs = other->m_bfmeDataFI;
	return bfmeHashFI(mine, theirs) == 0x944ada98;
}
