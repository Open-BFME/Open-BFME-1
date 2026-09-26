// ?bfmeUpdateXX@BfmeMoveXX@@QAE?AW4StateReturnType@@XZ
// partial score=0.75 date=2026-09-09
enum StateReturnType { BFME_STATE_FAILXX = -2 };

class BfmeBXX;
class BfmeOwnerXX;

class BfmeBXX
{
public:
	virtual void bfmeV00XX();
	virtual void bfmeV04XX();
	virtual void bfmeV08XX();
	virtual void bfmeV0CXX();
	virtual void bfmeV10XX();
	virtual void bfmeV14XX();
	virtual void bfmeApplyXX(void *a, int *b);
	virtual void bfmeV1CXX();
	virtual void bfmeV20XX();
	virtual void bfmeV24XX();
	virtual void bfmeV28XX();
	virtual void bfmeV2CXX();
	virtual void bfmeV30XX();
	virtual void bfmeV34XX();
	virtual char bfmeTestXX();
};

class BfmeOwnerXX
{
public:
	BfmeBXX *bfmeGetBXX();
};

class BfmeCtxXX
{
public:
	BfmeOwnerXX *bfmeGetOwnerXX();

	unsigned char m_bfmeHeadXX[0x10];
	void *m_bfme10XX;
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

class BfmeMoveXX : public AIInternalMoveToState
{
public:
	StateReturnType bfmeUpdateXX();

	unsigned char m_bfmeHeadXX[0x1c - 4];
	BfmeCtxXX *m_bfme1CXX;
	unsigned char m_bfmeMidXX[4];
	int m_bfme24XX;
};

StateReturnType BfmeMoveXX::bfmeUpdateXX()
{
	BfmeOwnerXX *owner;
	BfmeBXX *b;

	owner = m_bfme1CXX->bfmeGetOwnerXX();

	if (owner == 0 || (b = owner->bfmeGetBXX()) == 0 || !b->bfmeTestXX())
		return BFME_STATE_FAILXX;

	b->bfmeApplyXX(m_bfme1CXX->m_bfme10XX, &m_bfme24XX);

	return AIInternalMoveToState::update();
}
