// ?d_0027def0@@YAXXZ
// partial score=0.78 date=2026-09-03
#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

class BfmeSlot14
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void bfmeReset(int value);
};

class BfmeSlot115
{
public:
	BFME_TEN_VIRTUALS(v000);
	BFME_TEN_VIRTUALS(v010);
	BFME_TEN_VIRTUALS(v020);
	BFME_TEN_VIRTUALS(v030);
	BFME_TEN_VIRTUALS(v040);
	BFME_TEN_VIRTUALS(v050);
	BFME_TEN_VIRTUALS(v060);
	BFME_TEN_VIRTUALS(v070);
	BFME_TEN_VIRTUALS(v080);
	BFME_TEN_VIRTUALS(v090);
	BFME_TEN_VIRTUALS(v100);
	virtual void v110(void);
	virtual void v111(void);
	virtual void v112(void);
	virtual void v113(void);
	virtual void v114(void);
	virtual void bfmeApply(int value, int enabled);
};

struct BfmeLookupObject
{
	char m_bfmeFields[0x204];
	BfmeSlot115 *m_bfmeSlot;
};

class GameLogicFrameSlice
{
public:
	BfmeLookupObject *bfmeFind(int handle);
};

extern GameLogicFrameSlice *TheGameLogic;

class BfmeInnerAKA
{
public:
	void bfmeSetAKA(int value);

private:
	char m_bfmeFields[0x10];
};

struct BfmeCommandOwner
{
	char m_bfmeFields[0x74];
	int m_bfmeValue;
};

class Gen_0027DEF0
{
public:
	void bfmeClear(int status);

private:
	char m_bfmeFields[8];
	BfmeCommandOwner *m_bfmeOwner;
	char m_bfme0C[0x14];
	BfmeInnerAKA m_bfmeInner;
	BfmeSlot14 *m_bfmeResetter;
	char m_bfme34[0x0C];
	int m_bfmeHandle;
	char m_bfme44[0x1B4];
	int m_bfmeStatus;
};

// ?bfmeClear@Gen_0027DEF0@@QAEXH@Z
void Gen_0027DEF0::bfmeClear(int status)
{
	m_bfmeStatus = status;
	if (status == -3) {
		if (m_bfmeHandle) {
			BfmeLookupObject *object = TheGameLogic->bfmeFind(m_bfmeHandle);
			if (object) {
				m_bfmeResetter->bfmeReset(0);
				m_bfmeInner.bfmeSetAKA(2);
			}
		}

		if (m_bfmeHandle) {
			BfmeCommandOwner *owner = m_bfmeOwner;
			BfmeLookupObject *object = TheGameLogic->bfmeFind(m_bfmeHandle);
			if (owner && object && object->m_bfmeSlot)
				object->m_bfmeSlot->bfmeApply(owner->m_bfmeValue, 0);
		}
	}

	m_bfmeHandle = 0;
}

#undef BFME_TEN_VIRTUALS
