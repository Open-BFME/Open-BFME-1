// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// BFME's EmotionSystem has its eight-byte subsystem prefix first, followed by
// the EmotionNugget pointer vector used by the matched findNugget/addNugget
// bodies at 0x0037CD70/0x0037CF10.  Those members put the ObjectID vector at
// +0x14, exactly where this body reads its begin/end/capacity pointers.
//
// The sole retail caller at 0x001C6AD7 loads TheEmotionSystem (0x012F0878)
// into ECX and passes an Object pointer.  The public source name is not
// independently present, so the method remains address-derived while keeping
// the proven EmotionSystem owner and ABI.

#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_prefix[ 0x74 ];
	ObjectID m_id;
};

class EmotionNugget;

class EmotionSystem
{
public:
	void rva0037CFF0( Object *object );

private:
	unsigned char m_subsystemPrefix[ 8 ];
	_STL::vector<EmotionNugget *> m_nuggets;
	_STL::vector<ObjectID> m_objectIDs;
};

void EmotionSystem::rva0037CFF0( Object *object )
{
	_STL::vector<ObjectID>::iterator iter = m_objectIDs.begin();
	_STL::vector<ObjectID>::iterator end = m_objectIDs.end();
	for( ; iter != end; ++iter )
	{
		if( *iter == object->getID() )
			return;
	}

	m_objectIDs.push_back( object->getID() );
}
