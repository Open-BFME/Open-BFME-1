// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Retail 0x0018B9A0 / 0x0018B950: vector<ObjectID> at +0x04.  addObjectID is
// the inlined push_back; addObject extracts Object::m_id at +0x74 and then
// does the same push.  Siblings of the +0x04 container at 0x0018B520 and
// 0x0018B620, not of Squad (whose matched rows keep the vector at +0x08).

#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID() const { return m_id; }

	unsigned char m_pad[ 0x74 ];
	ObjectID m_id;
};

class Rva0018B9A0Holder
{
public:
	void addObjectID( ObjectID id );
	void addObject( Object *objectToAdd );

private:
	int m_vptr;
	_STL::vector<ObjectID> m_ids;
};

void Rva0018B9A0Holder::addObjectID( ObjectID id )
{
	m_ids.push_back( id );
}

void Rva0018B9A0Holder::addObject( Object *objectToAdd )
{
	if ( objectToAdd )
		m_ids.push_back( objectToAdd->getID() );
}
