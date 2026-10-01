// cl: /O2
// Open-BFME: BfmeOwnerXO::bfmeCheck2XO, retail RVA 0x001FCCE0 (72B).
// The first guard is an early return.  The explicit failure label preserves
// retail's fall-through false block before the final true return block.

// retail walks the override chain through ILT 0x000022BB, which targets
// Overridable::getFinalOverride (matching row 0x00087A80).  The Locomotor view
// below stays unrelated to it; the pointer crosses as void so no code is
// emitted either way.
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class LocomotorOverridable
{
public:
	unsigned char m_bfmeHeadXO[4];
	LocomotorOverridable *m_bfme04XO;
	unsigned char m_bfmeMidXO[0xc0];
	unsigned char m_bfmeC8XO;
};

class Object
{
public:
	int getLayer() const;
	unsigned char m_bfmeHeadXO[4];
	LocomotorOverridable *m_bfme04XO;
};

class BfmeOwnerXO
{
public:
	char bfmeCheck2XO(Object *obj);
	unsigned char m_bfmeHeadXO[0x2c];
	int m_bfme2CXO;
};

static __forceinline LocomotorOverridable *bfmeFinalXO(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;
	if (p->m_bfme04XO == 0)
		return p;
	return (LocomotorOverridable *)(const void *)((const Overridable *)p->m_bfme04XO)->getFinalOverride();
}

char BfmeOwnerXO::bfmeCheck2XO(Object *obj)
{
	if (m_bfme2CXO != 1)
		return 0;
	if (obj == 0)
		goto fail;
	if ((bfmeFinalXO(obj->m_bfme04XO)->m_bfmeC8XO & 4) != 0)
		goto fail;
	if (obj->getLayer() != 1)
		goto fail;
	return 1;
fail:
	return 0;
}
