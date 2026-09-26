// cl: /DNDEBUG /MD /EHsc

class AsciiString;

class Rva0076F980MidFirst
{
public:
	Rva0076F980MidFirst()
	{
		m_begin = 0;
		m_end = 0;
	}

	AsciiString *m_begin;
	AsciiString *m_end;
};

class Rva0076F980MidEnd
{
public:
	Rva0076F980MidEnd()
		: m_capacity(0)
	{
	}

private:
	AsciiString *m_capacity;
};

class Rva0076F980Mid
{
public:
	Rva0076F980Mid()
	{
	}

	~Rva0076F980Mid();

	void clear()
	{
		erase(m_first.m_begin, m_first.m_end);
	}

	AsciiString *erase(AsciiString *first, AsciiString *last);

private:
	Rva0076F980MidFirst m_first;
	Rva0076F980MidEnd m_end;
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SubObjectsUpgrade.h
class SubObjectsUpgradeModuleData : public SubObjectsUpgradeModuleDataBase
{
public:
	SubObjectsUpgradeModuleData();
	virtual ~SubObjectsUpgradeModuleData();

private:
	Rva0076F980Mid m_showSubObjectNames;
	Rva0076F980Mid m_hideSubObjectNames;
	Rva0076F980Mid m_upgradeSubObjectNames;
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
