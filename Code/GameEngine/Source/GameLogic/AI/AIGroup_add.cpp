// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// stlport
// Open-BFME: AIGroup::add, retail 0x001526C0, 150 bytes.
//
// Team::getTeamAsAIGroup calls this body through its ILT. The BFME kind mask
// keeps structures, always-selectable objects, and the bit-122 BFME class in a
// group when they lack an AI update interface.

#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <bitset>
#include <list>

typedef unsigned int UnsignedInt;
typedef bool Bool;

class AIGroup;

class Object;

class BfmeKindOfMask
{
public:
	BfmeKindOfMask()
	{
		// This order preserves retail's mask materialization schedule.
		m_bits.set(7);
		m_bits.set(122);
		m_bits.set(57);
	}

private:
	std::bitset<192> m_bits;
};

class BfmeKindOfTester
{
public:
	Bool isAnyKindOf(const BfmeKindOfMask &mask) const;
};

class BfmeGroupAI
{
};

class Object
{
public:
	BfmeGroupAI *getAI(void) { return m_ai; }
	void enterGroup(AIGroup *group);

private:
	unsigned char m_unreconstructed_000[0x204];
	BfmeGroupAI *m_ai;
};

class AIGroup
{
public:
	void add(Object *member);

private:
	unsigned char m_unreconstructed_000[4];
	_STL::list<Object *> m_memberList;
	UnsignedInt m_memberListSize;
	void *m_groundPath;
	Bool m_dirty;
};

// ?add@AIGroup@@QAEXPAVObject@@@Z
void AIGroup::add(Object *member)
{
	if (member == 0)
		return;

	BfmeKindOfMask validNonAIKindofs;
	BfmeGroupAI *ai = member->getAI();
	if (ai == 0 && !reinterpret_cast<const BfmeKindOfTester *>(member)->isAnyKindOf(validNonAIKindofs))
		return;

	m_memberList.push_back(member);
	++m_memberListSize;
	member->enterGroup(this);
	m_dirty = true;
}
