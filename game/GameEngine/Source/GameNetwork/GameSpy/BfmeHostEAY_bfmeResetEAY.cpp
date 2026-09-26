class BfmeNodeEAY
{
public:
	int m_bfmeHeadNEAY;
	BfmeNodeEAY *m_bfmeNextEAY;
	BfmeNodeEAY *m_bfmePrevEAY;
	BfmeNodeEAY *m_bfmeTailEAY;
};

class BfmeListEAY
{
public:
	void bfmeEraseEAY(BfmeNodeEAY *node);

	BfmeNodeEAY *m_bfmeHeadEAY;
	int m_bfmeCountEAY;
};

class BfmeMsgEAY
{
public:
	BfmeMsgEAY();
	~BfmeMsgEAY();

	int m_bfmeKindEAY;
	unsigned char m_bfmeBodyEAY[0x190];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual void bfmeSlot00EAY();
	virtual void bfmeSlot01EAY();
	virtual void bfmeSlot02EAY();
	virtual void bfmeSlot03EAY();
	virtual void bfmeSlot04EAY();
	virtual void bfmeSlot05EAY();
	virtual void bfmePostEAY(BfmeMsgEAY *msg);
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class BfmeHostEAY
{
public:
	void bfmeResetEAY();

	unsigned char m_bfmeHeadEAY[0x4c];
	BfmeListEAY m_bfmeListEAY;
	unsigned char m_bfmePadAEAY[0x200];
	int m_bfmeAEAY;
	char m_bfmeBEAY;
	unsigned char m_bfmePadBEAY[0x46b];
	int m_bfmeFlagEAY;
};

void BfmeHostEAY::bfmeResetEAY()
{
	m_bfmeFlagEAY = 0;

	BfmeMsgEAY msg;

	msg.m_bfmeKindEAY = 0xc;

	TheGameSpyPeerMessageQueue->bfmePostEAY(&msg);

	BfmeListEAY *list = &m_bfmeListEAY;

	if (list->m_bfmeCountEAY != 0)
	{

		list->bfmeEraseEAY(list->m_bfmeHeadEAY->m_bfmeNextEAY);

		list->m_bfmeHeadEAY->m_bfmePrevEAY = list->m_bfmeHeadEAY;
		list->m_bfmeHeadEAY->m_bfmeNextEAY = 0;
		list->m_bfmeHeadEAY->m_bfmeTailEAY = list->m_bfmeHeadEAY;

		list->m_bfmeCountEAY = 0;
	}

	m_bfmeAEAY = 0;
	m_bfmeBEAY = 0;
}
