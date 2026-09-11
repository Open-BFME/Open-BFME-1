// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// Open-BFME5: SlaveWatcherBehavior update.

typedef unsigned char Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_UNREADY = 5,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class AsciiString
{
private:
	unsigned char m_pad[4];
};

class UpgradeTemplate;

class GameLogic
{
public:
	class Object *findObjectByID(int id);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

class Object
{
public:
	void removeUpgrade(const UpgradeTemplate *upgrade);
	void giveUpgrade(const UpgradeTemplate *upgrade);
	void updateUpgradeModules();

	unsigned char m_pad[0x344];
	unsigned char m_status;
};

class SlaveWatcherBehaviorModuleDataBase
{
public:
	virtual ~SlaveWatcherBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[4];
};

class SlaveWatcherBehaviorModuleData : public SlaveWatcherBehaviorModuleDataBase
{
public:
	AsciiString m_giveUpgrade;
	AsciiString m_removeUpgrade;
};

extern GameLogic *TheGameLogic;
extern UpgradeCenter *TheUpgradeCenter;

class SlaveWatcherBehavior
{
public:
	virtual UpdateSleepTime update();
};

// ?update@SlaveWatcherBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SlaveWatcherBehavior::update()
{
	unsigned char *self = reinterpret_cast<unsigned char *>(this);
	int slaveID = *reinterpret_cast<int *>(self + 0x10);
	const SlaveWatcherBehaviorModuleData *data =
		*reinterpret_cast<const SlaveWatcherBehaviorModuleData **>(self - 0x0c);
	Object *owner = *reinterpret_cast<Object **>(self - 0x08);

	if (slaveID != 0)
	{
		Object *slave = TheGameLogic->findObjectByID(slaveID);
		if (slave != 0 && (slave->m_status & 1) != 0)
		{
			const UpgradeTemplate *remove = TheUpgradeCenter->findUpgrade(data->m_removeUpgrade);
			const UpgradeTemplate *give = TheUpgradeCenter->findUpgrade(data->m_giveUpgrade);
			owner->removeUpgrade(remove);
			owner->giveUpgrade(give);
			owner->updateUpgradeModules();
			*reinterpret_cast<int *>(self + 0x10) = 0;
			return UPDATE_SLEEP_FOREVER;
		}
	}

	return UPDATE_SLEEP_UNREADY;
}
