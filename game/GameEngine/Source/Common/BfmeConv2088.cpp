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

static __forceinline LocomotorOverridable *bfmeFinalXO(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04XO == 0)
		return p;

	return (LocomotorOverridable *)(const void *)((const Overridable *)p->m_bfme04XO)->getFinalOverride();
}

char bfmeCheckXO(Object *obj)
{
	if (obj == 0)
		return 0;
	else if ((bfmeFinalXO(obj->m_bfme04XO)->m_bfmeC8XO & 4) != 0)
		return 0;
	else
		return obj->getLayer() == 1;
}
