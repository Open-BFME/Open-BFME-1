unsigned int __cdecl bfmeHashFI(void *first, void *second);

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
