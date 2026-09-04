// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// readable body of the BFME skirmish approach-path team action at retail
// 0x002F2E40 (461 bytes).

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

struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D &operator+=(const Coord3D &that)
	{
		x += that.x;
		y += that.y;
		z += that.z;
		return *this;
	}
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
	Coord3D *getPosition(void) { return &m_position; }
	unsigned char m_tail[0x40];
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

class AIGroup;

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
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
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
	Int m_mpStartIndex;

public:
	Int getMpStartIndex(void) const { return m_mpStartIndex; }
};

class ScriptEngine
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual Team *getTeamNamed(AsciiString name, Bool unused);
	virtual Player *getSkirmishEnemyPlayer(void);
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
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *position,
		AsciiString pathLabel);
};

struct Rva0015A190Packet
{
	void *m_first;
	unsigned char m_flag;
	union
	{
		void *m_objA;
		float m_scratchZ;
	};
	void *m_objB;
};

class Rva0015A190Owner
{
public:
	void applyPacket(Rva0015A190Packet *packet, Int command);
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamMoveToSkirmishApproachPath(const AsciiString &teamName,
		const AsciiString &waypointPathLabel);
};

void ScriptActions::doTeamMoveToSkirmishApproachPath(
	const AsciiString &teamName, const AsciiString &waypointPathLabel)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;

	theTeam->getTeamAsAIGroup(theGroup);
	Int count = 0;
	Coord3D position;
	position.x = position.y = position.z = 0;
	Rva0015A190Packet packet;

	DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
	if (!iter.done())
	{
		do
		{
			Object *object = iter.cur();
			const Coord3D *objectPosition =
				((const Object *)object)->getPosition();
			float objectX = objectPosition->x;
			float objectY = objectPosition->y;
			packet.m_scratchZ = objectPosition->z;
			position.x += objectX;
			position.y += objectY;
			position.z += packet.m_scratchZ;
			++count;
			iter.advance();
		}
		while (!iter.done());
	}

	if (count == 0)
		return;

	position.x /= count;
	position.y /= count;
	position.z /= count;

	Player *enemyPlayer = TheScriptEngine->getSkirmishEnemyPlayer();
	if (!enemyPlayer)
		return;

	Int multiplayerIndex = enemyPlayer->getMpStartIndex() + 1;
	AsciiString pathLabel;
	pathLabel.format("%s%d", waypointPathLabel.str(), multiplayerIndex);

	Waypoint *waypoint = TheTerrainLogic->getClosestWaypointOnPath(
		&position, pathLabel);
	if (!waypoint)
		return;

	packet.m_first = (void *)&waypoint->m_location;
	packet.m_flag = 0;
	packet.m_objA = 0;
	packet.m_objB = 0;
	((Rva0015A190Owner *)theGroup)->applyPacket(&packet, 1);
}
