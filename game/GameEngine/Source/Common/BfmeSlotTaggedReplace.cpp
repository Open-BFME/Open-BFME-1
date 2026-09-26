// cl: /O2 /DNDEBUG /MD

class BfmeHeldC680
{
public:
	virtual void bfmeAddRefC680(void) = 0;
	virtual void bfmeReleaseC680(void) = 0;
	virtual void bfmeSpare002C680(void) = 0;
	virtual void bfmeSpare003C680(void) = 0;
	virtual void bfmeSpare004C680(void) = 0;
	virtual unsigned char bfmeIsUniqueC680(void) = 0;
};

struct BfmeSlotC680
{
	void *m_bfmeHead;
	void *m_bfmeHeld;
};

class BfmeStoreC680
{
public:
	void bfmePutC680(int index, BfmeHeldC680 *obj);

private:
	int m_bfmeHead;
	BfmeSlotC680 *m_bfmeSlots;
};

void BfmeStoreC680::bfmePutC680(int index, BfmeHeldC680 *obj)
{
	BfmeHeldC680 *old = (BfmeHeldC680 *)((unsigned)m_bfmeSlots[index].m_bfmeHeld & ~1u);
	obj->bfmeAddRefC680();
	if (old)
		old->bfmeReleaseC680();
	if (obj->bfmeIsUniqueC680() == 1)
		m_bfmeSlots[index].m_bfmeHeld = (void *)((unsigned)obj | 1);
	else
		m_bfmeSlots[index].m_bfmeHeld = obj;
}
