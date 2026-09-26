// Open-BFME5 conversions.

class BfmeCalc919G
{
public:
	int bfmeCalc919G();
};

class BfmeObj919G
{
public:
	virtual void bfmeSlot91900();
	virtual void bfmeSlot91901();
	virtual void bfmeSlot91902();
	virtual void bfmeSlot91903();
	virtual void bfmeSlot91904();
	virtual void bfmeSlot91905();
	virtual void bfmeSlot91906();
	virtual void bfmeSlot91907();
	virtual void bfmeSlot91908();
	virtual void bfmeSlot91909();
	virtual void bfmeSlot91910();
	virtual void bfmeSlot91911();
	virtual void bfmeSlot91912();
	virtual void bfmeSlot91913();
	virtual void bfmeSlot91914();
	virtual void bfmeSlot91915();
	virtual void bfmeSlot91916();
	virtual void bfmeSlot91917();
	virtual void bfmeSlot91918();
	virtual void bfmeSlot91919();
	virtual void bfmeSlot91920();
	virtual void bfmeVirt919G(int r);
};

class BfmeThing919G
{
public:
	void bfmeGo919G(void *a, void *b, void *c);
	char m_bfmePad[8];
	BfmeCalc919G *m_bfmeCalc;
	char m_bfmePad2[0x18];
	BfmeObj919G *m_bfmeObj;
};

void BfmeThing919G::bfmeGo919G(void *a, void *b, void *c)
{
	if (m_bfmeObj)
		m_bfmeObj->bfmeVirt919G(m_bfmeCalc->bfmeCalc919G());
}

class BfmeThing919H
{
public:
	void bfmeGo919H(void *a, void *b, void *c);
	char m_bfmePad[8];
	BfmeCalc919G *m_bfmeCalc;
	BfmeObj919G *m_bfmeObj;
};

void BfmeThing919H::bfmeGo919H(void *a, void *b, void *c)
{
	if (m_bfmeObj)
		m_bfmeObj->bfmeVirt919G(m_bfmeCalc->bfmeCalc919G());
}
