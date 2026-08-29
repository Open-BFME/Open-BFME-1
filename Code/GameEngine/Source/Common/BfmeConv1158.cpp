// Open-BFME5 conversions.

class BfmeArg1158;

class BfmeSub1158
{
public:
	virtual void bfmeSubVM01158();
	virtual void bfmeSubVM11158();
	virtual void bfmeSubVM21158();
	virtual void bfmeSubVM31158();
	virtual void bfmeSubVM41158();
	virtual void bfmeSubVM51158();
	virtual void bfmeSubVM61158();
	virtual void bfmeSubVM71158();
	virtual void bfmeSubVM81158();
	virtual void bfmeSubVM91158();
	virtual void bfmeSubVM101158();
	virtual void bfmeSubVM111158();
	virtual void bfmeSubVM121158();
	virtual void bfmeSubVM131158();
	virtual void bfmeSubA1158(BfmeArg1158 *a);
	virtual void bfmeSubVM151158();
	virtual void bfmeSubB1158();
	virtual void bfmeSubC1158(BfmeArg1158 *a);
	virtual void bfmeSubVM181158();
	virtual void bfmeSubVM191158();
	virtual void bfmeSubVM201158();
	virtual void bfmeSubVM211158();
	virtual void bfmeSubVM221158();
	virtual void bfmeSubVM231158();
	virtual void bfmeSubD1158(BfmeArg1158 *a);
	virtual void bfmeSubE1158(BfmeArg1158 *a);
	virtual void bfmeSubVM261158();
	virtual void bfmeSubVM271158();
	virtual void bfmeSubF1158();
	virtual void bfmeSubVM291158();
	virtual void bfmeSubVM301158();
	virtual void bfmeSubVM311158();
	virtual int bfmeSubG1158(BfmeArg1158 *a);
	virtual int bfmeSubH1158(BfmeArg1158 *a);
	virtual int bfmeSubI1158();
	virtual int bfmeSubJ1158();
};

class BfmeItem1158
{
public:
	virtual void bfmeVM01158();
	virtual void bfmeVM11158();
	virtual void bfmeVM21158();
	virtual void bfmeVM31158();
	virtual void bfmeVM41158();
	virtual void bfmeVM51158();
	virtual void bfmeVM61158();
	virtual void bfmeVM71158();
	virtual void bfmeVM81158();
	virtual void bfmeVM91158();
	virtual void bfmeVM101158();
	virtual void bfmeVM111158();
	virtual void bfmeVM121158();
	virtual void bfmeVM131158();
	virtual void bfmeVM141158();
	virtual void bfmeVM151158();
	virtual void bfmeVM161158();
	virtual void bfmeVM171158();
	virtual void bfmeVM181158();
	virtual void bfmeVM191158();
	virtual void bfmeVM201158();
	virtual void bfmeVM211158();
	virtual void bfmeVM221158();
	virtual void bfmeVM231158();
	virtual void bfmeVM241158();
	virtual void bfmeVM251158();
	virtual void bfmeVM261158();
	virtual void bfmeVM271158();
	virtual void bfmeVM281158();
	virtual void bfmeVM291158();
	virtual void bfmeVM301158();
	virtual void bfmeVM311158();
	virtual void bfmeVM321158();
	virtual void bfmeVM331158();
	virtual void bfmeVM341158();
	virtual void bfmeVM351158();
	virtual void bfmeVM361158();
	virtual void bfmeVM371158();
	virtual void bfmeVM381158();
	virtual BfmeSub1158 *bfmeGetSub1158();
	virtual void bfmeVM401158();
	virtual void bfmeVM411158();
	virtual void bfmeVM421158();
	virtual void bfmeVM431158();
	virtual void bfmeVM441158();
	virtual void bfmeVM451158();
	virtual void bfmeVM461158();
	virtual void bfmeVM471158();
	virtual void bfmeVM481158();
	virtual void bfmeVM491158();
	virtual void bfmeVM501158();
	virtual void bfmeItemStop1158(BfmeArg1158 *a);
	virtual void bfmeItemStopNow1158();
	virtual void bfmeVM531158();
	virtual void bfmeVM541158();
	virtual void bfmeStop1158(BfmeArg1158 *a);
	virtual void bfmeStart1158(BfmeArg1158 *a);
};

class BfmeOwner1158
{
public:
	void bfmeStopAll1158(BfmeArg1158 *a);
	void bfmeStartAll1158(BfmeArg1158 *a);
	void bfmeSubBAll1158(void);
	void bfmeSubFAll1158(void);
	void bfmeSubAAll1158(BfmeArg1158 *a);
	void bfmeSubCAll1158(BfmeArg1158 *a);
	void bfmeSubDAll1158(BfmeArg1158 *a);
	void bfmeSubEAll1158(BfmeArg1158 *a);
	int bfmeSubIAny1158(void);
	int bfmeSubJAny1158(void);
	int bfmeSubGAny1158(BfmeArg1158 *a);
	int bfmeSubHAny1158(BfmeArg1158 *a);
	void bfmeItemStopAll1158(BfmeArg1158 *a, char now);

	char m_bfmePad[0x150];
	BfmeItem1158 **m_bfmeItems;
};

void BfmeOwner1158::bfmeStartAll1158(BfmeArg1158 *a)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p)
		(*p)->bfmeStart1158(a);
}

void BfmeOwner1158::bfmeStopAll1158(BfmeArg1158 *a)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p)
		(*p)->bfmeStop1158(a);
}

void BfmeOwner1158::bfmeSubBAll1158(void)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s)
			s->bfmeSubB1158();
	}
}

void BfmeOwner1158::bfmeSubFAll1158(void)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s)
			s->bfmeSubF1158();
	}
}

void BfmeOwner1158::bfmeSubAAll1158(BfmeArg1158 *a)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s)
			s->bfmeSubA1158(a);
	}
}

void BfmeOwner1158::bfmeSubCAll1158(BfmeArg1158 *a)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s)
			s->bfmeSubC1158(a);
	}
}

void BfmeOwner1158::bfmeSubDAll1158(BfmeArg1158 *a)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s)
			s->bfmeSubD1158(a);
	}
}

void BfmeOwner1158::bfmeSubEAll1158(BfmeArg1158 *a)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s)
			s->bfmeSubE1158(a);
	}
}

int BfmeOwner1158::bfmeSubIAny1158(void)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s) {
			int r = s->bfmeSubI1158();

			if (r)
				return r;
		}
	}

	return 0;
}

int BfmeOwner1158::bfmeSubJAny1158(void)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s) {
			int r = s->bfmeSubJ1158();

			if (r)
				return r;
		}
	}

	return 0;
}

int BfmeOwner1158::bfmeSubGAny1158(BfmeArg1158 *a)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s) {
			int r = s->bfmeSubG1158(a);

			if (r)
				return r;
		}
	}

	return 0;
}

int BfmeOwner1158::bfmeSubHAny1158(BfmeArg1158 *a)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s) {
			int r = s->bfmeSubH1158(a);

			if (r)
				return r;
		}
	}

	return 0;
}

void BfmeOwner1158::bfmeItemStopAll1158(BfmeArg1158 *a, char now)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		if (now)
			(*p)->bfmeItemStopNow1158();
		else
			(*p)->bfmeItemStop1158(a);
	}
}
