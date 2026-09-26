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

static __forceinline LocomotorOverridable *bfmeFinalXO(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04XO == 0)
		return p;

	return p->m_bfme04XO->friend_getFinalOverride();
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
