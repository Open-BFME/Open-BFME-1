// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME goal setup body at 0x002BC260.

#pragma comment(linker, "/alternatename:?initialize@Rva002BC260Global@@QAEXPAX00000@Z=?j_0000a795@@YAXXZ")
#pragma comment(linker, "/alternatename:?finalize@Rva002BC260Goal@@QAEXXZ=?j_00049ae9@@YAXXZ")

class Rva002BC260Global
{
public:
	void initialize(void *a, void *b, void *c, void *d, void *e, void *f);
};

class Rva002BC260Goal
{
public:
	virtual void unused000();
	virtual void unused004();
	virtual void configure(int a, int b, int c, int d, int e, int f);
	void finalize();

private:
	unsigned char m_unreconstructed00c[0x50];
};

struct Rva002BC260Coord3D
{
	float x;
	float y;
	float z;
};

class Rva002BC260Owner
{
public:
	void run(void *arg1, void *arg2, void *arg3, void *arg4);

private:
	unsigned char m_unreconstructed000[8];
	void *m_goalArguments;
	unsigned char m_unreconstructed00c[0x3f4];
	Rva002BC260Goal m_goal;
	Rva002BC260Coord3D m_source;
	unsigned char m_unreconstructed460[8];
	int m_unreconstructed468;
	unsigned char m_unreconstructed46c;
	unsigned char m_unreconstructed46d[0xf];
	Rva002BC260Coord3D m_destination;
};

extern Rva002BC260Global *g_rva002bc260;

void Rva002BC260Owner::run(void *arg1, void *arg2, void *arg3, void *arg4)
{
	Rva002BC260Goal *goal = &m_goal;
	g_rva002bc260->initialize(m_goalArguments, arg1, goal, arg2, arg3, arg4);
	goal->configure(1, 0xfa0, 0x447a0000, 0x447a0000, 0, 0);
	goal->finalize();
	m_destination = m_source;
	m_unreconstructed468 = 0;
	m_unreconstructed46c = 0;
}
