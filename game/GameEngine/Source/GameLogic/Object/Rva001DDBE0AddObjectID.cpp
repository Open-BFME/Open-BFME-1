// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Retail 0x001DDBE0: inlined vector<ObjectID>::push_back of Object::m_id at
// +0x74, container at this+8, always returns true.  Overflow calls the
// ObjectID insert pin at 0x00010B8B.

#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

	unsigned char m_pad[0x74];
	ObjectID m_id;
};

class Rva001DDBE0Holder
{
public:
	bool addObject(Object *objectToAdd);

private:
	unsigned char m_pad[8];
	_STL::vector<ObjectID> m_ids;
};

bool Rva001DDBE0Holder::addObject(Object *objectToAdd)
{
	m_ids.push_back(objectToAdd->getID());
	return true;
}
