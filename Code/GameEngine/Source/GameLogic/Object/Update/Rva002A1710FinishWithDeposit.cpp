// cl: /DNDEBUG /MD /O2
// Open-BFME5: UpdateModule helper at retail 0x002A1710, 88 bytes.
// If the +0x2C flag is set: sleep forever, stamp completion fields, and
// deposit +0x3C into the controlling player's Money at Player+0x48.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object
{
public:
	class Player *getControllingPlayer() const;
};

class Money
{
public:
	void deposit(UnsignedInt amountToDeposit, bool playSound);
};

class Player
{
public:
	char m_pad00[0x48];
	Money m_money;
};

class UpdateModule
{
public:
	void bfmeFinishWithDeposit();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

private:
	void *m_vftable;
	void *m_moduleData;
	Object *m_object;
	char m_pad0C[0x20];
	UnsignedInt m_flag2C;
	UnsignedInt m_at30;
	int m_at34;
	char m_pad38[4];
	UnsignedInt m_depositAmount;
	unsigned char m_done40;
};

// ?bfmeFinishWithDeposit@UpdateModule@@QAEXXZ
void UpdateModule::bfmeFinishWithDeposit()
{
	Object *obj = m_object;
	Player *player = obj->getControllingPlayer();
	Money *money = player ? &player->m_money : 0;
	if (m_flag2C)
	{
		m_flag2C = 1;
		setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
		m_done40 = 1;
		m_at34 = -1;
		m_at30 = 0;
		money->deposit(m_depositAmount, true);
	}
}
