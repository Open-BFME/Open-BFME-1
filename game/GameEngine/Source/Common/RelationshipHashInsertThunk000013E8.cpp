// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// The carved ILT at 0x000013E8 jumps to the matched Relationship hash insert
// body at 0x00787140.  This wrapper keeps the ILT's address-qualified name.
//
// The call target is named directly: the _STL::hashtable instantiation for
// pair<const int, Relationship> is declared here (only its shape matters for
// the symbol), so no linker alias pragma is needed.

#define _STLP_NO_EXCEPTIONS 1

typedef int Int;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

namespace _STL
{
template <class _T1, class _T2>
struct pair;

template <class _Key>
struct hash;

template <class _Pair>
struct _Select1st;

template <class _Key>
struct equal_to;

template <class _Tp>
class allocator;

// Declared exactly as the retail body is, so the call resolves by name.
template <class _Val, class _Key, class _HashF, class _ExtractKey, class _EqlF,
	class _Alloc>
class hashtable
{
public:
	pair<const Int, Relationship> &_M_insert(
		const pair<const Int, Relationship> &value);
};

typedef hashtable<
	pair<const Int, Relationship>,
	Int,
	hash<Int>,
	_Select1st<pair<const Int, Relationship> >,
	equal_to<Int>,
	allocator<pair<const Int, Relationship> > >
	RelationshipHashtable;
}

class Rva000013E8RelationshipHashInsertThunk
{
public:
	__declspec(noinline) _STL::pair<const Int, Relationship> &forward(
		const _STL::pair<const Int, Relationship> &value)
	{
		return ((_STL::RelationshipHashtable *)this)->_M_insert(value);
	}
};

typedef _STL::pair<const Int, Relationship> &
	(Rva000013E8RelationshipHashInsertThunk::*Rva000013E8ForwardType)(
		const _STL::pair<const Int, Relationship> &);

Rva000013E8ForwardType g_rva000013e8_forward =
	&Rva000013E8RelationshipHashInsertThunk::forward;
