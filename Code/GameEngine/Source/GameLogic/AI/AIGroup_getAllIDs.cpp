// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::getAllIDs, retail 0x00154AD0, 136 bytes.
//
// Clears the ID vector at +0x34 (STLport erase-all leftover copy with a
// zero count, then end=begin) and walks the member list at +4, pushing
// Object::m_id at +0x74.

#include <vector>

enum ObjectID { INVALID_OBJECT_ID = 0 };

class Object
{
public:
	ObjectID getID() const { return m_id; }

	unsigned char m_pad[0x74];
	ObjectID m_id;
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;
};

class AIGroup
{
public:
	const _STL::vector<ObjectID> &getAllIDs(void) const;

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;
	char m_bfmeMid[0x34 - 0x08];
	mutable _STL::vector<ObjectID> m_lastRequestedIDList;
};

// ?getAllIDs@AIGroup@@QBEABV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@XZ
const _STL::vector<ObjectID> &AIGroup::getAllIDs(void) const
{
	m_lastRequestedIDList.clear();
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		if (obj)
			m_lastRequestedIDList.push_back(obj->getID());
	}
	return m_lastRequestedIDList;
}
