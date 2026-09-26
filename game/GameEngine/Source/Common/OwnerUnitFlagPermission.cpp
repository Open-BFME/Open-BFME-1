// ?Rva0025DDB0@BfmeOwnerXR@@QAE_NPAX@Z
// Permission gate: refuse when the owner's own check fails, otherwise allow
// unless the stored key resolves to a unit whose low flag bit is clear.

class BfmeUnitXR
{
public:
	unsigned char m_bfmeHeadXR[0x344];
	unsigned char m_bfmeFlagsXR;
};

struct Rva00367E30Logic
{
	BfmeUnitXR *bfmeFindXR(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerXR
{
public:
	bool Rva0025DDB0(void *item);
	bool bfmeCheckXR(void *item);

	unsigned char m_bfmeHeadXR[0x8c];
	void *m_bfmeKeyXR;
};

// The return type must be bool so the first exit reuses al from the test, and
// the last two conditions must stay one short-circuit expression so both reach
// the shared 32-bit `mov eax,1`; four separate returns merge them instead.
bool BfmeOwnerXR::Rva0025DDB0(void *item)
{
	if (!bfmeCheckXR(item))
		return false;

	void *key = m_bfmeKeyXR;

	if (key == 0)
		return true;

	BfmeUnitXR *unit = TheBfmeGameLogic->bfmeFindXR(key);

	return unit == 0 || (unit->m_bfmeFlagsXR & 1) != 0;
}
