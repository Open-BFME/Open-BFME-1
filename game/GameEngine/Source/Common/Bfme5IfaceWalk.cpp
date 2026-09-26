// Open-BFME5 conversions: walks over a null-terminated item array at this+0x1f0.
//
// Each item carries an interface sub-object at +0x0c, which is why every call
// site is a `lea ecx,[item+0x0c]` rather than a plain move.

class Bfme5WalkSub
{
public:
	virtual void bfmeSV0();
	virtual void bfmeNotify();
};

class Bfme5WalkHit;

class Bfme5WalkAnswer
{
public:
	virtual int bfmeValue();
};

class Bfme5WalkIface
{
public:
	virtual void bfmeIV0();
	virtual void bfmeIV1();
	virtual void bfmeIV2();
	virtual Bfme5WalkSub *bfmeGetSub();
	virtual void bfmeIV4();
	virtual void bfmeIV5();
	virtual void bfmeIV6();
	virtual void bfmeIV7();
	virtual void bfmeIV8();
	virtual void bfmeIV9();
	virtual void bfmeIV10();
	virtual void bfmeIV11();
	virtual void bfmeIV12();
	virtual void bfmeIV13();
	virtual void bfmeIV14();
	virtual void bfmeIV15();
	virtual void bfmeIV16();
	virtual void bfmeIV17();
	virtual void bfmeIV18();
	virtual void bfmeIV19();
	virtual void bfmeIV20();
	virtual void bfmeIV21();
	virtual void bfmeIV22();
	virtual void bfmeIV23();
	virtual void bfmeIV24();
	virtual void *bfmePick();
	virtual void bfmeIV26();
	virtual void bfmeIV27();
	virtual void bfmeIV28();
	virtual void bfmeIV29();
	virtual void bfmeIV30();
	virtual void bfmeIV31();
	virtual void bfmeIV32();
	virtual void bfmeIV33();
	virtual void bfmeIV34();
	virtual void bfmeIV35();
	virtual void bfmeIV36();
	virtual void bfmeIV37();
	virtual void *bfmeFind();
};

class Bfme5WalkItem
{
public:
	char m_bfmePad[0x0c];
	Bfme5WalkIface m_bfmeIface;
};

class Bfme5WalkOwner
{
public:
	void bfmeNotifyAll(void);

	char m_bfmePad[0x1f0];
	Bfme5WalkItem **m_bfmeItems;
};

void Bfme5WalkOwner::bfmeNotifyAll(void)
{
	for (Bfme5WalkItem **p = m_bfmeItems; *p; ++p) {
		Bfme5WalkSub *s = (*p)->m_bfmeIface.bfmeGetSub();

		if (s)
			s->bfmeNotify();
	}
}

Bfme5WalkHit * __cdecl bfme5WalkFindHit(Bfme5WalkOwner *o)
{
	for (Bfme5WalkItem **p = o->m_bfmeItems; *p; ++p) {
		Bfme5WalkHit *h = (Bfme5WalkHit *)(*p)->m_bfmeIface.bfmeFind();

		if (h)
			return h;
	}

	return 0;
}

int __cdecl bfme5WalkFirstValue(Bfme5WalkOwner *o)
{
	for (Bfme5WalkItem **p = o->m_bfmeItems; *p; ++p) {
		Bfme5WalkAnswer *a = (Bfme5WalkAnswer *)(*p)->m_bfmeIface.bfmePick();

		if (a)
			return a->bfmeValue();
	}

	return 0;
}

