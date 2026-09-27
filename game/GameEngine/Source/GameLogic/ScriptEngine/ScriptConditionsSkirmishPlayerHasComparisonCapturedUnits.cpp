// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define BFME_STLP_NODE_ALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/Player.h"

typedef bool Bool;
typedef int Int;

class Parameter
{
public:
	Int getInt() const { return *(const Int *)((const char *)this + 0x08); }
	unsigned char m_unmodelled[0x1c];
};

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *);
};
extern ScriptEngine *TheScriptEngine;

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
};
extern PlayerList *ThePlayerList;

struct BfmePlayerTeamFields
{
	unsigned char m_unreconstructed_000[0x288];
	Player::PlayerTeamList m_playerTeamPrototypes;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class BfmePlayerObjectDlinkObject;

class BfmePlayerObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmePlayerObjectVbptrCarrier : public virtual BfmePlayerObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmePlayerObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class BfmePlayerObjectDlinkBase
{
public:
	BfmePlayerObjectDlinkObject *dlink_next_TeamMemberList() const;
};

class BfmePlayerObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class BfmePlayerObjectDlinkObject : public BfmePlayerObjectVtbl,
	public BfmePlayerObjectDlinkBase, public BfmePlayerObjectDlinkPad,
	public BfmePlayerObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

class BfmeCapturedObjectView
{
public:
	unsigned char m_unmodelled_000[0x344];
	unsigned char m_privateStatus;

	Bool isCaptured() const { return (m_privateStatus & 4) != 0; }
};

template <class ObjectType> class BfmePlayerDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmePlayerDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	bool done() const { return m_cur == 0; }
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

class BfmePlayerTeamView
{
public:
	unsigned char m_unmodelled_000[0x0c];
	BfmePlayerObjectDlinkObject *m_head;

	BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> iterate_TeamMemberList() const
	{
		return BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>(m_head,
			BfmePlayerObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	unsigned char m_unmodelled_000[0x274];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *head) : m_cur(head) { }

	bool done() const { return m_cur == 0; }
	BfmePlayerTeamView *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (BfmePlayerTeamView *)
				((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

private:
	BfmePlayerTeamView *m_cur;
	int m_unmodelled;
};

class ScriptConditions
{
protected:
	Bool evaluateSkirmishPlayerHasComparisonCapturedUnits(Parameter *, Parameter *, Parameter *);
};

// ?evaluateSkirmishPlayerHasComparisonCapturedUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateSkirmishPlayerHasComparisonCapturedUnits(
	Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm)
{
	Int numCapturedUnits = 0;
	Player::PlayerTeamList::iterator it;
	PlayerMaskType playerMask =
		TheScriptEngine->unidentified_0034DB40(pSkirmishPlayerParm);
	if (playerMask)
	{
		while (playerMask)
		{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (player)
		{
			numCapturedUnits = 0;
			BfmePlayerTeamFields *teamFields = (BfmePlayerTeamFields *)player;
			for (it = teamFields->m_playerTeamPrototypes.begin();
				it != teamFields->m_playerTeamPrototypes.end(); ++it)
			{
				for (BfmePlayerTeamInstanceIterator teams(
						((BfmePlayerTeamPrototypeInstances *)(*it))->m_teamInstanceList);
					!teams.done(); teams.advance())
				{
					BfmePlayerTeamView *team = teams.cur();
					if (!team)
						continue;

					for (BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> objects =
							team->iterate_TeamMemberList();
						!objects.done(); objects.advance())
					{
						BfmePlayerObjectDlinkObject *object = objects.cur();
						if (!object)
							continue;

						if (((BfmeCapturedObjectView *)object)->isCaptured())
							++numCapturedUnits;
					}
				}
			}

			Bool comparison = false;
			switch (pComparisonParm->getInt())
			{
			case 0: comparison = numCapturedUnits < pCountParm->getInt(); break;
			case 1: comparison = numCapturedUnits <= pCountParm->getInt(); break;
			case 2: comparison = numCapturedUnits == pCountParm->getInt(); break;
			case 3: comparison = numCapturedUnits >= pCountParm->getInt(); break;
			case 4: comparison = numCapturedUnits > pCountParm->getInt(); break;
			case 5: comparison = numCapturedUnits != pCountParm->getInt(); break;
			}
			if (comparison)
				return TRUE;
		}
	}
	}

	return FALSE;
}

