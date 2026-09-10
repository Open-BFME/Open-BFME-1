// cl: /O2
// Open-BFME: BfmeOwnerXO::bfmeCheck2XO, retail RVA 0x001FCCE0 (72B).
// The first guard is an early return.  The explicit failure label preserves
// retail's fall-through false block before the final true return block.

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();
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
	return p->m_bfme04XO->friend_getFinalOverride();
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
