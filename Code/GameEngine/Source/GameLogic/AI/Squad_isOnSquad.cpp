// cl: /DNDEBUG /MD /EHsc
// readable body of ?isOnSquad@Squad@@QBE_NPBVObject@@@Z: Code/GameEngine/Source/GameLogic/AI/Squad.cpp

// Squad::isOnSquad, retail 0x0018B520. No calls: the object's id is read inline
// from +0x74, and the squad's membership is a plain pointer pair at +0x04 and
// +0x08 walked one dword at a time.
//
// The empty case is tested once before the loop and then only at the bottom,
// which is a while loop rather than a for.
//
// The membership test is written id-first. Retail compares `cmp edx,[eax]' -
// the id in the register against the entry in memory - and `*p == id' emits
// `cmp [eax],edx' instead. One byte, and the only one in the body.

typedef int ObjectID;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unmodelled_00[ 0x74 ];
	ObjectID m_id;							// +0x74
};

class Squad
{
public:
	Bool isOnSquad( const Object *obj ) const;

private:
	unsigned char m_unmodelled_00[ 4 ];
	ObjectID *m_begin;						// +0x04
	ObjectID *m_end;						// +0x08
};

// ?isOnSquad@Squad@@QBE_NPBVObject@@@Z
Bool Squad::isOnSquad( const Object *obj ) const
{
	ObjectID id = obj->m_id;

	ObjectID *p = m_begin;
	ObjectID *end = m_end;

	while( p != end )
	{
		if( id == *p )
			return true;

		++p;
	}

	return false;
}
