// ?addObject@BfmeObjectIdOwner@@QAEXPAVObject@@@Z
// partial score=0.82 date=2026-09-04
// ?addObject@BfmeObjectIdOwner@@QAEXPAVObject@@@Z
// partial score=0.82 date=2026-09-04
// cl: /DNDEBUG /MD /EHs-c-
// stlport
// partial score=0.82
//
// Open-BFME5: thiscall ObjectID vector unique-append at retail 0x0037CFF0 (95B).
// Sibling of landed removeObject at 0x0037CBC0. Shape correct: inline scan
// of vector at +0x14 for Object::m_id (+0x74), then capacity-fast push_back
// or _M_insert_overflow ILT 0x00010B8B. Wall is prologue register shape
// (retail mov edx,ecx / lea ecx,[edx+0x14] vs add ecx,0x14) and found-exit
// sharing the overflow epilogue.

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
	ObjectID m_id;
};

class BfmeObjectIdOwner
{
public:
	void addObject(Object *object);

private:
	char m_pad[0x14];
	_STL::vector<ObjectID> m_ids;
};

void BfmeObjectIdOwner::addObject(Object *object)
{
	ObjectID id = object->getID();
	if (_STL::find(m_ids.begin(), m_ids.end(), id) != m_ids.end())
		return;
	m_ids.push_back(id);
}
