// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Open-BFME5: WeaponTemplate::parseScatterTarget, retail 0x001EA7F0 size 110.
// Focused TU: Weapon.cpp keeps the ZH layout (scatter vector after the
// scalars). BFME stores m_scatterTargets at +0x34. The 8-byte Coord2D
// construct and reallocating insert are the already-landed pair at
// 0x001E21F0 / 0x001E9020, reached through their ILTs. The overflow
// dispatch tag is aliased onto the instance argument, the same stack-slot
// trick the member push_back family uses on its value parameter.

struct Coord2D
{
	float x;
	float y;
};

class INI
{
public:
	static void parseCoord2D(INI *, void *, void *, const void *);
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

void __cdecl BfmeCoord2DConstruct(Coord2D *destination, const Coord2D &value);

template <class Type, class Allocator>
class vector
{
public:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);
};

template <class Type, class Allocator>
class public_vector : public vector<Type, Allocator>
{
public:
	using vector<Type, Allocator>::_M_insert_overflow;
};
}

class WeaponTemplate
{
	static void parseScatterTarget(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_pad_00[0x34];
	_STL::public_vector<Coord2D, _STL::allocator<Coord2D> > m_scatterTargets;
};

// ?parseScatterTarget@WeaponTemplate@@CAXPAVINI@@PAX1PBX@Z
void WeaponTemplate::parseScatterTarget(INI *ini, void *instance, void *, const void *)
{
	Coord2D target;
	target.x = 0;
	target.y = 0;
	INI::parseCoord2D(ini, 0, &target, 0);

	WeaponTemplate *self = (WeaponTemplate *)instance;
	_STL::public_vector<Coord2D, _STL::allocator<Coord2D> > &items = self->m_scatterTargets;
	if (items._M_finish != items._M_end_of_storage)
	{
		_STL::BfmeCoord2DConstruct(items._M_finish, target);
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow(items._M_finish, target,
			reinterpret_cast<const _STL::__false_type &>(instance), 1, true);
	}
}
