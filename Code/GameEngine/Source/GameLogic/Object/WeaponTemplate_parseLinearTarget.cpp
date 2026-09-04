// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Open-BFME5: WeaponTemplate::parseLinearTarget, retail 0x001EA880 size 151.
// Field table 0x0109FE18 names this callback LinearTarget, immediately after
// ScatterTarget. Tokens are X/Y (scanReal) and T (scanUnsignedInt). The
// 12-byte record is pushed onto a vector at +0x40, which sits against the
// scatter vector at +0x34. Construct / overflow go through ILTs 0x0001A5EB
// and 0x00001B6D. Dispatch tag is aliased onto the instance argument.

struct LinearTarget
{
	float x;
	float y;
	unsigned int t;
};

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	static float scanReal(const char *token);
	static unsigned int scanUnsignedInt(const char *token);
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

void __cdecl BfmeLinearTargetConstruct(LinearTarget *destination, const LinearTarget &value);

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
	static void parseLinearTarget(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_pad_00[0x40];
	_STL::public_vector<LinearTarget, _STL::allocator<LinearTarget> > m_linearTargets;
};

// ?parseLinearTarget@WeaponTemplate@@CAXPAVINI@@PAX1PBX@Z
void WeaponTemplate::parseLinearTarget(INI *ini, void *instance, void *, const void *)
{
	LinearTarget rec;
	rec.x = INI::scanReal(ini->getNextSubToken("X"));
	rec.y = INI::scanReal(ini->getNextSubToken("Y"));
	unsigned int t = INI::scanUnsignedInt(ini->getNextSubToken("T"));

	WeaponTemplate *self = (WeaponTemplate *)instance;
	_STL::public_vector<LinearTarget, _STL::allocator<LinearTarget> > &items = self->m_linearTargets;
	LinearTarget *end = items._M_end_of_storage;
	rec.t = t;
	if (items._M_finish != end)
	{
		_STL::BfmeLinearTargetConstruct(items._M_finish, rec);
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow(items._M_finish, rec,
			reinterpret_cast<const _STL::__false_type &>(instance), 1, true);
	}
}
