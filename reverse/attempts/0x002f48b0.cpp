// ?d_002f48b0@@YAXXZ
// partial score=0.99 date=2026-09-18
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/objectdlink /ICode/Libraries/Source/WWVegas/WWLib

typedef bool Bool;
typedef unsigned short UnsignedShort;

struct Coord3D
{
	float x;
	float y;
	float z;
};

#include "ascii_string.h"

class SpecialPowerTemplate;

class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void doSpecialPowerAtLocation(const Coord3D *, int);
};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};
class BfmeObjectVtbl { public: virtual void slot00(); };

class Object;
class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};
class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *) const;
	unsigned char m_tail[0x40];
};

struct BfmePlayerTeamListNode
{
	BfmePlayerTeamListNode *m_next;
	BfmePlayerTeamListNode *m_prev;
	class BfmePlayerTeamPrototypeInstances *m_prototype;
};

class BfmePlayerTeamPrototypeInstances;
class BfmePlayerTeamInstanceLink;

class BfmePlayerTeamInstanceLink
{
public:
	BfmePlayerTeamInstanceLink *_bfme_nextInInstanceList();
};

class Player
{
public:
	unsigned char m_pad[0x288];
	BfmePlayerTeamListNode *m_teamList;
};

class BfmePlayerObjectDlinkObject;
class BfmePlayerTeamView;

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *cur) : m_cur(cur) {}

	bool done() const { return m_cur == 0; }
	BfmePlayerTeamView *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = (BfmePlayerTeamView *)
				((BfmePlayerTeamInstanceLink *)m_cur)
					->_bfme_nextInInstanceList();
	}

private:
	BfmePlayerTeamView *m_cur;
	int m_unused;
};

class BfmePlayerTeamPrototypeInstances
{
public:
	unsigned char m_pad[0x274];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmePlayerTeamListField
{
public:
	unsigned char m_pad[0x288];
	BfmePlayerTeamListNode *m_head;
};

class BfmePlayerTeamView
{
public:
	unsigned char m_pad[0x0c];
	Object *m_head;
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)() const;

template<class ObjectType>
class BfmePlayerDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmePlayerDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) {}

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

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &, Bool *);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &);
};

extern void *TheScriptEngine;
extern PlayerList *ThePlayerList;

class BfmeFireSpecialPowerHelper
{
public:
	Bool fire(const AsciiString &, const SpecialPowerTemplate *, const Coord3D *);
};

Bool BfmeFireSpecialPowerHelper::fire(const AsciiString &player,
	const SpecialPowerTemplate *power, const Coord3D *location)
{
	UnsignedShort playerMask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player, 0);
	while (playerMask != 0)
	{
		Player *playerObject = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (playerObject == 0)
			return false;

		BfmePlayerTeamListField *teams =
			(BfmePlayerTeamListField *)playerObject;
		for (BfmePlayerTeamListNode *teamNode = teams->m_head->m_next;
			teamNode != teams->m_head; teamNode = teamNode->m_next)
		{
			BfmePlayerTeamInstanceIterator iter(
				teamNode->m_prototype->m_teamInstanceList);
			for (; !iter.done(); iter.advance())
			{
				BfmePlayerTeamView *team = iter.cur();
				if (team == 0)
					continue;
				BfmeGetNextTeamMemberFunc getNext =
					BfmeObjectDlinkBase::dlink_next_TeamMemberList;
				Object *object = team->m_head;
				while (object != 0)
				{
					SpecialPowerModuleInterface *module =
						object->getSpecialPowerModule(power);
					if (module != 0)
					{
						module->doSpecialPowerAtLocation(location, 0x40000);
						return true;
					}
					object = (object->*getNext)();
				}
			}
		}
	}
	return false;
}
