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
};

class Rva002BCB60Owner
{
public:
	int choose(void *mode, int unused);
	void route(void *mode, Coord3D *position, int source);

	private:
	unsigned char m_unreconstructed000[8];
	Rva002BCB60Thing *m_thing;
	unsigned char m_unreconstructed00c[0x470];
	Coord3D m_goalPosition47c;
};

class Rva002BC260GoalOwner
{
public:
	void run(void *position, void *goalData, void *unused, void *source);
};

#pragma comment(linker, "/alternatename:?choose@Rva002BCB60Owner@@QAEHPAXH@Z=?j_00018e8a@@YAXXZ")
#pragma comment(linker, "/alternatename:?setHeight@Rva002BCB60Thing@@QAEXM@Z=?j_000281ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?run@Rva002BC260GoalOwner@@QAEXPAX000@Z=?j_0000795a@@YAXXZ")

#define g_Rva01075344 (*(float *)0x01075344)
#define g_Rva01075334 (*(float *)0x01075334)
#define g_Rva012F02D4 (*(int *)0x012F02D4)
#define g_Rva012F02D8 (*(int *)0x012F02D8)

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
