// ?rva00240c50@Rva00240C50HordeContain@@QAE_NXZ
// partial score=0.08 date=2026-09-20
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: address-derived HordeContain member promotion, retail 0x00240C50.

typedef bool Bool;
typedef int Int;

#define _STLP_USE_NEWALLOC 1
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate( unsigned int bytes );
};

template <bool Threads, int Instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *node, unsigned int bytes );
};
}

class Object
{
public:
	char m_pad[ 0x74 ];
	Int m_id;
};

class BfmeSubDSU
{
public:
	void **bfmeTwoDSU( void **what );
	unsigned int erase( const Int &what );

	char m_body[ 0x0c ];
};

struct BfmeSlot
{
	Int m_key;
	float m_x;
	float m_y;
	float m_z;
};

struct BfmeRandomNode
{
	BfmeRandomNode *m_next;
	BfmeRandomNode *m_previous;
	Int m_value;
};

struct BfmeRandomList
{
	BfmeRandomNode *m_head;
};

struct BfmeSlotVector
{
	BfmeSlot *m_begin;
	BfmeSlot *m_end;
	BfmeSlot *m_capacity;
};

struct BfmeMemberNode
{
	BfmeMemberNode *m_next;
	BfmeMemberNode *m_previous;
	Object *m_value;
};

struct BfmeRankNode
{
	BfmeRankNode *m_next;
	BfmeRankNode *m_previous;
	Int m_value;
};

struct BfmeModuleData
{
	char m_pad[ 0x24c ];
	BfmeRankNode *m_ranksThatStopAdvance;
};

struct BfmeMemberState
{
	char m_body[ 0x1c ];
};

class Rva00240C50HordeContain
{
public:
	Bool rva00240c50();

private:
	char m_head[ 4 ];
	BfmeModuleData *m_moduleData;
	char m_pad08[ 0x30 ];
	BfmeMemberNode *m_members;
	char m_pad3c[ 0xe4 ];
	BfmeSubDSU m_memberIndices;
	BfmeSlot *m_slots;
	BfmeSlot *m_slotsEnd;
	BfmeSlot *m_slotsCapacity;
	BfmeRandomNode *m_randomList;
	char m_pad13c[ 0x9c ];
	BfmeMemberState *m_memberStates;
};

#pragma comment(linker, "/alternatename:?erase@BfmeSubDSU@@QAEIABH@Z=?j_0000d517@@YAXXZ")

// ?rva00240c50@Rva00240C50HordeContain@@QAE_NXZ
Bool Rva00240C50HordeContain::rva00240c50()
{
	BfmeRandomNode *randomHead = m_randomList;
	if (randomHead->m_next == randomHead)
		goto fail;

	BfmeRandomNode *bestNode;
	Int selected = (Int)(m_slotsEnd - m_slots);
	BfmeRandomNode *node = randomHead->m_next;

	while (node != randomHead)
	{
		if (node->m_value < selected)
		{
			selected = node->m_value;
			bestNode = node;
		}
		node = node->m_next;
	}

	if (selected >= (Int)(m_slotsEnd - m_slots))
		goto fail;

	Int selectedOffset = selected * 0x10;
	Int selectedKey = *(Int *)((char *)m_slots + selectedOffset);
	Int rankLimit = 0x63;
	BfmeRankNode *rankHead = m_moduleData->m_ranksThatStopAdvance;
	BfmeRankNode *rankNode = rankHead->m_next;
	while (rankNode != rankHead)
	{
		if (rankNode->m_value >= selectedKey)
		{
			rankLimit = rankNode->m_value;
			break;
		}
		rankNode = rankNode->m_next;
	}

	BfmeMemberNode *memberHead = m_members;
	BfmeMemberNode *memberNode = memberHead->m_next;
	Object *bestMember = 0;
	float bestDistance = 100000.0f;
	if (memberNode == memberHead)
		goto fail;

	while (memberNode != memberHead)
	{
		Object *member = memberNode->m_value;
		Int key = member->m_id;
		Int mapped = *(Int *)m_memberIndices.bfmeTwoDSU(
			(void **)&key );

		if (mapped > selected)
		{
			BfmeSlot *slot = m_slots + mapped;
			if (slot->m_key <= rankLimit && slot->m_key > selectedKey)
			{
				volatile float candidateY = slot->m_y;
				float x = *(float *)((char *)m_slots + selectedOffset + 4) -
					slot->m_x;
				float y = *(float *)((char *)m_slots + selectedOffset + 8) -
					candidateY;
				float distance = x * x + y * y;
				if (distance < bestDistance)
				{
					bestDistance = distance;
					rankLimit = slot->m_key;
					bestMember = member;
				}
			}
		}
		memberNode = memberNode->m_next;
	}

	if (bestMember == 0)
		goto fail;

	Int key = bestMember->m_id;
	Int mapped = *(Int *)m_memberIndices.bfmeTwoDSU(
		(void **)&key );
	m_memberStates[mapped].m_body[ 0x10 ] = 0;
	m_memberIndices.erase( key );
	key = bestMember->m_id;
	*m_memberIndices.bfmeTwoDSU( (void **)&key ) = (void *)selected;
	m_memberStates[selected].m_body[ 0x10 ] = 1;

	BfmeRandomNode *next = bestNode->m_next;
	BfmeRandomNode *previous = bestNode->m_previous;
	previous->m_next = next;
	next->m_previous = previous;
	_STL::__node_alloc<true, 0>::_M_deallocate( bestNode, 0x0c );

	BfmeRandomNode *inserted = (BfmeRandomNode *)
		_STL::__new_alloc::allocate( 0x0c );
	inserted->m_value = mapped;
	inserted->m_next = m_randomList;
	inserted->m_previous = m_randomList->m_previous;
	inserted->m_previous->m_next = inserted;
	m_randomList->m_previous = inserted;
	*((unsigned char *)this + 0xe8) = 1;
	return true;

fail:
	return false;
}
