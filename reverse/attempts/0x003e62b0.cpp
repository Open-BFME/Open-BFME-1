// ??0Rva003E62B0Info@@QAE@PAVPathfinder@@PAVObject@@HHHH@Z
// partial score=0.78 date=2026-09-04
// cl: /DNDEBUG /MD
//
// Open-BFME5: six-arg pathfinding query payload ctor at retail 0x003E62B0 (64B).
// Sibling of ??0Rva003E6200Info@@ at 0x003E6200; Pathfinder::bfmeQuery ILT 0x000461FF.
//
// PARTIAL: size-exact 64B; same call/epilogue. MSVC 7.1 loads a3 before a6
// into edx instead of retail mov edx,[esp+18] (a6) / mov eax,[esp+8] (obj).

typedef int Int;

class Object;
class Pathfinder
{
public:
	void bfmeQuery(Object *obj, Int *radius, Int *center);
};

class Rva003E62B0Info
{
public:
	Rva003E62B0Info(Pathfinder *pathfinder, Object *obj, Int a3, Int a4, Int a5, Int a6);

	Pathfinder *m_pathfinder;
	Object *m_obj;
	Int m_center;
	Int m_radius;
	Int m_a6;
	Int m_a3;
	Int m_a4;
	Int m_a5;
};

// ??0Rva003E62B0Info@@QAE@PAVPathfinder@@PAVObject@@HHHH@Z
Rva003E62B0Info::Rva003E62B0Info(Pathfinder *pathfinder, Object *obj, Int a3, Int a4, Int a5, Int a6)
{
	Int six = a6;
	Object *o = obj;
	Pathfinder *pf = pathfinder;
	Int three = a3;
	Int four = a4;
	Int five = a5;
	m_a6 = six;
	m_a3 = three;
	m_a4 = four;
	m_a5 = five;
	m_pathfinder = pf;
	m_obj = o;
	pf->bfmeQuery(o, &m_radius, &m_center);
}
