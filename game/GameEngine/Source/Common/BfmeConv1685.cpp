class BfmeRefEW;

class BfmeTargetEW
{
public:
	void bfmeSetReferenceEW(BfmeRefEW *reference);

	unsigned char m_bfmeHeadEW[0x9c];
	int m_bfmeLockEW;
};

class BfmeOwnerEW
{
public:
	void bfmeApplyEW(void);

	unsigned char m_bfmeHeadEW[0x34];
	BfmeTargetEW *m_bfmeTargetEW;
	unsigned char m_bfmeMidEW[0x1f4];
	BfmeRefEW *m_bfmeRefEW;
};

void BfmeOwnerEW::bfmeApplyEW(void)
{
	BfmeTargetEW *target = m_bfmeTargetEW;
	if (target == 0)
		return;

	BfmeRefEW *reference = m_bfmeRefEW;
	if (reference == 0)
		return;

	if (target->m_bfmeLockEW != 0)
		return;

	target->bfmeSetReferenceEW(reference);
}
