// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink
// ?doTeamFollowSkirmishApproachPath@ScriptActions@@IAEXABVAsciiString@@0_N@Z
// BFME team follow action at retail 0x002F2BD0 (498 bytes).

typedef bool Bool;
typedef int Int;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &that);
	StringBase(const T *text);
	~StringBase(void);
	void releaseBuffer(void);

public:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &that)
		: StringBase<char>(*(const StringBase<char> *)&that) {}
	~AsciiString(void) {}

	const char *str(void) const
	{
		return m_data ? (const char *)((const char *)m_data + 8) : "";
	}

	void __cdecl format(AsciiString format, ...);
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &that);
	~BfmeStringArgBase(void);
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg(void);

private:
	char *m_text;
};

struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D(void) {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
};

class Object;

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

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_beforePosition[0x34];
	Coord3D m_position;
	unsigned char m_afterPosition[0x24];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const Coord3D *getPosition(void) const { return &m_position; }
};

class Waypoint;

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance(void)
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done(void) const { return m_cur == 0; }
	OBJCLASS *cur(void) const { return m_cur; }
};

class AIGroup
{
public:
	void groupFollowWaypointPathAsTeamClearFormation(const Waypoint *way,
		CommandSourceType commandSource);
	void groupFollowWaypointPath(const Waypoint *way,
		CommandSourceType commandSource);
};

class Team
{
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

public:
	void getTeamAsAIGroup(AIGroup *group);

	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class AI
{
public:
	AIGroup *createGroup(void);
};

class Player
{
	unsigned char m_pad[0x224];

public:
	Int getMpStartIndex(void) const
	{
		return *(const Int *)((const unsigned char *)this + 0x224);
	}
};

class CurrentPlayer
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void checkBridges(Object *firstUnit, const Waypoint *way);
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
	virtual Player *getSkirmishEnemyPlayer(void) = 0;
	virtual CurrentPlayer *getCurrentPlayer(void) = 0;
};

class Waypoint
{
public:
	unsigned char m_pad[0x0c];
	Coord3D m_location;
};

class TerrainLogic
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *position,
		BfmeAsciiStringArg label) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;
extern float g_bfmeDefaultBU;

class ScriptActions
{
protected:
	void doTeamFollowSkirmishApproachPath(const AsciiString &teamName,
		const AsciiString &waypointPathLabel, Bool asTeam);
};

void ScriptActions::doTeamFollowSkirmishApproachPath(
	const AsciiString &teamName, const AsciiString &waypointPathLabel,
	Bool asTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;

	theTeam->getTeamAsAIGroup(theGroup);
	Int count = 0;
	Coord3D pos;
	pos.x = pos.y = pos.z = 0;

	Object *firstUnit = 0;
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z;
		count++;
		if (firstUnit == 0)
			firstUnit = obj;
	}

	if (count == 0)
		return;

	pos.x /= count;
	pos.y /= count;
	pos.z /= count;

	Player *enemyPlayer = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemyPlayer == 0)
		return;

	Int mpNdx = enemyPlayer->getMpStartIndex() + 1;
	AsciiString pathLabel;
	pathLabel.format("%s%d", waypointPathLabel.str(), mpNdx);
	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(&pos, pathLabel);
	if (!way)
		return;

	CurrentPlayer *aiPlayer = TheScriptEngine->getCurrentPlayer();
	if (aiPlayer && firstUnit)
		aiPlayer->checkBridges(firstUnit, way);

	if (asTeam)
		theGroup->groupFollowWaypointPathAsTeamClearFormation(way,
			CMD_FROM_SCRIPT);
	else
		theGroup->groupFollowWaypointPath(way, CMD_FROM_SCRIPT);
}
