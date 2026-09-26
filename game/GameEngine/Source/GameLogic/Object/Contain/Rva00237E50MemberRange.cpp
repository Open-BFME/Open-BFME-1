// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// Retail 0x00237E50 is an address-derived member selector.  It
// scans the list returned by the interface at this-0xC4 and then the indexed
// member tree at +0x30, retaining the Object whose current weapon has the
// greatest height-adjusted attack range.  The neutral owner preserves the
// proven raw ABI without inventing a canonical source declaration.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

class Object;
class Weapon;

enum WeaponSlotType
{
	Rva00237E50WeaponSlotUnknown = 0
};

class Object
{
public:
	Weapon *getCurrentWeapon( WeaponSlotType *slot );
};

class Weapon
{
public:
	Real getAttackRange( const Object *source, Real heightDifference ) const;
};

// These are existing ILT thunk rows.  The member-pointer adapters below keep
// the retail call targets and exact ECX/stack ABI while avoiding the stale
// candidate alias formerly attached to 0x0001536B.
extern void j_00031a7f();
extern void j_0001536b();

struct BfmeMemberNode
{
	BfmeMemberNode *m_next;
	BfmeMemberNode *m_previous;
	Object *m_object;
};

typedef _STL::list<Object *> BfmeMemberList;

struct BfmeMemberIndexNode
{
	UnsignedInt m_color;
	BfmeMemberIndexNode *m_parent;
	BfmeMemberIndexNode *m_next;
	BfmeMemberIndexNode *m_right;
	UnsignedInt m_key;
};

namespace _STL
{
struct _Rb_tree_node_base;

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment( _Rb_tree_node_base * );
};
}

typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

class GameLogic
{
public:
	__forceinline Object *findObjectByID( UnsignedInt key )
	{
		BfmeObjectPtrHash::iterator it = m_objectHash.find( key );
		if ( it == m_objectHash.end() )
			return 0;
		return (*it).second;
	}

	char m_head[ 0xb0 ];
	BfmeObjectPtrHash m_objectHash;
};

extern GameLogic *TheBfmeGameLogic;

class Rva00237E50MemberView
{
public:
#define RVA00237E50_SLOT(N) virtual Int slot##N() = 0
	RVA00237E50_SLOT(00); RVA00237E50_SLOT(01); RVA00237E50_SLOT(02);
	RVA00237E50_SLOT(03); RVA00237E50_SLOT(04); RVA00237E50_SLOT(05);
	RVA00237E50_SLOT(06); RVA00237E50_SLOT(07); RVA00237E50_SLOT(08);
	RVA00237E50_SLOT(09); RVA00237E50_SLOT(10); RVA00237E50_SLOT(11);
	RVA00237E50_SLOT(12); RVA00237E50_SLOT(13); RVA00237E50_SLOT(14);
	RVA00237E50_SLOT(15); RVA00237E50_SLOT(16); RVA00237E50_SLOT(17);
	RVA00237E50_SLOT(18); RVA00237E50_SLOT(19); RVA00237E50_SLOT(20);
	RVA00237E50_SLOT(21); RVA00237E50_SLOT(22); RVA00237E50_SLOT(23);
	RVA00237E50_SLOT(24); RVA00237E50_SLOT(25); RVA00237E50_SLOT(26);
	RVA00237E50_SLOT(27); RVA00237E50_SLOT(28); RVA00237E50_SLOT(29);
	RVA00237E50_SLOT(30); RVA00237E50_SLOT(31); RVA00237E50_SLOT(32);
	RVA00237E50_SLOT(33); RVA00237E50_SLOT(34); RVA00237E50_SLOT(35);
	RVA00237E50_SLOT(36); RVA00237E50_SLOT(37); RVA00237E50_SLOT(38);
	RVA00237E50_SLOT(39); RVA00237E50_SLOT(40); RVA00237E50_SLOT(41);
	RVA00237E50_SLOT(42); RVA00237E50_SLOT(43); RVA00237E50_SLOT(44);
	RVA00237E50_SLOT(45); RVA00237E50_SLOT(46); RVA00237E50_SLOT(47);
	RVA00237E50_SLOT(48); RVA00237E50_SLOT(49); RVA00237E50_SLOT(50);
	RVA00237E50_SLOT(51); RVA00237E50_SLOT(52); RVA00237E50_SLOT(53);
	RVA00237E50_SLOT(54); RVA00237E50_SLOT(55); RVA00237E50_SLOT(56);
	RVA00237E50_SLOT(57); RVA00237E50_SLOT(58); RVA00237E50_SLOT(59);
	RVA00237E50_SLOT(60); RVA00237E50_SLOT(61); RVA00237E50_SLOT(62);
	RVA00237E50_SLOT(63); RVA00237E50_SLOT(64);
	virtual const BfmeMemberList &getMemberList() const = 0;
#undef RVA00237E50_SLOT
};

class Rva00237E50Owner
{
public:
	Object *rva00237E50();

private:
	char m_prefix[ 0x30 ];
	BfmeMemberIndexNode *m_memberIndex;
};

typedef Weapon *(Object::*Rva00237E50GetWeaponCall)( WeaponSlotType * );
typedef Real (Weapon::*Rva00237E50RangeCall)( const Object *, Real ) const;

static Weapon *rva00237E50GetWeapon( Object *object )
{
	union
	{
		void *asVoid;
		Rva00237E50GetWeaponCall asMember;
	} call;
	call.asVoid = (void *)j_00031a7f;
	return (object->*call.asMember)((WeaponSlotType *)0);
}

static Real rva00237E50GetRange( Weapon *weapon, const Object *object )
{
	union
	{
		void *asVoid;
		Rva00237E50RangeCall asMember;
	} call;
	call.asVoid = (void *)j_0001536b;
	return (weapon->*call.asMember)(object, 0.0f);
}

// ?rva00237E50@Rva00237E50Owner@@QAEPAVObject@@XZ
Object *Rva00237E50Owner::rva00237E50()
{
	Object *bestObject = 0;
	Real bestRange = 0.0f;
	const BfmeMemberList &members =
		((Rva00237E50MemberView *)((char *)this - 0xc4))->getMemberList();

	for (BfmeMemberList::const_iterator it = members.begin();
		it != members.end(); ++it)
	{
		Object *object = *it;
		if (object != 0)
		{
			Weapon *weapon = rva00237E50GetWeapon( object );
			if (weapon != 0)
			{
				Real range = rva00237E50GetRange( weapon, object );
				if (range > bestRange)
				{
					bestRange = range;
					bestObject = object;
				}
			}
		}
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		if (key != 0)
		{
			Object *object = TheBfmeGameLogic->findObjectByID( key );
			if (object != 0)
			{
				Weapon *weapon = rva00237E50GetWeapon( object );
				if (weapon != 0)
				{
					Real range = rva00237E50GetRange( weapon, object );
					if (range > bestRange)
					{
						bestRange = range;
						bestObject = object;
					}
				}
			}
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}

	return bestObject;
}
