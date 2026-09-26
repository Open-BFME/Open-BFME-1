// cl: /DNDEBUG /MD /EHsc

class Gen00038951Owner
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeSlot1(void) = 0;
	virtual void bfmeSlot2(void) = 0;
	virtual void bfmeSlot3(void) = 0;
	virtual void bfmeSlot4(void) = 0;
	virtual void bfmeSlot5(void) = 0;
	virtual void bfmeSlot6(void) = 0;
	virtual void bfmeSlot7(void) = 0;
	virtual void bfmeSlot8(void) = 0;
	virtual bool bfmeContains(int value) = 0;
};

class Gen00038951
{
public:
	void bfmeRefresh(void);
	void handle(int value);

private:
	unsigned char m_unmodelled[4];
	Gen00038951Owner *m_owner;
	int m_first;
	int m_second;
};

// The retail body calls the same object's already pinned handle(int) ILT after
// validating both stored IDs through slot 9 of the owner interface.  Neither
// class exposes a retail spelling, so both names remain address-derived.
// ?bfmeRefresh@Gen00038951@@QAEXXZ
void Gen00038951::bfmeRefresh(void)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (m_first)
		handle(m_first);
}
