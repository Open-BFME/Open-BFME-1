// ??0Rva003E62B0Info@@QAE@PAVPathfinder@@PAVObject@@HHHH@Z
// partial score=0.78 date=2026-09-04
// partial score=0.78 date=2026-09-04
// cl: /DNDEBUG /MD
//
// Retail 0x003E62B0 (64B): six-arg query payload ctor. Exact size; wall is
// prologue register mirror: retail preloads arg6 into edx and arg2 into eax
// before push esi, then stores +0x10/+0x14/+0x18/+0x1c from edx reloads.
// Volatile member stores fix order but keep eax/edx swapped; volatile locals
// spill to stack (98B).

typedef int Int;
class Object;
class Pathfinder;
class Pathfinder { public: void bfmeQuery(Object *obj, Int *radius, Int *center); };
class Rva003E62B0Info
{
public:
	Rva003E62B0Info(Pathfinder *pathfinder, Object *obj, Int a3, Int a4, Int a5, Int a6);
	Pathfinder *m_pathfinder;
	Object *m_obj;
	Int m_center;
	Int m_radius;
	Int volatile m_a6;
	Int volatile m_a3;
	Int volatile m_a4;
	Int volatile m_a5;
};
Rva003E62B0Info::Rva003E62B0Info(Pathfinder *pathfinder, Object *obj, Int a3, Int a4, Int a5, Int a6)
{
	Int six = a6;
	Object *o = obj;
	Pathfinder *pf = pathfinder;
	m_a6 = six;
	Int three = a3;
	m_a3 = three;
	Int four = a4;
	m_a4 = four;
	Int five = a5;
	m_a5 = five;
	m_pathfinder = pf;
	m_obj = o;
	pf->bfmeQuery(o, &m_radius, &m_center);
}
