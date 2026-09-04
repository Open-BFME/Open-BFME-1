// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef int Int;

class Object;
class Pathfinder
{
public:
    void bfmeQuery(Object *object, Int *radius, Int *center);
};

class Rva003E62B0Info
{
public:
    Rva003E62B0Info(Pathfinder *pathfinder, Object *object,
        Int a3, Int a4, Int a5, Int a6);

    Pathfinder *m_pathfinder;
    Object *m_object;
    Int m_center;
    Int m_radius;
    volatile Int m_a6;
    volatile Int m_a3;
    volatile Int m_a4;
    volatile Int m_a5;
};

Rva003E62B0Info::Rva003E62B0Info(Pathfinder *pathfinder, Object *object,
	Int a3, Int a4, Int a5, Int volatile a6)
{
	register Int six = a6;
	register void *obj = *(void * volatile *)&object;
	register Pathfinder *pf = *(Pathfinder * volatile *)&pathfinder;
	register Int three = a3;
	register Int four = a4;
	register Int five = a5;
	m_a6 = six;
	m_a3 = three;
	m_a4 = four;
	m_a5 = five;
	m_pathfinder = pf;
	m_object = (Object *)obj;
	pf->bfmeQuery((Object *)obj, &m_radius, &m_center);
}
