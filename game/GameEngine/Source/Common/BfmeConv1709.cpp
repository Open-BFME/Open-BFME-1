class BfmeThingGA
{
public:
	virtual void bfmeSlot0GA(void);
	virtual void bfmeSlot1GA(void);
	virtual void bfmeSlot2GA(void);
	virtual void bfmeSlot3GA(void);
	virtual void bfmeHandleGA(void *payload);
};

class BfmeItemGA
{
public:
	BfmeThingGA *bfmeResolveGA(void);
};

class BfmeNodeGA
{
public:
	BfmeNodeGA *m_bfmeNextGA;
	unsigned char m_bfmeMidGA[4];
	BfmeItemGA *m_bfmeItemGA;
};

class BfmeOwnerGA
{
public:
	void bfmeNotifyGA(void *payload);

	unsigned char m_bfmeHeadGA[4];
	BfmeNodeGA *m_bfmeListGA;
};

void BfmeOwnerGA::bfmeNotifyGA(void *payload)
{
	if (payload == 0)
		return;

	for (BfmeNodeGA *node = m_bfmeListGA->m_bfmeNextGA;
		node != m_bfmeListGA;
		node = node->m_bfmeNextGA)
	{
		BfmeThingGA *thing = node->m_bfmeItemGA->bfmeResolveGA();
		if (thing != 0)
			thing->bfmeHandleGA(payload);
	}
}
