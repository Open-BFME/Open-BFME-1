// cl: /DNDEBUG /MD /EHsc

// Walk the list, delete each node, then the base destructor.
//
// The next pointer at +0x108 is read before the delete rather than after, which
// is the only order that works and is what the hoisted load shows. Two null
// tests appear per iteration and both belong: the outer one is the while
// condition, the inner one is the delete expression's own.
//
// The base destructor is called rather than inlined, so it is declared without a
// body here, and this class's own vptr is stored at entry as every destructor
// does.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	virtual ~UpgradeTemplate();

	UpgradeTemplate *friend_getNext(void) const { return m_next; }

private:
	unsigned char m_head[0x104];
	UpgradeTemplate *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter : public SubsystemInterface
{
public:
	virtual ~UpgradeCenter();

private:
	int m_04;
	UpgradeTemplate *m_upgradeList;
};

// ??1UpgradeCenter@@UAE@XZ
UpgradeCenter::~UpgradeCenter()
{
	while (m_upgradeList != 0) {
		UpgradeTemplate *next = m_upgradeList->friend_getNext();
		delete m_upgradeList;
		m_upgradeList = next;
	}
}
