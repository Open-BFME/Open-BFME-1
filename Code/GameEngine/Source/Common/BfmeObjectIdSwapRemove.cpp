// cl: /DNDEBUG /MD /EHs-c-
// stlport
//
// Open-BFME5: thiscall ObjectID vector swap-remove at retail 0x0037CBC0 (68B).
// Reads Object::m_id at +0x74, __find over the ObjectID vector at this+0x14,
// then unordered-erase by copying end[-1] into the hole and shrinking end.

#include <algorithm>
#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	ObjectID getID(void) const { return m_id; }

private:
	char m_pad[0x74];
	ObjectID m_id; // +0x74
};

class BfmeObjectIdVector
{
public:
	ObjectID *begin(void) { return m_begin; }
	ObjectID *end(void) { return m_end; }

	ObjectID *m_begin; // +0
	ObjectID *m_end;   // +4
	ObjectID *m_cap;   // +8
};

class BfmeObjectIdOwner
{
public:
	bool removeObject(Object *object);

private:
	char m_pad[0x14];
	BfmeObjectIdVector m_ids; // +0x14
};

// ?removeObject@BfmeObjectIdOwner@@QAE_NPAVObject@@@Z
bool BfmeObjectIdOwner::removeObject(Object *object)
{
	ObjectID id = object->getID();
	ObjectID *first = m_ids.begin();
	ObjectID *last = m_ids.end();
	ObjectID *found = _STL::find(first, last, id);
	if (found != last)
	{
		*found = *(last - 1);
		--m_ids.m_end;
		return true;
	}
	return false;
}
