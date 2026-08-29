// Open-BFME5 conversions.

class BfmeProbe956
{
public:
	virtual void bfmeV0956();
	virtual void bfmeV1956();
	virtual void bfmeV2956();
	virtual void bfmeV3956();
	virtual bool bfmeReady956();
};

class BfmeAI956
{
public:
	virtual void bfmeV0956();
	virtual void bfmeV1956();
	virtual void bfmeV2956();
	virtual void bfmeV3956();
	virtual void bfmeV4956();
	virtual void bfmeV5956();
	virtual void bfmeV6956();
	virtual void bfmeV7956();
	virtual void bfmeV8956();
	virtual void bfmeV9956();
	virtual void bfmeV10956();
	virtual void bfmeV11956();
	virtual void bfmeV12956();
	virtual void bfmeV13956();
	virtual void bfmeV14956();
	virtual void bfmeV15956();
	virtual void bfmeV16956();
	virtual void bfmeV17956();
	virtual void bfmeV18956();
	virtual void bfmeV19956();
	virtual void bfmeV20956();
	virtual void bfmeV21956();
	virtual void bfmeV22956();
	virtual void bfmeV23956();
	virtual void bfmeV24956();
	virtual void bfmeV25956();
	virtual void bfmeV26956();
	virtual void bfmeV27956();
	virtual void bfmeV28956();
	virtual void bfmeV29956();
	virtual void bfmeV30956();
	virtual void bfmeV31956();
	virtual void bfmeV32956();
	virtual void bfmeV33956();
	virtual void bfmeV34956();
	virtual void bfmeV35956();
	virtual void bfmeV36956();
	virtual void bfmeV37956();
	virtual void bfmeV38956();
	virtual void bfmeV39956();
	virtual void bfmeV40956();
	virtual void bfmeV41956();
	virtual void bfmeV42956();
	virtual void bfmeV43956();
	virtual void bfmeV44956();
	virtual void bfmeV45956();
	virtual void bfmeV46956();
	virtual void bfmeV47956();
	virtual void bfmeV48956();
	virtual void bfmeV49956();
	virtual void bfmeV50956();
	virtual void bfmeV51956();
	virtual void bfmeV52956();
	virtual void bfmeV53956();
	virtual void bfmeV54956();
	virtual void bfmeV55956();
	virtual void bfmeV56956();
	virtual void bfmeV57956();
	virtual void bfmeV58956();
	virtual void bfmeV59956();
	virtual void bfmeV60956();
	virtual void bfmeV61956();
	virtual void bfmeV62956();
	virtual void bfmeV63956();
	virtual void bfmeV64956();
	virtual void bfmeV65956();
	virtual void bfmeV66956();
	virtual void bfmeV67956();
	virtual void bfmeV68956();
	virtual void bfmeV69956();
	virtual void bfmeV70956();
	virtual void bfmeV71956();
	virtual void bfmeV72956();
	virtual void bfmeV73956();
	virtual void bfmeV74956();
	virtual void bfmeV75956();
	virtual void bfmeV76956();
	virtual void bfmeV77956();
	virtual void bfmeV78956();
	virtual void bfmeV79956();
	virtual void bfmeV80956();
	virtual BfmeProbe956 *bfmeProbe956();
	virtual void bfmeV82956();
	virtual void bfmeV83956();
	virtual void bfmeV84956();
	virtual void bfmeV85956();
	virtual void bfmeV86956();
	virtual void bfmeV87956();
	virtual void bfmeV88956();
	virtual void bfmeV89956();
	virtual void bfmeV90956();
	virtual void bfmeV91956();
	virtual void bfmeV92956();
	virtual void bfmeV93956();
	virtual void bfmeV94956();
	virtual void bfmeV95956();
	virtual bool bfmeBusy956();

	int bfmeKind956();
};

struct BfmeObj956
{
	char m_bfmePad[0x204];
	BfmeAI956 *m_bfmeAI;
};

struct BfmeOwner956
{
	char m_bfmePad[0x10];
	BfmeObj956 *m_bfmeObj;
};

struct BfmeState956
{
	char m_bfmePad[0x1c];
	BfmeOwner956 *m_bfmeOwner;
};

char bfmeReadyA956(BfmeState956 *state, void *user)
{
	BfmeAI956 *ai = state->m_bfmeOwner->m_bfmeObj->m_bfmeAI;
	BfmeProbe956 *p;

	return ai != 0 && (p = ai->bfmeProbe956()) != 0 && p->bfmeReady956() && ai->bfmeBusy956();
}

char bfmeReadyB956(BfmeState956 *state, void *user)
{
	BfmeAI956 *ai = state->m_bfmeOwner->m_bfmeObj->m_bfmeAI;

	return ai != 0 && !ai->bfmeBusy956() && ai->bfmeKind956() != 14 && ai->bfmeKind956() != 47;
}

struct BfmeInfo956
{
	char m_bfmePad[0x2c];
	int m_bfmeMode;
};

class BfmeKey956
{
public:
	BfmeInfo956 *bfmeFind956();
};

struct BfmeTune956
{
	char m_bfmePad[0x88];
	float m_bfmeScale;
};

struct BfmeGlob956
{
	char m_bfmePad[0x14];
	BfmeTune956 *m_bfmeTune;
};

extern BfmeGlob956 *g_bfmeGlob956;

struct BfmeSrc956
{
	char m_bfmePad[0x6c];
	float m_bfmeBase;
};

class BfmeScale956
{
public:
	float bfmeGo956();
};

float BfmeScale956::bfmeGo956()
{
	if ((*(BfmeKey956 **)((char *)this - 0x338))->bfmeFind956()
			&& (*(BfmeKey956 **)((char *)this - 0x338))->bfmeFind956()->m_bfmeMode == 1) {
		BfmeSrc956 *s = *(BfmeSrc956 **)((char *)this - 0x33c);
		return s->m_bfmeBase * g_bfmeGlob956->m_bfmeTune->m_bfmeScale;
	}

	BfmeSrc956 *s = *(BfmeSrc956 **)((char *)this - 0x33c);
	return s->m_bfmeBase;
}
