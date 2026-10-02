// cl: /O2 /DNDEBUG /MD
// The call at +0x1E is the reference-replacement body at 0x0091FC90, defined by
// game/GameEngine/Source/Common/Rva0091FC90ReferenceSet.cpp under its real
// mangled name.  Its receiver layout is this file's BfmeTargetEW (the pointer
// both classes keep at +0x9C), so the target is cast to the owning class rather
// than a bfmeSetReferenceEW nothing defines.

class BfmeRefEW;

class Rva0091FC90Reference;
class Rva0091FC90Owner
{
public:
	void setReference(Rva0091FC90Reference *reference);
};

class BfmeTargetEW
{
public:
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

	((Rva0091FC90Owner *)target)->setReference((Rva0091FC90Reference *)reference);
}