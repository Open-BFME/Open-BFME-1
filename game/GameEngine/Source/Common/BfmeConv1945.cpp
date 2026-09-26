class BfmeRecEQR
{
public:
	BfmeRecEQR(void *first, void *second, BfmeRecEQR **ownerLink);

	unsigned char m_bfmeBodyEQR[0x30];
};

class BfmeThingEQR
{
public:
	virtual void bfmeSlot0EQR();
	virtual void bfmeSlot1EQR();
	virtual void bfmeSlot2EQR();
	virtual void bfmeSlot3EQR();
	virtual void bfmeSlot4EQR();
	virtual void bfmeSlot5EQR(BfmeRecEQR *rec);
	virtual void *bfmeSlot6EQR();
};

class BfmeHostEQR
{
public:
	void bfmeAddEQR(BfmeThingEQR *thing);
	void bfmeLinkEQR(BfmeRecEQR *rec);

	unsigned char m_bfmeHeadEQR[0xe4];
	BfmeRecEQR *m_bfmeListEQR;
};

void BfmeHostEQR::bfmeAddEQR(BfmeThingEQR *thing)
{
	if (thing == 0)
		return;

	if (thing->bfmeSlot6EQR() != 0)
		return;

	BfmeRecEQR *rec = new BfmeRecEQR(this, thing, &m_bfmeListEQR);

	thing->bfmeSlot5EQR(rec);
	bfmeLinkEQR(rec);
}
