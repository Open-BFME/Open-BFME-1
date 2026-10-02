// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stlp_nodealloc
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

// Forward of the retail kind-of mask the defining spelling names
// (?isAnyKindOf@Thing@@QBE_NABV?$BitFlags@$0HE@@@@Z, pinned via the ILT at
// 0x0004250A onto the body at 0x00132AE0). The mask below is still built as
// BfmeKindOfMask (identical stack construction); only its address is passed
// on as the BitFlags<116> the ledger records. No body is declared here.
template <int N>
class BitFlags;

class Thing
{
public:
	// Retail spelling of the kind-of test; the argument is the BfmeKindOfMask
	// local below, passed by address.
	Bool isAnyKindOf(const BitFlags<116> &mask) const;
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
	if (ai == 0 && !reinterpret_cast<const Thing *>(member)->isAnyKindOf(
		reinterpret_cast<const BitFlags<116> &>(validNonAIKindofs)))
		return;

	m_memberList.push_back(member);
	++m_memberListSize;
	member->enterGroup(this);
	m_dirty = true;
}
