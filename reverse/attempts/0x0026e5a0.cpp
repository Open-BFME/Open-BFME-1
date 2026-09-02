// ?bfmeStalled@Gen_0026E5A0@@QBE_NXZ
// partial score=0.55 date=2026-09-02
// Sibling of Gen_0026E570::bfmeActive: same +4 list / +0x10 guard, but
// walks the list (next at +8, deadline at +0x20) with a 100-step budget.
// Retail is 60B: two-guard xor-al-ret stub, xor ecx / mov edx,7fffffff /
// push esi, then 7-byte lea esp,[esp] aligning the loop to 16, then
// mov esi,ecx / inc ecx / cmp esi,64h / jae fail / cmp [eax+20],edx.
// This compile keeps the algorithm and the two loads but folds the
// guard-fail into the loop-fail (je to a shared xor al,al) and keeps the
// sentinel as an immediate, so it is 46B and never emits the alignment pad.

class BfmeNodeE5A0
{
public:
	char m_pad00[8];
	BfmeNodeE5A0 *m_next;
	char m_pad0C[0x14];
	int m_deadline;
};

class Gen_0026E5A0
{
public:
	bool bfmeStalled(void) const;

private:
	int m_head;
	BfmeNodeE5A0 *m_list;
	int m_gap[2];
	int *m_guard;
};

// ?bfmeStalled@Gen_0026E5A0@@QBE_NXZ
bool Gen_0026E5A0::bfmeStalled(void) const
{
	BfmeNodeE5A0 *node = m_list;
	if (!node)
		return false;
	if (!m_guard)
		return false;

	int i = 0;
	int sentinel = 0x7fffffff;
	do
	{
		int prev = i;
		++i;
		if ((unsigned)prev >= 100)
			return false;
		if (node->m_deadline != sentinel)
			return true;
		node = node->m_next;
	} while (node);

	return false;
}
