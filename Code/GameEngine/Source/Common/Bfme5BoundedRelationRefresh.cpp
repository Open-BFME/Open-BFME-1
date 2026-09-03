#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeRefreshPartitionCells(void);
};

class BfmeRelationRange
{
public:
	BFME_TEN_VIRTUALS(v00);
	BFME_TEN_VIRTUALS(v10);
	BFME_TEN_VIRTUALS(v20);
	BFME_TEN_VIRTUALS(v30);
	BFME_TEN_VIRTUALS(v40);
	BFME_TEN_VIRTUALS(v50);
	BFME_TEN_VIRTUALS(v60);
	BFME_TEN_VIRTUALS(v70);
	virtual void v80(void);
	virtual void v81(void);
	virtual void v82(void);
	virtual unsigned int bfmeLower(void);
	virtual void v84(void);
	virtual void v85(void);
	virtual unsigned int bfmeUpper(void);
	virtual Object *bfmeResolve(void *key);
};

class BfmeRelationSelector
{
public:
	BFME_TEN_VIRTUALS(v00);
	BFME_TEN_VIRTUALS(v10);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual BfmeRelationRange *bfmeRange(void);
};

struct BfmeRelationState
{
	char m_bfmeFields[0x1FC];
	BfmeRelationSelector *m_bfmeSelector;
};

struct BfmeRelationInput
{
	char m_bfmeFields[8];
	char m_bfmeKey[0x20C];
	BfmeRelationState *m_bfmeState;
};

struct BfmeRefreshContext
{
	char m_bfmeFields[0x34];
	void *m_bfmeLink;
};

void __cdecl bfmeLinkRelation(void *link, Object *object, int enabled);

class Gen_00283460
{
public:
	bool bfmeRefresh(BfmeRelationInput *input);

private:
	char m_bfmeFields[4];
	BfmeRefreshContext *m_bfmeContext;
};

// ?bfmeRefresh@Gen_00283460@@QAE_NPAUBfmeRelationInput@@@Z
bool Gen_00283460::bfmeRefresh(BfmeRelationInput *input)
{
	BfmeRelationState *state = input->m_bfmeState;
	if (state != 0) {
		BfmeRelationSelector *selector = state->m_bfmeSelector;
		if (selector == 0)
			return false;

		BfmeRelationRange *range = selector->bfmeRange();
		if (range != 0) {
			unsigned int lower = range->bfmeLower();
			unsigned int upper = range->bfmeUpper();
			if (upper < lower) {
				Object *object = range->bfmeResolve(input->m_bfmeKey);
				if (object != 0) {
					BfmeRefreshContext *context = m_bfmeContext;
					object->bfmeRefreshPartitionCells();
					if (context->m_bfmeLink != 0)
						bfmeLinkRelation(context->m_bfmeLink, object, 0);
					return true;
				}
			}
		}
	}

	return false;
}

#undef BFME_TEN_VIRTUALS
