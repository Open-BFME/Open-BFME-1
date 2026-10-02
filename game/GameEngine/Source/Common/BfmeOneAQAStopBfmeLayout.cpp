// BFME layout reconstruction of BfmeOneAQA::bfmeStopAQA.  The body is a
// virtual stop notification, a letterbox hide, a guarded singleton callback,
// and a final virtual state notification.

void HideControlBar(int immediate);

// The singleton at 0x012F706C is retail's ?g_bfmeGameCW@@3PAVBfmeGameCW@@A
// (dir32_addresses.csv); only the member j_0001d6c4 is pinned under the local
// view's name, so the global carries its real type and the view is applied at
// the call.
class BfmeGameCW;

class BfmeSingletonH
{
public:
	void j_0001d6c4();
};

extern BfmeGameCW *g_bfmeGameCW;

class CampaignManager;
extern CampaignManager *TheLivingWorldLogic;

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

	if (g_bfmeGameCW != 0)
		reinterpret_cast<BfmeSingletonH *>(g_bfmeGameCW)->j_0001d6c4();

	BfmeStateDO *state = reinterpret_cast<BfmeStateDO *>(TheLivingWorldLogic);
	if (state != 0)
		state->notify();
}
