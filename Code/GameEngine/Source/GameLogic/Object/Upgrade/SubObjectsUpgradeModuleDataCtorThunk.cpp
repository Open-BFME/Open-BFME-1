// cl: /DNDEBUG /MD /EHsc

class SpawnBehaviorModuleDataMemberAFirst
{
public:
	SpawnBehaviorModuleDataMemberAFirst()
	{
		m_begin = 0;
		m_end = 0;
	}

	unsigned int *m_begin;
	unsigned int *m_end;
};

class SpawnBehaviorModuleDataMemberAEnd
{
public:
	SpawnBehaviorModuleDataMemberAEnd()
		: m_capacity(0)
	{
	}

private:
	unsigned int *m_capacity;
};

class SpawnBehaviorModuleDataMemberA
{
public:
	SpawnBehaviorModuleDataMemberA()
	{
	}

	~SpawnBehaviorModuleDataMemberA();

	void clear()
	{
		erase(m_first.m_begin, m_first.m_end);
	}

	void erase(unsigned int *first, unsigned int *last);

private:
	SpawnBehaviorModuleDataMemberAFirst m_first;
	SpawnBehaviorModuleDataMemberAEnd m_end;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_pad[0x68];
};

class SubObjectsUpgradeModuleDataMemberD
{
public:
	SubObjectsUpgradeModuleDataMemberD()
		: m_begin(0), m_end(0), m_capacity(0)
	{
	}

	~SubObjectsUpgradeModuleDataMemberD();

private:
	void **m_begin;
	void **m_end;
	void **m_capacity;
};

class __declspec(novtable) SubObjectsUpgradeModuleDataBase
{
public:
	SubObjectsUpgradeModuleDataBase()
	{
	}

	virtual ~SubObjectsUpgradeModuleDataBase();

private:
	unsigned int m_moduleData;
	UpgradeModuleDataSub m_upgradeData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SubObjectsUpgrade.h
class SubObjectsUpgradeModuleData : public SubObjectsUpgradeModuleDataBase
{
public:
	SubObjectsUpgradeModuleData();
	virtual ~SubObjectsUpgradeModuleData();

private:
	SpawnBehaviorModuleDataMemberA m_showSubObjectNames;
	SpawnBehaviorModuleDataMemberA m_hideSubObjectNames;
	SpawnBehaviorModuleDataMemberA m_upgradeSubObjectNames;
	SubObjectsUpgradeModuleDataMemberD m_replacementModels;
	unsigned int m_defaultConditionState;
	unsigned int m_defaultAnimationState;
	unsigned char m_showOnlySelected;
	unsigned char m_hideOnlySelected;
};

// ??0SubObjectsUpgradeModuleData@@QAE@XZ
SubObjectsUpgradeModuleData::SubObjectsUpgradeModuleData()
{
	m_defaultConditionState = 0;
	m_defaultAnimationState = 0;
	m_showOnlySelected = 0;
	m_hideOnlySelected = 0;
	m_showSubObjectNames.clear();
	m_hideSubObjectNames.clear();
	m_upgradeSubObjectNames.clear();
}
