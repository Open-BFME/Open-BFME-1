// ??0Rva003E5A50Info@@QAE@PAVPathfinder@@PAVObject@@H@Z
// partial score=0.96 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x003E5A50: the constructor of a BFME pathfind query payload.
//
// __thiscall with three stack arguments (ret 0xC): the pathfinder, the object
// and an integer that seeds the goal descriptor.  Like TightenPathStruct at
// 0x003E1720 it stores the pair, clears its scratch fields and finishes by
// asking the pathfinder for the object's radius and centre flag through
// Pathfinder::bfmeQuery -- BFME's out-of-line replacement for Zero Hour's
// inlined getRadiusAndCenter(obj, radius, center).
//
// Layout recovered from the stores: pathfinder 0x00, obj 0x04, scratch ints
// 0x08/0x0C/0x10, the bfmeQuery outputs 0x14 (radius) and 0x18 (centre), a
// second flag 0x19, an int 0x1C that ends up holding 12, an int 0x20, the
// current goal descriptor 0x24, an int 0x30, three bools 0x34-0x36, an int
// 0x38 and the requested goal descriptor at 0x44 followed by an int at 0x50.
//
// The two controlling-player lookups are an inlined accessor: a NULL team
// yields NULL, a team with no BIA sub-object yields the team pointer itself
// (the `je` path leaves the outer pointer in eax) and otherwise the sub-object
// is asked.  The first lookup reads the player's 0x444, the second its 0x4CC.
//
// No /EHsc: retail registers no handler for the body.

class Object;
class Player;
class Pathfinder;

class BfmeSubBIA
{
public:
	int bfmeAskBIA();
};

class Team
{
public:
	int m_field00;
	BfmeSubBIA *m_sub;
};

class Object
{
public:
	bool bfmeIsComputerControlled() const;

	int m_field00;
	Team *m_team;
};

class Player
{
public:
	char m_pad00[0x444];
	int m_field444;
	char m_pad448[0x4cc - 0x448];
	bool m_field4cc;
};

class Pathfinder
{
public:
	void bfmeQuery( Object *obj, int *radius, int *center );
};

static Player *controllingPlayer( Object *obj )
{
	Team *team = obj->m_team;

	if (team == 0)
		return 0;

	if (team->m_sub == 0)
		return (Player *)team;

	return (Player *)team->m_sub->bfmeAskBIA();
}

struct Rva003E5A50Goal
{
	int m_value;
	bool m_flag;
	bool m_ai;
	int m_level;
};

class Rva003E5A50Info
{
public:
	Rva003E5A50Info( Pathfinder *pathfinder, Object *obj, int value );

	Pathfinder *m_pathfinder;		// 0x00
	Object *m_obj;					// 0x04
	int m_field08;					// 0x08
	int m_field0C;					// 0x0C
	int m_field10;					// 0x10
	int m_radius;					// 0x14
	bool m_center;					// 0x18
	bool m_field19;					// 0x19
	int m_field1C;					// 0x1C
	int m_field20;					// 0x20
	Rva003E5A50Goal m_cur;			// 0x24
	int m_field30;					// 0x30
	bool m_field34;					// 0x34
	bool m_field35;					// 0x35
	bool m_field36;					// 0x36
	int m_field38;					// 0x38
	int m_field3C;					// 0x3C
	int m_field40;					// 0x40
	Rva003E5A50Goal m_goal;			// 0x44
	int m_field50;					// 0x50
};

Rva003E5A50Info::Rva003E5A50Info( Pathfinder *pathfinder, Object *obj, int value )
{
	m_pathfinder = pathfinder;
	m_obj = obj;

	m_field08 = 0;
	m_field0C = 0;
	m_field10 = 0;
	m_radius = 0;
	m_center = false;
	m_field19 = false;
	m_field1C = 0;
	m_field20 = 0;

	m_cur.m_value = 0;
	m_cur.m_flag = false;
	m_cur.m_ai = false;
	m_cur.m_level = -1;

	m_field30 = 0;
	m_field35 = false;
	m_field36 = false;
	m_field34 = false;
	m_field38 = 0;

	int level = controllingPlayer( obj )->m_field444;
	bool skill = controllingPlayer( obj )->m_field4cc;

	m_goal.m_value = value;
	m_goal.m_ai = obj->bfmeIsComputerControlled();
	m_goal.m_flag = (skill == false);
	m_goal.m_level = level - 1;

	m_cur = m_goal;

	m_field50 = 0;
	m_field19 = false;
	m_field1C = 12;

	m_pathfinder->bfmeQuery( m_obj, &m_radius, (int *)&m_center );
}
