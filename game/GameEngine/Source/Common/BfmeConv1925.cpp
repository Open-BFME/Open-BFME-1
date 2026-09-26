// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

class BfmeUpgradeSinkCN;

class BfmeSubCN
{
public:
	virtual void bfmeSlot00CN();
	virtual void bfmeSlot01CN();
	virtual void bfmeSlot02CN();
	virtual void bfmeSlot03CN();
	virtual void bfmeSlot04CN();
	virtual void bfmeSlot05CN();
	virtual void bfmeSlot06CN();
	virtual void bfmeSlot07CN();
	virtual void bfmeSlot08CN();
	virtual void bfmeSlot09CN();
	virtual void bfmeSlot10CN();
	virtual void bfmeSlot11CN();
	virtual void bfmeSlot12CN();
	virtual void bfmeSlot13CN();
	virtual void bfmeSlot14CN();
	virtual void bfmeSlot15CN();
	virtual void bfmeSlot16CN();
	virtual void bfmeSlot17CN();
	virtual void bfmeSlot18CN();
	virtual void bfmeSlot19CN();
	virtual void bfmeSlot20CN();
	virtual void bfmeSlot21CN();
	virtual void bfmeSlot22CN();
	virtual void bfmeSlot23CN();
	virtual void bfmeSlot24CN();
	virtual void bfmeSlot25CN();
	virtual BfmeUpgradeSinkCN *bfmeSlot26CN();
	virtual void bfmeSlot27CN();
	virtual void bfmeSlot28CN();
	virtual void bfmeSlot29CN();
	virtual void bfmeSlot30CN();
	virtual void bfmeSlot31CN();
	virtual void bfmeSlot32CN();
	virtual void bfmeSlot33CN();
	virtual void bfmeSlot34CN();
	virtual void bfmeSlot35CN();
	virtual void bfmeSlot36CN();
	virtual void bfmeSlot37CN();
	virtual void bfmeSlot38CN();
	virtual void bfmeSlot39CN();
	virtual void bfmeSlot40CN();
	virtual void bfmeSlot41CN();
	virtual void bfmeSlot42CN();
	virtual void bfmeSlot43CN();
	virtual void bfmeSlot44CN();
	virtual void bfmeSlot45CN();
	virtual void bfmeSlot46CN();
	virtual void bfmeSlot47CN();
	virtual void bfmeSlot48CN();
	virtual void bfmeSlot49CN();
	virtual void bfmeSlot50CN();
	virtual void bfmeSlot51CN();
	virtual void bfmeSlot52CN();
	virtual void bfmeSlot53CN();
	virtual void bfmeSlot54CN();
	virtual void bfmeSlot55CN();
	virtual void bfmeSlot56CN();
	virtual void bfmeStopCN();
};

class BfmeUnitCN
{
public:
	bool bfmeDoneCN();

	unsigned char m_bfmeHeadCN[0x1f0];
	class BfmeBehaviorModuleCN **m_bfmeBehaviorsCN;
	unsigned char m_bfmePadBehaviorsCN[8];
	BfmeSubCN *m_bfmeSubCN;
	class BfmeBodyDamageSourceCN *m_bfmeBodyCN;
	unsigned char m_bfmePadCN[0x10];
	BfmeUnitCN *m_bfmeContainedByCN;
};

class BfmeDoneInterfaceCN
{
public:
	virtual void bfmeDoneSlotCN();
};

class BfmeBehaviorModuleInterfaceCN
{
public:
	virtual void bfmeBehaviorSlot00CN();
	virtual void bfmeBehaviorSlot01CN();
	virtual void bfmeBehaviorSlot02CN();
	virtual void bfmeBehaviorSlot03CN();
	virtual void bfmeBehaviorSlot04CN();
	virtual void bfmeBehaviorSlot05CN();
	virtual void bfmeBehaviorSlot06CN();
	virtual void bfmeBehaviorSlot07CN();
	virtual void bfmeBehaviorSlot08CN();
	virtual void bfmeBehaviorSlot09CN();
	virtual void bfmeBehaviorSlot10CN();
	virtual void bfmeBehaviorSlot11CN();
	virtual void bfmeBehaviorSlot12CN();
	virtual void bfmeBehaviorSlot13CN();
	virtual void bfmeBehaviorSlot14CN();
	virtual void bfmeBehaviorSlot15CN();
	virtual void bfmeBehaviorSlot16CN();
	virtual void bfmeBehaviorSlot17CN();
	virtual void bfmeBehaviorSlot18CN();
	virtual void bfmeBehaviorSlot19CN();
	virtual void bfmeBehaviorSlot20CN();
	virtual void bfmeBehaviorSlot21CN();
	virtual void bfmeBehaviorSlot22CN();
	virtual void bfmeBehaviorSlot23CN();
	virtual void bfmeBehaviorSlot24CN();
	virtual void bfmeBehaviorSlot25CN();
	virtual void bfmeBehaviorSlot26CN();
	virtual void bfmeBehaviorSlot27CN();
	virtual void bfmeBehaviorSlot28CN();
	virtual void bfmeBehaviorSlot29CN();
	virtual void bfmeBehaviorSlot30CN();
	virtual void bfmeBehaviorSlot31CN();
	virtual void bfmeBehaviorSlot32CN();
	virtual void bfmeBehaviorSlot33CN();
	virtual BfmeDoneInterfaceCN *bfmeDoneInterfaceCN();
};

struct BfmeDamageInfoCN
{
	unsigned char m_bfmeHeadCN[8];
	int m_bfmeSourceIDCN;
};

class BfmeBodyDamageSourceCN
{
public:
	virtual void bfmeBodySlot00CN();
	virtual void bfmeBodySlot01CN();
	virtual void bfmeBodySlot02CN();
	virtual void bfmeBodySlot03CN();
	virtual void bfmeBodySlot04CN();
	virtual void bfmeBodySlot05CN();
	virtual void bfmeBodySlot06CN();
	virtual void bfmeBodySlot07CN();
	virtual void bfmeBodySlot08CN();
	virtual void bfmeBodySlot09CN();
	virtual void bfmeBodySlot10CN();
	virtual void bfmeBodySlot11CN();
	virtual void bfmeBodySlot12CN();
	virtual void bfmeBodySlot13CN();
	virtual void bfmeBodySlot14CN();
	virtual BfmeDamageInfoCN *getLastDamageInfoCN();
};

class BfmeUpgradeSinkCN
{
public:
	virtual void bfmeUpgradeSlot00CN();
	virtual void bfmeUpgradeSlot01CN();
	virtual void bfmeUpgradeSlot02CN();
	virtual void bfmeUpgradeSlot03CN();
	virtual void bfmeUpgradeSlot04CN();
	virtual void bfmeUpgradeSlot05CN();
	virtual void bfmeUpgradeSlot06CN();
	virtual void bfmeUpgradeSlot07CN();
	virtual void bfmeUpgradeSlot08CN();
	virtual void bfmeUpgradeSlot09CN();
	virtual void bfmeUpgradeSlot10CN();
	virtual void bfmeUpgradeSlot11CN();
	virtual void bfmeUpgradeSlot12CN();
	virtual void bfmeUpgradeSlot13CN();
	virtual void bfmeUpgradeSlot14CN(BfmeUnitCN *unit);
};

class BfmeOwnerCN
{
public:
	unsigned char m_bfmeHeadCN[0x10];
	BfmeUnitCN *m_bfmeUnitCN;
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadCN[0x3c];
	unsigned int m_bfmeFrameCN;
	unsigned char m_bfmePad2CN[0x70];
	_STL::hash_map<int, BfmeUnitCN *> m_bfmeObjectHashCN;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

static __forceinline BfmeUnitCN *BfmeFindObjectByIDCN(int id)
{
	if (id == 0)
		return 0;

	_STL::hash_map<int, BfmeUnitCN *>::iterator it =
		TheBfmeGameLogic->m_bfmeObjectHashCN.find(id);
	if (it == TheBfmeGameLogic->m_bfmeObjectHashCN.end())
		return 0;

	return (*it).second;
}

extern void j_0001b94b(void);

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
};

class BFMEReportDamageSource
{
public:
	void report(Object *owner, int setting);
};

typedef void (BFMEReportDamageSource::*BFMEReportDamageSourceFunction)(Object *, int);

bool BfmeUnitCN::bfmeDoneCN()
{
	BfmeBehaviorModuleCN **module = m_bfmeBehaviorsCN;
	BfmeDoneInterfaceCN *done = 0;
	while (module != 0 && *module != 0)
	{
		BfmeBehaviorModuleInterfaceCN *interfaceCN =
			(BfmeBehaviorModuleInterfaceCN *)((unsigned char *)*module + 0xc);
		done = interfaceCN->bfmeDoneInterfaceCN();
		if (done != 0)
			break;
		++module;
	}

	BfmeDamageInfoCN *damageInfo = m_bfmeBodyCN->getLastDamageInfoCN();
	if (damageInfo != 0)
	{
		int sourceID = m_bfmeBodyCN->getLastDamageInfoCN()->m_bfmeSourceIDCN;
		BfmeUnitCN *source = BfmeFindObjectByIDCN(sourceID);
		if (source != 0)
		{
			union
			{
				void (*raw)(void);
				BFMEReportDamageSourceFunction member;
			} report;
			report.raw = j_0001b94b;
			(reinterpret_cast<BFMEReportDamageSource *>(source)->*report.member)((Object *)this, 1);
		}
	}

	if (done != 0)
	{
		if (m_bfmeContainedByCN != 0)
		{
			BfmeSubCN *sub = m_bfmeContainedByCN->m_bfmeSubCN;
			if (sub != 0)
			{
				BfmeUpgradeSinkCN *sink = sub->bfmeSlot26CN();
				if (sink != 0)
					sink->bfmeUpgradeSlot14CN(this);
			}
		}

		done->bfmeDoneSlotCN();
		return true;
	}

	((Object *)this)->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	return false;
}

class BfmeHostCN
{
public:
	int bfmeTickCN();
	void bfmeBeginCN(BfmeUnitCN *u);

	unsigned char m_bfmeHeadCN[0x1c];
	BfmeOwnerCN *m_bfmeOwnerCN;
	unsigned char m_bfmePadCN[8];
	unsigned int m_bfmeSecondCN;
	unsigned int m_bfmeFirstCN;
};

int BfmeHostCN::bfmeTickCN()
{
	BfmeUnitCN *u = m_bfmeOwnerCN->m_bfmeUnitCN;

	if (u == 0)
		return -2;

	bfmeBeginCN(u);

	if (m_bfmeFirstCN <= TheBfmeGameLogic->m_bfmeFrameCN)
	{
		BfmeSubCN *s = u->m_bfmeSubCN;

		if (s != 0)
			s->bfmeStopCN();

		m_bfmeFirstCN = 0xffffffff;
	}

	if (m_bfmeSecondCN <= TheBfmeGameLogic->m_bfmeFrameCN)
	{
		u->bfmeDoneCN();

		return -1;
	}

	return 0;
}
