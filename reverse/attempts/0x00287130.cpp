// ?d_00287130@@YAXXZ
// partial score=0.75 date=2026-09-03
#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

class Object {};
class Player {};

class BfmeGuard96
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
	BFME_TEN_VIRTUALS(v80);
	virtual void v90(void);
	virtual void v91(void);
	virtual void v92(void);
	virtual void v93(void);
	virtual void v94(void);
	virtual void v95(void);
	virtual bool bfmeAllows(void);
};

struct RvaC4390Interface
{
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void v5(void);
	virtual int bfmeState(void);
	virtual int bfmeValue(void);
};

struct RvaC4390First : public Object
{
	RvaC4390Interface *getInterface(void);

	char m_bfmeFields[0x204];
	BfmeGuard96 *m_bfmeGuard;
};

struct RvaC4390Second
{
	RvaC4390First *resolve(int mode);
};

class BfmePlayerSource
{
public:
	Player *bfmePlayer(void);

	char m_bfmeFields[0x74];
	int m_bfmeValue;
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *object, Player *player);
};

struct BfmeFilterHolder
{
	char m_bfmeFields[8];
	Rva2225E0Filter m_bfmeFilter;
};

class Gen_00287130
{
public:
	bool bfmeAccept(RvaC4390Second *source);

private:
	char m_bfmeFields[0xE4];
	BfmeFilterHolder *m_bfmeFilterHolder;
	BfmePlayerSource *m_bfmePlayerSource;
};

// ?bfmeAccept@Gen_00287130@@QAE_NPAVRvaC4390Second@@@Z
bool Gen_00287130::bfmeAccept(RvaC4390Second *source)
{
	RvaC4390First *first = source->resolve(0);
	BfmeFilterHolder *filterHolder = m_bfmeFilterHolder;
	if (first != 0) {
		BfmeGuard96 *guard = first->m_bfmeGuard;
		if (guard == 0 || guard->bfmeAllows()) {
			RvaC4390Interface *interface = first->getInterface();
			if (interface != 0) {
				BfmePlayerSource *playerSource = m_bfmePlayerSource;
				Player *player = playerSource->bfmePlayer();
				if (filterHolder->m_bfmeFilter.accepts(first, player)) {
					int value = interface->bfmeValue();
					if (value == 0 ||
						interface->bfmeValue() == playerSource->m_bfmeValue)
						return interface->bfmeState() == 0;
				}
			}
		}
	}

	return false;
}

#undef BFME_TEN_VIRTUALS
