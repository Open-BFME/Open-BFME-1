// cl: /O2 /DNDEBUG /MD

class BfmeHeldC6E0
{
public:
	virtual void bfmeAddRefC6E0(void) = 0;
	virtual void bfmeSpare001C6E0(void) = 0;
	virtual void bfmeSpare002C6E0(void) = 0;
	virtual void bfmeSpare003C6E0(void) = 0;
	virtual void bfmeSpare004C6E0(void) = 0;
	virtual unsigned char bfmeIsUniqueC6E0(void) = 0;
};

struct BfmeSlotC6E0
{
	void *m_bfmeHead;
	void *m_bfmeHeld;
};

class BfmeStoreC6E0
{
public:
	void bfmePutC6E0(int index, BfmeHeldC6E0 *obj);

private:
	int m_bfmeHead;
	BfmeSlotC6E0 *m_bfmeSlots;
};

void BfmeStoreC6E0::bfmePutC6E0(int index, BfmeHeldC6E0 *obj)
{
	obj->bfmeAddRefC6E0();
	if (obj->bfmeIsUniqueC6E0() == 1)
		m_bfmeSlots[index].m_bfmeHeld = (void *)((unsigned)obj | 1);
	else
		m_bfmeSlots[index].m_bfmeHeld = obj;
}
