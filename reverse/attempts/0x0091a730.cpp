// ??0StreakLineClass@@QAE@XZ
// partial score=0.97 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// readable body of ??0StreakLineClass@@QAE@XZ:
// Code/Libraries/Source/WWVegas/WW3D2/streak.cpp
//
// Retail 0x0091A730, 207 bytes. Named by the S4 ctor-then-publish caller as
// S4Made0091A730 (416-byte allocation). Identity is StreakLineClass: base
// RenderObjClass ctor at 0x009204B0, then SegLineRendererClass at +0x104 and
// StreakRendererClass at +0x154 -- the same offsets streak.cpp already uses.
//
// Probe 202/207: vector stores and callee calls match. Wall is EH state
// numbers -- retail `mov byte [esp+0x14], 5` / `6` before the two renderer
// ctors, ours emits `3` and omits the state-6 store (5 bytes). Adding a
// Personalities dtor member picks up a state but also zeros the two vtable
// writes and hoists the EH-state store ahead of them.

class RefCountClass
{
public:
	virtual ~RefCountClass();
	int RefCount;
};

class PersistClass
{
public:
	virtual void On_Post_Load();
};

// upstream layout: reference/shims/sweep/rendobj.h (BFME RenderObjClass is 0xC8)
class RenderObjClass : public RefCountClass, public PersistClass
{
public:
	RenderObjClass();

protected:
	char m_rest[0xC8 - 12];
};

template <class T>
class SimpleVecClass
{
public:
	SimpleVecClass() : Vector(0), VectorMax(0) {}
	virtual ~SimpleVecClass();

protected:
	T *Vector;
	int VectorMax;
};

template <class T>
class SimpleDynVecClass : public SimpleVecClass<T>
{
public:
	SimpleDynVecClass() : ActiveCount(0) {}

protected:
	int ActiveCount;
};

class Vector3;
class Vector4;

// upstream layout: Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.h
class SegLineRendererClass
{
public:
	SegLineRendererClass();

private:
	char m_storage[0x50];
};

// upstream layout: Code/Libraries/Source/WWVegas/WW3D2/StreakRendererCtor.cpp
class StreakRendererClass
{
public:
	StreakRendererClass();

private:
	char m_storage[0x4C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streak.h
// offsets: StreakLineClass_Get_Obj_Space_Bounding_Box.cpp
class StreakLineClass : public RenderObjClass
{
public:
	StreakLineClass();

private:
	unsigned int MaxSubdivisionLevels;
	unsigned int *Personalities;
	float NormalizedScreenArea;
	SimpleDynVecClass<Vector3> PointLocations;
	SimpleDynVecClass<Vector4> PointColors;
	SimpleDynVecClass<float> PointWidths;
	SegLineRendererClass LineRenderer;
	StreakRendererClass StreakRenderer;
};

// ??0StreakLineClass@@QAE@XZ
StreakLineClass::StreakLineClass(void) :
	MaxSubdivisionLevels(0),
	NormalizedScreenArea(0.0f)
{
	Personalities = 0;
}
