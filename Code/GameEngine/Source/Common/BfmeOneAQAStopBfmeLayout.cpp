// BFME layout reconstruction of BfmeOneAQA::bfmeStopAQA.  The body is a
// virtual stop notification, a letterbox hide, a guarded singleton callback,
// and a final virtual state notification.

void HideControlBar(int immediate);

class BfmeSingletonH
{
public:
	void j_0001d6c4();
};

extern BfmeSingletonH *g_bfmeSingletonH;

class BfmeOneAQA
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void stop(int first, int second);
	void bfmeStopAQA(void);
};

class BfmeStateDO
{
public:
	virtual void slot00();
	virtual void notify();
};

void BfmeOneAQA::bfmeStopAQA(void)
{
	stop(0, 1);
	HideControlBar(1);

	if (g_bfmeSingletonH != 0)
		g_bfmeSingletonH->j_0001d6c4();

	BfmeStateDO *state = *reinterpret_cast<BfmeStateDO **>(0x012F1028);
	if (state != 0)
		state->notify();
}
