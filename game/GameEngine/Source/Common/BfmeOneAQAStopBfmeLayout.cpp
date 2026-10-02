// BFME layout reconstruction of BfmeOneAQA::bfmeStopAQA.  The body is a
// virtual stop notification, a letterbox hide, a guarded singleton callback,
// and a final virtual state notification.

void HideControlBar(bool immediate);

// Retail 0x012F706C is LivingWorldManager *TheLivingWorldManager.  The
// shutdown call uses ILT 0x0001D6C4 to the matched body at 0x00617DB0.
class LivingWorldManager;

class BfmeHostAAY
{
public:
	void bfmeShutdownAAY();
};

extern LivingWorldManager *TheLivingWorldManager;

// Retail 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined
// once in game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

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
	HideControlBar(true);

	if (TheLivingWorldManager != 0)
		reinterpret_cast<BfmeHostAAY *>(TheLivingWorldManager)->bfmeShutdownAAY();

	BfmeStateDO *state = reinterpret_cast<BfmeStateDO *>(TheLivingWorldLogic);
	if (state != 0)
		state->notify();
}
