// cl: /DNDEBUG /MD /EHsc
// readable body of ?onTunnelCreated@TunnelTracker@@: Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp

// Open-BFME5: TunnelTracker::onTunnelCreated, retail 0x000F8DD0, 56 bytes. The
// body carried only a machine byte-dump row; reverse/reloc_names.csv holds the
// name with identity=real.
//
// A counter at +0x14 goes up, then the object's id at +0x74 is pushed onto the
// list whose sentinel pointer sits at +4. The push is STLport's insert with the
// node allocation and the four link stores all inlined: node next at +0, prev
// at +4, value at +8, twelve bytes in all.
//
// The null test between the allocation and the value store is placement new --
// this compiler checks the pointer operator new(size_t, void*) returns before
// constructing through it.

inline void *operator new(unsigned int, void *place) { return place; }

typedef unsigned int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_bfmeHead[0x74];
	ObjectID m_bfmeID;					// +0x74
};

namespace _STL
{
void *__cdecl vectorSmallAllocate(unsigned int bytes);		// retail 0x0082E540
}

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;				// +0x00
	BfmeListNodeBase *m_bfmePrev;				// +0x04
};

struct BfmeObjectIDNode : public BfmeListNodeBase
{
	ObjectID m_bfmeValue;					// +0x08
};

class BfmeObjectIDList
{
public:
	// Taken by value, not by const reference: by reference the id is only read
	// inside push_back, after the allocation, where retail reads it before.
	//
	// The sentinel goes in as an argument for the same reason -- push_back is
	// insert at end(), and the end iterator is built at the call site, so the
	// load of the sentinel lands ahead of the allocation.
	void push_back(ObjectID value) { insert(m_bfmeNode, value); }

	void insert(BfmeListNodeBase *n, ObjectID value)
	{
		BfmeObjectIDNode *tmp = (BfmeObjectIDNode *)
			_STL::vectorSmallAllocate(sizeof(BfmeObjectIDNode));
		new (&tmp->m_bfmeValue) ObjectID(value);

		BfmeListNodeBase *p = n->m_bfmePrev;
		tmp->m_bfmeNext = n;
		tmp->m_bfmePrev = p;
		p->m_bfmeNext = tmp;
		n->m_bfmePrev = tmp;
	}

	BfmeListNodeBase *m_bfmeNode;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	void onTunnelCreated(const Object *object);

private:
	char m_bfmeHeadA[0x04];
	BfmeObjectIDList m_bfmeList;				// +0x04
	char m_bfmeHeadB[0x14 - 0x08];
	int m_bfmeCount;					// +0x14
};

// ?onTunnelCreated@TunnelTracker@@QAEXPBVObject@@@Z
void TunnelTracker::onTunnelCreated(const Object *object)
{
	++m_bfmeCount;
	m_bfmeList.push_back(object->m_bfmeID);
}
