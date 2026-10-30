// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<FlightDeckBehavior::FlightDeckInfo> reallocating
// insert, retail 0x00231A00, 334 bytes. The name sat on the 5-byte
// incremental-link thunk at 0x0000A47A and the body it jumps to carried only a
// machine byte-dump row.
//
// The callees confirm the element: both bulk phases reach helpers the ledger
// already names for FlightDeckInfo -- __uninitialized_copy at 0x0022FE20
// through the ILT at 0x0002894D and __uninitialized_fill_n at 0x0022FE80
// through the ILT at 0x00017E0E.
//
// The element is 24 bytes -- a Coord3D, a Real, an Int and an ObjectID -- so
// both size computations go through the signed divide-by-twenty-four magic
// multiply and the byte count is a lea followed by a shift of three. Retail
// hands the helpers' empty dispatch tag the address of its own trailing bool
// argument rather than spending a frame slot on it.

enum ObjectID
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
	void set(const Coord3D *p) { x = p->x; y = p->y; z = p->z; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
class FlightDeckBehavior
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
	struct FlightDeckInfo
	{
		Coord3D m_prep;
		float m_orientation;
		int m_runway;
		ObjectID m_objectInSpace;
	};
};

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
static void vectorSmallDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	friend void vectorSmallDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }
static inline void vectorLargeDeallocate(void *block) { ::operator delete(block); }
static inline void vectorSmallDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

struct __false_type
{
};

template <class Type>
class allocator
{
};

// Both reach the helpers the ledger already names for this element through
// their link thunks; naming them apart from the _STL spellings keeps those
// names on their real bodies at 0x0022FE20 and 0x0022FE80.
FlightDeckBehavior::FlightDeckInfo *__cdecl BfmeFlightDeckInfoUninitializedCopy(
	FlightDeckBehavior::FlightDeckInfo *first, FlightDeckBehavior::FlightDeckInfo *last, FlightDeckBehavior::FlightDeckInfo *result, const __false_type &);

// The fill helper is STLport's own template, defined here so the compiler can
// see that it does not keep the value's address (the 0x00231C50 caller below
// depends on that); it emits the same body as FlightDeckBehavior.cpp's
// matched copy at 0x0022FE80.
template <class _ForwardIter, class _Size, class _Tp>
__declspec(noinline) _ForwardIter __uninitialized_fill_n(_ForwardIter __first, _Size __n,
	const _Tp &__x, const __false_type &)
{
	_ForwardIter __cur = __first;
	for (; __n > 0; --__n, ++__cur)
		new (&*__cur) _Tp(__x);
	return __cur;
}

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &,
	unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Type *newStart;
	if (length)
	{
		unsigned int bytes = length * sizeof(Type);
		if (bytes > 128)
			newStart = (Type *)vectorLargeAllocate(bytes);
		else
			newStart = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = BfmeFlightDeckInfoUninitializedCopy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = __uninitialized_fill_n(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeFlightDeckInfoUninitializedCopy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	if (_M_start)
	{
		unsigned int bytes = (unsigned int)(_M_end_of_storage - _M_start) * sizeof(Type);
		if (bytes > 128)
			vectorLargeDeallocate(_M_start);
		else
			vectorSmallDeallocate(_M_start, bytes);
	}

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

template class vector<FlightDeckBehavior::FlightDeckInfo, allocator<FlightDeckBehavior::FlightDeckInfo> >;
}

// Retail 0x00231C50 (812 B, ret 4): the AODHordeContain.cpp offset builder
// whose per-member jitter vector grows through the _M_insert_overflow above
// (ILT 0x0000A47A). It lives in this unit because that callee must be visible
// to the compiler: with the insert defined beside it, the six-float record
// stays unaliased and retail's interleaved element copy and dead-argument
// angle slot come out; with the insert only declared both differ (49 bytes).
// The owner keeps its address name: no BFME 1 caller or ILT spelling
// (ilt_oracle at 0x00043531) proves AODHordeContain::initOffsets.
extern void j_00005835();
extern void j_0002de0c();

struct Rva00231C50Record { float values[6]; };

class Rva00231C50Jitter : public _STL::vector<FlightDeckBehavior::FlightDeckInfo,
	_STL::allocator<FlightDeckBehavior::FlightDeckInfo> >
{
public:
	void reserve(int n)
	{
		typedef void (Rva00231C50Jitter::*Fn)(int);
		union { void (*fn)(); Fn call; } u = { j_00005835 };
		(this->*u.call)(n);
	}
	void append(const FlightDeckBehavior::FlightDeckInfo &r)
	{
		if (this->_M_finish != this->_M_end_of_storage)
		{
			if (this->_M_finish)
				new (this->_M_finish) Rva00231C50Record(*(const Rva00231C50Record *)&r);
			++this->_M_finish;
		}
		else
		{
			_STL::__false_type tag;
			this->_M_insert_overflow(this->_M_finish, r, tag, 1, true);
		}
	}
};

struct Rva00231C50Item { unsigned words[4]; };
struct Rva00231C50Items
{
	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	Rva00231C50Item *m_start;
	Rva00231C50Item *m_finish;
	Rva00231C50Item *m_end;
};
// class-gate: allow Coord2D the matched callee row ?rotatedOffset@Rva00233F30@@QAE?AURva00233F30Offset@@PBVCoord2D@@@Z is class-keyed; the canonical header is struct-keyed
class Coord2D { public: float x, y; };
class Rva00231C50Object { public: char pad000[0x38]; Coord3D m_cachedPos; float m_cachedAngle; };
class BfmePairDH { public: BfmePairDH() {} BfmePairDH(const BfmePairDH &v) : m_bfmeFirst(v.m_bfmeFirst), m_bfmeSecond(v.m_bfmeSecond) {} int m_bfmeFirst, m_bfmeSecond; };
class Gen_002301A0 { public: BfmePairDH bfmeGet(int) const; };
struct Rva00233F30Offset { Rva00233F30Offset() {} Rva00233F30Offset(const Rva00233F30Offset &v) : x(v.x), y(v.y) {} float x, y; };
struct Rva00233F30 { Rva00233F30Offset rotatedOffset(const Coord2D *); };
class BfmeAODHordeContainOwner { public: void addPathPosition(const Coord3D *); };
float Rva0002CCA5GetGameLogicRandomValueRealThunk(float, float, char *, int);
struct Data00231C50 { char prefix[0x2f8]; float f2f8; float f2fc; float f300; float f304; float f308; float f30c; float f310; float f314; };
struct FlowPoint00231C50 { float key; float angle; Coord3D position; bool flag; };

class Formation00231C50
{
public:
	void rva00231C50(int arg);
	char prefix[4]; Data00231C50 *data; Rva00231C50Object *object;
	char pad00c[0x120]; Rva00231C50Items items;
	char pad138[0xec]; Rva00231C50Jitter randoms;
	char pad230[0x3e4]; FlowPoint00231C50 points[20]; int count;
};

// ?rva00231C50@Formation00231C50@@QAEXH@Z
void Formation00231C50::rva00231C50(int arg)
{
	Data00231C50 *settings = data;
	Rva00231C50Object *owner = object;
	{
		typedef void (Formation00231C50::*Fn)(int);
		union { void (*fn)(); Fn call; } u = { j_0002de0c };
		(this->*u.call)(arg);
	}
	int memberCount = items.size();
	randoms.reserve(memberCount);
	for (int i = 0; i < memberCount; ++i)
	{
		Rva00231C50Record r;
		float angle = 6.2831855f * settings->f2f8;
		r.values[1] = Rva0002CCA5GetGameLogicRandomValueRealThunk(1.0f - settings->f300, 1.0f + settings->f300, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 521);
		r.values[0] = Rva0002CCA5GetGameLogicRandomValueRealThunk(0.0f, angle, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 522);
		r.values[2] = Rva0002CCA5GetGameLogicRandomValueRealThunk(1.0f - settings->f2f8, 1.0f + settings->f2f8, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 523);
		angle = 6.2831855f * settings->f30c;
		r.values[4] = Rva0002CCA5GetGameLogicRandomValueRealThunk(1.0f - settings->f314, 1.0f + settings->f314, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 526);
		r.values[3] = Rva0002CCA5GetGameLogicRandomValueRealThunk(0.0f, angle, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 527);
		r.values[5] = Rva0002CCA5GetGameLogicRandomValueRealThunk(1.0f - settings->f30c, 1.0f + settings->f30c, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 528);
		randoms.append(*(const FlightDeckBehavior::FlightDeckInfo *)&r);
	}
	float firstOffset = 0;
	for (int i = 0; i < memberCount; ++i)
	{
		BfmePairDH pair = ((Gen_002301A0 *)this)->bfmeGet(i);
		Coord2D &formationOffset = *(Coord2D *)&pair;
		bool found = false;
		for (int j = 0; j < count; ++j)
			if (formationOffset.x == points[j].key) { found = true; break; }
		if (found)
			continue;
		if (count >= 20)
			break;
		points[count].key = formationOffset.x;
		if (count == 0)
			firstOffset = formationOffset.x;
		formationOffset.x -= firstOffset;
		formationOffset.y = 0;
		Rva00233F30Offset rotated = ((Rva00233F30 *)this)->rotatedOffset((Coord2D *)&formationOffset);
		points[count].flag = true;
		Coord3D position;
		position.set(&owner->m_cachedPos);
		position.x += rotated.x;
		position.y += rotated.y;
		points[count].position = position;
		points[count].angle = owner->m_cachedAngle;
		++count;
	}
	for (int i = count - 1; i >= 0; --i)
		((BfmeAODHordeContainOwner *)this)->addPathPosition(&points[i].position);
}
