// ?link@BfmeLinkedObj@@QAEXPAV1@H@Z
// partial score=0.86 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /Ireference/shims/stringinline /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?link@BfmeLinkedObj@@QAEXPAV1@H@Z present-unmatched
//
// The BFME body behind the existing BfmeLinkedObj::link pin.  The caller in
// BfmeConv831 proves the class and method spelling.  The second caller and
// the Zero Hour twin establish the asset-transfer role; the extra BFME
// status, influence, upgrade, and map-counter work is recovered from the
// retail body itself.

#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <bitset>
#include <list>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Player;
class Team;
class Object;

// The two list operations are the existing retail callees printed by
// tools/callees.py.  These aliases keep their direct ILT calls while the
// local declarations retain the useful member ABIs.
extern void j_00001140();
extern void j_000022bb();
extern void j_00014b91();
extern void j_0001df16();
extern void j_00027d6d();
extern void j_000307e7();
extern void j_00040327();
extern void j_00041894();

extern unsigned char g_bfmeTableDH[];

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2,
	UnsignedInt count);
#pragma intrinsic(memcmp)

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID,
	UPGRADE_STATUS_IN_PRODUCTION,
	UPGRADE_STATUS_COMPLETE
};

class Upgrade;

class UpgradeTemplate
{
public:
	unsigned char m_unmodelled_000[8];
	AsciiString m_name;
	unsigned char m_unmodelled_00c[0x14];
	UnsignedInt m_upgradeMask;
};

class Upgrade
{
};

class Money
{
public:
	UnsignedInt countMoney() const { return m_money; }
	UnsignedInt withdraw(UnsignedInt amount, Bool playSound = true);
	void deposit(UnsignedInt amount, Bool playSound = true);

private:
	unsigned char m_unmodelled_000[4];
	UnsignedInt m_money;
	Int m_playerIndex;
};

#pragma comment(linker, "/alternatename:?withdraw@Money@@QAEII_N@Z=?j_00041894@@YAXXZ")
#pragma comment(linker, "/alternatename:?deposit@Money@@QAEXI_N@Z=?j_00027d6d@@YAXXZ")

template <int NUM_BITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<NUM_BITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0xc4];
	UnsignedInt m_kindOfCC;
	UnsignedInt m_kindOfD0;
	UnsignedInt m_flagsD4;
	UnsignedInt m_flagsD8;
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value && value->m_nextOverride)
			value = (const T *)value->m_nextOverride->getFinalOverride();
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

class BfmeObjectVtbl
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void setTeam(Team *team) = 0;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	void bfmeTransferPowerInfluence(Player *oldPlayer, Player *newPlayer);
	void setStatus(const ObjectStatusMaskType &mask, Bool enabled);

	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}

	unsigned char m_unmodelled_070[0x24];
	UnsignedInt m_status94;
	unsigned char m_unmodelled_098[0x16c];
	void *m_ai;
	unsigned char m_unmodelled_208[0x0c];
	Object *m_containedBy;
};

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeTransferPowerInfluence@Object@@QAEXPAVPlayer@@0@Z=?j_00014b91@@YAXXZ")
#pragma comment(linker, "/alternatename:?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z=?j_000307e7@@YAXXZ")

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class Team
{
public:
	Team *_bfme_nextInInstanceList();

	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_head,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}

private:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

#pragma comment(linker, "/alternatename:?_bfme_nextInInstanceList@Team@@QAEPAV1@XZ=?j_00022a70@@YAXXZ")

class BfmeTeamPrototype
{
public:
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;
};

typedef _STL::list<BfmeTeamPrototype *> BfmePlayerTeamList;

class BfmePlayerTeamFields
{
public:
	unsigned char m_unmodelled_000[0x288];
	BfmePlayerTeamList m_playerTeamPrototypes;
};

class BfmePlayerMapState
{
public:
	Int m_value00;
	Int m_value04;
	Int m_value08;
	Int m_field;
	Int m_value10;
	Int m_value14;
};

class BfmePlayerTemplate
{
public:
	unsigned char m_unmodelled_000[0x118];
	Bool m_hasFactionFlag;
};

class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *upgradeTemplate,
		UpgradeStatusType status);

	Money *getMoney() { return &m_money; }
	const Money *getMoney() const { return &m_money; }

	unsigned char m_unmodelled_000[4];
	BfmePlayerTemplate *m_playerTemplate;
	unsigned char m_unmodelled_008[0x28];
	BfmePlayerMapState m_mapState;
	Money m_money;
	unsigned char m_unmodelled_054[0x38];
	UnsignedInt m_upgradeMask[6];
	unsigned char m_unmodelled_0a4[0x18c];
	Team *m_defaultTeam;
	unsigned char m_unmodelled_234[0x54];
	BfmePlayerTeamList m_playerTeamPrototypes;
};

#pragma comment(linker, "/alternatename:?addUpgrade@Player@@QAEPAVUpgrade@@PBVUpgradeTemplate@@W4UpgradeStatusType@@@Z=?j_00040327@@YAXXZ")

struct BfmeNodeND;

class BfmeThingND
{
public:
	BfmeNodeND *bfmeFindND(const UnsignedInt *mask);
};

struct BfmeNodeND
{
	unsigned char m_unmodelled_000[8];
	AsciiString m_name;
	unsigned char m_unmodelled_00c[0x14];
	UnsignedInt m_bit;
};

// The first nine upgrade tests are inlined in retail.  The last two use the
// existing StringBase<char>::compare callee, so keep this tiny view local to
// the inlined branch rather than routing every name through that callee.
class BfmeTransferStringView
{
public:
	int compare(const char *text, Int length) const
	{
		Int thisLength = m_text ?
			*(const unsigned short *)(m_text + 4) : 0;
		const char *data = m_text ? m_text + 8 :
			(const char *)0x0107388B;
		Int count = thisLength < length ? thisLength : length;
		int result = memcmp(data, text, count);
		if (result != 0)
			return result;
		return thisLength - length;
	}

	int compare(const char *text) const;

	char *m_text;
};

#pragma comment(linker, "/alternatename:?compare@BfmeTransferStringView@@QBEHPBD@Z=?compare@?$StringBase@D@@QBEHPBD@Z")

#define TheUpgradeCenter (*(BfmeThingND **)0x012EF188)

#pragma comment(linker, "/alternatename:?bfmeFindND@BfmeThingND@@QAEPAUBfmeNodeND@@PBI@Z=?j_0001df16@@YAXXZ")

class UpgradeMaskType
{
public:
	UnsignedInt m_bits[6];

	int checksum() const
	{
		int total = 0;
		const unsigned char *first = (const unsigned char *)this;
		const unsigned char *last = first + sizeof(m_bits);
		while (first < last)
		{
			total += g_bfmeTableDH[*first];
			++first;
		}
		return total;
	}

	void clear(UnsignedInt bit)
	{
		m_bits[bit >> 5] &= ~(1u << (bit & 0x1f));
	}
};

class BfmeLinkedObj
{
public:
	void link(BfmeLinkedObj *that, Int transferFlag);
};

void BfmeLinkedObj::link(BfmeLinkedObj *that, Int transferFlag)
{
	Team *defaultTeam = ((Player *)this)->m_defaultTeam;
	if (!defaultTeam)
		return;

	_STL::list<Object *> objectsToComplete;
	_STL::list<Object *> objectsWithInfluence;

	BfmePlayerTeamFields *sourceTeams = (BfmePlayerTeamFields *)that;
	for (BfmePlayerTeamList::iterator it =
		sourceTeams->m_playerTeamPrototypes.begin();
		it != sourceTeams->m_playerTeamPrototypes.end(); ++it)
	{
		BfmePlayerTeamList::value_type prototype = *it;
		Team *team = prototype->m_teamInstanceList;
		for (;;)
		{
			if (!team)
				break;

			BfmeDlinkIterator<Object> objects = team->iterate_TeamMemberList();
			while (!objects.done())
			{
				Object *object = objects.cur();
				if (object)
				{
					const ThingTemplate *templateObject = object->getTemplate();
					if (!(templateObject->m_kindOfD0 & 0x01000000))
					{
						const ThingTemplate *templateAgain = object->getTemplate();
						if (!(templateAgain->m_flagsD8 & 0x20))
						{
							const ThingTemplate *templateThird = object->getTemplate();
							if (!(templateThird->m_kindOfCC & 0x00008000))
							{
				if (object->m_status94 & 0x20000000)
					objectsWithInfluence.push_back(object);
				else
					objectsToComplete.push_back(object);
							}
						}
					}
				}
				objects.advance();
			}
			team = team->_bfme_nextInInstanceList();
			if (!team)
				break;
		}
	}

	for (_STL::list<Object *>::iterator it =
		objectsToComplete.begin(); it != objectsToComplete.end(); ++it)
	{
		Object *object = *it;
		if (!object || (object->m_status94 & 0x20))
			continue;

		object->bfmeTransferPowerInfluence((Player *)that, (Player *)this);
		const unsigned char doTransfer = (unsigned char)transferFlag;
		if (doTransfer)
		{
			ObjectStatusMaskType status(ObjectStatusMaskType::kInit, 15);
			object->setStatus(status, true);

			Object *containedBy = object->m_containedBy;
			if (containedBy)
			{
				const ThingTemplate *containedTemplate = containedBy->getTemplate();
				if (containedTemplate->m_flagsD4 & 0x1000)
					containedBy->setTeam(defaultTeam);
				else
					object->setTeam(defaultTeam);
			}
			else
			{
				object->setTeam(defaultTeam);
			}
		}
	}

	for (_STL::list<Object *>::iterator it =
		objectsWithInfluence.begin(); it != objectsWithInfluence.end(); ++it)
	{
		Object *object = *it;
		if (object && !(object->m_status94 & 0x20))
			object->slot18();
	}

	UpgradeMaskType upgrades;
	for (Int i = 0; i < 6; ++i)
		upgrades.m_bits[i] = ((Player *)that)->m_upgradeMask[i];

	while (upgrades.checksum() > 0)
	{
		BfmeNodeND *node =
			TheUpgradeCenter->bfmeFindND(upgrades.m_bits);
		if (!node)
			break;

		BfmeTransferStringView *name =
			(BfmeTransferStringView *)&node->m_name;
		Bool matches =
			name->compare("Upgrade_RohanDualEconomyChoice", 0x1e) == 0 ||
			name->compare("Upgrade_IsengardDualEconomyChoice", 0x21) == 0 ||
			name->compare("Upgrade_MordorDualEconomyChoice", 0x1f) == 0 ||
			name->compare("Upgrade_EvilDualEconomyChoice", 0x1d) == 0 ||
			name->compare("Upgrade_GondorFaction", 0x15) == 0 ||
			name->compare("Upgrade_IsengardFaction", 0x17) == 0 ||
			name->compare("Upgrade_MordorFaction", 0x15) == 0 ||
			name->compare("Upgrade_RohanFaction", 0x14) == 0 ||
			name->compare("Upgrade_GandalfWhite", 0x14) == 0 ||
			name->compare("Upgrade_Anduril") == 0 &&
				name->compare("Upgrade_ElvenGift") == 0;

		if (matches)
		{
			((Player *)this)->addUpgrade((const UpgradeTemplate *)node,
				UPGRADE_STATUS_COMPLETE);
			upgrades.clear(node->m_bit);
		}
	}

	UnsignedInt allMoney = ((Player *)that)->getMoney()->countMoney();
	((Player *)that)->getMoney()->withdraw(allMoney, true);
	((Player *)this)->getMoney()->deposit(allMoney, true);

	BfmePlayerMapState *sourceMap = &((Player *)that)->m_mapState;
	BfmePlayerMapState *destinationMap = &((Player *)this)->m_mapState;
	Int value10 = sourceMap->m_value10;
	Int value14 = sourceMap->m_value14;
	if (((Player *)that)->m_playerTemplate->m_hasFactionFlag)
		++value14;
	++value10;
	destinationMap->m_value10 += value10;
	destinationMap->m_value14 += value14;
}
