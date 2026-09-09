// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define BFME_STLP_NODE_ALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/Player.h"

class TeamPrototype;
class Object;
class BehaviorModule;

struct BfmePlayerScienceFields
{
	unsigned char m_unreconstructed_000[0x234];
	ScienceVec m_sciences;
	ScienceVec m_sciencesDisabled;
	ScienceVec m_sciencesHidden;
};

struct BfmePlayerIndexField
{
	unsigned char m_unreconstructed_000[0x24];
	Int m_playerIndex;
};

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

class BfmeBehaviorModuleSpecialPowerShim
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot0c() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot18() = 0;
	virtual class BfmeSpecialPowerModuleShim *getSpecialPower() = 0;
};

class BfmeSpecialPowerModuleShim
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot0c() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot18() = 0;
	virtual ScienceType getRequiredScience() const = 0;
	virtual void onSpecialPowerCreation() = 0;
	virtual void setReadyFrame(UnsignedInt frame) = 0;
	virtual void bfmePauseCountdown() = 0;
	virtual void bfmeDoSpecialPower() = 0;
	virtual void bfmeDoSpecialPowerAtObject() = 0;
	virtual void bfmeDoSpecialPowerAtLocation() = 0;
	virtual void bfmeDoSpecialPowerUsingWaypoints() = 0;
	virtual void bfmeMarkSpecialPowerTriggered() = 0;
	virtual void startPowerRecharge() = 0;
};

struct BfmeObjectBehaviorsField
{
	unsigned char m_unreconstructed_000[0x1f0];
	void **m_behaviors;
};

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame();

	unsigned char m_unreconstructed_000[0x3c];
	UnsignedInt m_frame;
};

class ControlBar
{
public:
	void markUIDirty()
	{
		m_UIDirty = 1;
	}

private:
	unsigned char m_unreconstructed_000[0x24];
	unsigned char m_UIDirty;
};

class ScriptEngine
{
public:
#define BFME_SCRIPT_SLOT(n) virtual void slot##n();
	BFME_SCRIPT_SLOT(00) BFME_SCRIPT_SLOT(01) BFME_SCRIPT_SLOT(02)
	BFME_SCRIPT_SLOT(03) BFME_SCRIPT_SLOT(04) BFME_SCRIPT_SLOT(05)
	BFME_SCRIPT_SLOT(06) BFME_SCRIPT_SLOT(07) BFME_SCRIPT_SLOT(08)
	BFME_SCRIPT_SLOT(09) BFME_SCRIPT_SLOT(10) BFME_SCRIPT_SLOT(11)
	BFME_SCRIPT_SLOT(12) BFME_SCRIPT_SLOT(13) BFME_SCRIPT_SLOT(14)
	BFME_SCRIPT_SLOT(15) BFME_SCRIPT_SLOT(16) BFME_SCRIPT_SLOT(17)
	BFME_SCRIPT_SLOT(18) BFME_SCRIPT_SLOT(19) BFME_SCRIPT_SLOT(20)
	BFME_SCRIPT_SLOT(21) BFME_SCRIPT_SLOT(22) BFME_SCRIPT_SLOT(23)
	BFME_SCRIPT_SLOT(24) BFME_SCRIPT_SLOT(25) BFME_SCRIPT_SLOT(26)
	BFME_SCRIPT_SLOT(27) BFME_SCRIPT_SLOT(28) BFME_SCRIPT_SLOT(29)
	BFME_SCRIPT_SLOT(30) BFME_SCRIPT_SLOT(31) BFME_SCRIPT_SLOT(32)
	BFME_SCRIPT_SLOT(33) BFME_SCRIPT_SLOT(34) BFME_SCRIPT_SLOT(35)
	BFME_SCRIPT_SLOT(36) BFME_SCRIPT_SLOT(37) BFME_SCRIPT_SLOT(38)
#undef BFME_SCRIPT_SLOT
	virtual void notifyOfAcquiredScience(Int playerIndex, ScienceType science);
};

extern GameLogicPortraitShim *TheBfmeGameLogic;
extern ControlBar *TheControlBar;
extern ScriptEngine *TheScriptEngine;

Bool Player::addScience(ScienceType science)
{
	register ScienceType scienceInRegister = science;
	const BfmePlayerScienceFields *scienceFields =
		(const BfmePlayerScienceFields *)this;
	ScienceVec::const_iterator scienceEnd = scienceFields->m_sciences.end();
	if (std::find(scienceFields->m_sciences.begin(), scienceEnd, scienceInRegister) != scienceEnd)
		return false;

	((BfmePlayerScienceFields *)scienceFields)->m_sciences.push_back(science);

	BfmePlayerTeamFields *teamFields = (BfmePlayerTeamFields *)this;
	for (Player::PlayerTeamList::iterator it = teamFields->m_playerTeamPrototypes.begin();
		it != teamFields->m_playerTeamPrototypes.end(); ++it)
	{
		BfmePlayerTeamInstanceIterator teams =
			BfmePlayerTeamInstanceIterator(
				((BfmePlayerTeamPrototypeInstances *)(*it))->m_teamInstanceList);
		while (!teams.done())
		{
			BfmePlayerTeamView *team = teams.cur();
			if (team)
			{
				BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> objects =
					team->iterate_TeamMemberList();
				while (!objects.done())
				{
					BfmePlayerObjectDlinkObject *object = objects.cur();
					if (object)
					{
						void **behaviors =
							((BfmeObjectBehaviorsField *)object)->m_behaviors;
						for (void **m = behaviors; *m; ++m)
						{
							BfmeBehaviorModuleSpecialPowerShim *module =
								(BfmeBehaviorModuleSpecialPowerShim *)((char *)*m + 0xc);
							BfmeSpecialPowerModuleShim *sp = module->getSpecialPower();
							if (!sp)
								continue;

							if (sp->getRequiredScience() == science)
							{
								sp->onSpecialPowerCreation();
								if (TheBfmeGameLogic->isInMultiplayerOrSkirmishGame())
									sp->setReadyFrame(TheBfmeGameLogic->m_frame);
								else
									sp->startPowerRecharge();
							}
						}
					}
					objects.advance();
				}
			}
			teams.advance();
		}

		TheControlBar->markUIDirty();
	}

	if (TheScriptEngine)
	{
		BfmePlayerIndexField *playerFields = (BfmePlayerIndexField *)this;
		TheScriptEngine->notifyOfAcquiredScience(playerFields->m_playerIndex, science);
	}
	return true;
}
