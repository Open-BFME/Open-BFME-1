// cl: /DNDEBUG /MD
//
// Address-derived recovery for the Giant Bird goal-routing body at retail
// RVA 0x002BCB60.  The selector call is the adjacent 0x002BC9C0 body; the
// two goal sinks and the height adjustment retain their retail ILT aliases.

struct Coord3D
{
	float x;
	float y;
	float z;
};


class Rva002BCB60Thing
{
public:
	void setHeight(float height);

	private:
	unsigned char m_unreconstructed000[0x40];

	public:
	float m_height40;
	unsigned char m_unreconstructed044[0x7c];
	float m_heightC0;
};

class Rva002BCB60QueryObject
{
	unsigned char m_unreconstructed000[0x24];
};

class Rva002BCB60AerialPathfinder
{
public:
	bool query(Rva002BCB60Thing *thing, Rva002BCB60QueryObject *queryObject,
		float range, void *mode);
	bool tryQuery(Rva002BCB60QueryObject *queryObject, float range,
		Coord3D *result);
};

class Rva002BCB60Owner
{
public:
	int choose(void *mode, int fullRange);
	unsigned char checkHeight();
	void route(void *mode, Coord3D *position, int source);

private:
	unsigned char m_unreconstructed000[8];
	Rva002BCB60Thing *m_thing;
	unsigned char m_unreconstructed00c[0x1c0];
	void *m_heightData1cc;
	unsigned char m_unreconstructed1d0[0x230];
	Rva002BCB60QueryObject m_queryObject400;
	unsigned char m_continue424;
	unsigned char m_unreconstructed425[0x43];
	float m_height468;
	unsigned char m_unreconstructed46c[0x0c];
	float m_goalRange478;
	Coord3D m_goalPosition47c;
};

class Rva002BC260GoalOwner
{
public:
	void run(void *position, void *goalData, void *unused, void *source);
};

#pragma comment(linker, "/alternatename:?query@Rva002BCB60AerialPathfinder@@QAE_NPAVRva002BCB60Thing@@PAVRva002BCB60QueryObject@@MPAX@Z=?j_0002fcd9@@YAXXZ")
#pragma comment(linker, "/alternatename:?tryQuery@Rva002BCB60AerialPathfinder@@QAE_NPAVRva002BCB60QueryObject@@MPAUCoord3D@@@Z=?j_0003e13a@@YAXXZ")
#pragma comment(linker, "/alternatename:?checkHeight@Rva002BCB60Owner@@QAEEXZ=?j_0004539f@@YAXXZ")
#pragma comment(linker, "/alternatename:?setHeight@Rva002BCB60Thing@@QAEXM@Z=?j_000281ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?run@Rva002BC260GoalOwner@@QAEXPAX000@Z=?j_0000795a@@YAXXZ")

#define g_Rva012EF1F8 (*(Rva002BCB60AerialPathfinder **)0x012EF1F8)
#define g_Rva0107533C (*(float *)0x0107533C)
#define g_Rva01075C74 (*(float *)0x01075C74)
#define g_Rva01088830 (*(float *)0x01088830)
#define g_Rva01075344 (*(float *)0x01075344)
#define g_Rva01075334 (*(float *)0x01075334)
#define g_Rva012F02D4 (*(int *)0x012F02D4)
#define g_Rva012F02D8 (*(int *)0x012F02D8)

// ?choose@Rva002BCB60Owner@@QAEHPAXH@Z
int Rva002BCB60Owner::choose(void *mode, int fullRange)
{
	Rva002BCB60Thing *thing = m_thing;
	if (thing == 0 || m_heightData1cc == 0)
		return 0;
	if (m_continue424 == 0)
		return 2;

	if ((unsigned char)fullRange != 0)
	{
		float range = thing->m_heightC0 + thing->m_heightC0 + m_height468;
		if (!g_Rva012EF1F8->query(thing, &m_queryObject400, range, mode))
			return 1;
	}
	else
	{
		float twiceHeight = m_height468 + m_height468;
		if (!g_Rva012EF1F8->query(thing, &m_queryObject400,
			twiceHeight
				- thing->m_heightC0 * g_Rva0107533C, mode))
			return 1;
		if (g_Rva012EF1F8->query(thing, &m_queryObject400,
			twiceHeight, mode))
		{
			// Continue to the height check below.
		}
		else
		{
			return 1;
		}
	}

	if (!checkHeight())
		return 0;

	// Preserve the retail x87 load of the current height before the offset.
	Coord3D result;
	if (!g_Rva012EF1F8->tryQuery(&m_queryObject400,
		(volatile float &)m_height468 + g_Rva01075C74, &result))
		return 0;
	if (result.z - g_Rva01088830 > thing->m_height40)
	{
		if (m_goalRange478 < thing->m_height40)
			return 2;
	}
	return 0;
}

// ?route@Rva002BCB60Owner@@QAEXPAXPAUCoord3D@@H@Z
void Rva002BCB60Owner::route(void *mode, Coord3D *position, int source)
{
	int state = choose(mode, 0);
	if (state == 0)
		return;

	Coord3D goal;
	if (position != 0)
		goal = *position;
	else
		goal = m_goalPosition47c;

	if (state == 1)
	{
		Rva002BCB60Thing *thing = m_thing;
		thing->setHeight(thing->m_height40 + g_Rva01075344);
		((Rva002BC260GoalOwner *)this)->run(&goal,
			&g_Rva012F02D8, 0, (void *)source);
	}
	else if (state == 2)
	{
		Rva002BCB60Thing *thing = m_thing;
		thing->setHeight(thing->m_height40 - g_Rva01075334);
		((Rva002BC260GoalOwner *)this)->run(&goal,
			&g_Rva012F02D4, 0, (void *)source);
	}
}
