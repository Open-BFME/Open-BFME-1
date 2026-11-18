// ?rva001F1620@BezierProjectileBehavior@@QAEX_N@Z
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB /Igame/Libraries/Include
// Evidence: targets/game/reverse/identity_evidence/001f1620-mask-scope-recovery.md
#include <string.h>

#include "../../../../Include/Common/ScalarTypes.h"


#include <Lib/Coord3D.h>

#include "../../../../Include/Common/Enums/PathfindLayerEnum.h"




enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

#include "../../../../Include/Common/Enums/DeathType.h"




template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}
	BitFlags(int word, unsigned bits)
	{
		memset(m_bits, 0, sizeof(m_bits));
		m_bits[word] |= bits;
	}

	UnsignedInt test(int i) const { return m_bits[i >> 5] & (1U << (i & 31)); }
	void set(int i) { m_bits[i >> 5] |= 1U << (i & 31); }
	UnsignedInt m_bits[(NUM_BITS + 31) / 32];
};

typedef BitFlags<304> ModelConditionFlags;
typedef BitFlags<86> ObjectStatusMaskType;

class Object;

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip);
};

extern TerrainLogic *TheTerrainLogic;


extern void j_000095ed();

class Object
{
public:
	void setLayer(PathfindLayerEnum layer);
	void setPosition(const Coord3D *position);
	// The canonical 320-bit signature conflicts with the decoded 304-bit complement.
	void clearAndSetModelConditionFlags001C7720(const ModelConditionFlags &clear,
        const ModelConditionFlags &set)
    {
        typedef void (Object::*Update)(const ModelConditionFlags &, const ModelConditionFlags &);
        union { void (*fn)(); Update call; } route = {j_000095ed};
        (this->*route.call)(clear,set);
    }
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void notifyModelConditionChanged();
	void kill(DamageType damage, DeathType death);

	char m_pad00[0x38];
	volatile Coord3D m_position;
	char m_pad44[0xCC];
	ModelConditionFlags m_conditionWords;
	char m_pad138[0xCC];
	void *m_ai;
};

class BezierProjectileBehaviorModuleData
{
public:
	char m_pad00[0x19];
	Bool m_killInsteadOfDestroy;
	char m_pad1a[0x1e];
	UnsignedInt m_aiCommand;
};

struct BezierPathPod
{
	int m_words[3];
};

struct RandomAccessIteratorTag
{
};

// Only the links are interpreted; retail frees a twelve-byte node.
struct ListNode
{
	ListNode *m_next;
	ListNode *m_previous;
};

extern void j_00014d7b();
typedef BezierPathPod *(__cdecl *BezierPathCopy001F1620)(BezierPathPod *, BezierPathPod *, BezierPathPod *, const RandomAccessIteratorTag &, int *);
// ?copyBezierPath@@YAPAUBezierPathPod@@PAU1@00ABURandomAccessIteratorTag@@PAH@Z absent-from-retail
static inline BezierPathPod *copyBezierPath(BezierPathPod *first, BezierPathPod *last,
    BezierPathPod *result, const RandomAccessIteratorTag &tag, int *distance)
{
    union { void (*fn)(); BezierPathCopy001F1620 call; } route = {j_00014d7b};
    return route.call(first, last, result, tag, distance);
}

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

class BfmeInnerCPB
{
public:
	void bfmeOneCPB(int one, int two);
};

enum CommandSourceType { rva001F1620Source = 2 };

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType commandSource);
};

class BezierProjectileBehavior
{
public:
	void rva001F1620(Bool flag);
	// ?clearLinks@BezierProjectileBehavior@@QAEXXZ absent-from-retail
	void clearLinks() { m_list->m_next = m_list; m_list->m_previous = m_list; }


	char m_pad00[0x04];
	BezierProjectileBehaviorModuleData *m_moduleData;
	Object *m_object;
	char m_pad0c[0x38];
	BezierPathPod *m_pathBegin;
	BezierPathPod *m_pathEnd;
	char m_pad4c[0x24];
	volatile int m_unknown70;
	char m_pad74[0x04];
	volatile int m_packetCounter;
	ListNode *m_list;
};

// ?rva001F1620@BezierProjectileBehavior@@QAEX_N@Z
void BezierProjectileBehavior::rva001F1620(Bool)
{
	Object *object = m_object;
	Coord3D position;
	position.x = object->m_position.x;
	position.y = object->m_position.y;
	position.z = object->m_position.z + 10.0f;

	PathfindLayerEnum layer =
		TheTerrainLogic->getLayerForDestination(object, &position);
	object->setLayer(layer);
	position.z = TheTerrainLogic->getLayerHeight(position.x, position.y,
		layer, 0, true);
	object->setPosition(&position);

	RandomAccessIteratorTag tag;
	BezierPathPod *begin = m_pathBegin;
	BezierPathPod *end = m_pathEnd;
	*(BezierPathPod * volatile *)&m_pathEnd =
		copyBezierPath(end, end, begin, tag, 0);
	m_unknown70 = 0;
	m_packetCounter = 0;
	*(volatile int *)((char *)this + 0x28) = 0;

	ListNode *list = *(ListNode * volatile *)((char *)this + 0x7c);
	ListNode *node = list->m_next;
	while (node != list)
	{
		ListNode *current = node;
		node = node->m_next;
		bfmeDeallocate(current, 0x0c);
		list = *(ListNode * volatile *)((char *)this + 0x7c);
	}
	clearLinks();
	{
		const ModelConditionFlags set(4, 0x30000);
		ModelConditionFlags clear;
		object->clearAndSetModelConditionFlags001C7720(set, clear);
	}

	BezierProjectileBehaviorModuleData *data = m_moduleData;
	if (data->m_killInsteadOfDestroy)
	{
		if (object->m_conditionWords.test(115) == 0)
		{
			object->m_conditionWords.set(115);
			object->notifyModelConditionChanged();
		}
		object->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}
	ObjectStatusMaskType status;
	status.m_bits[0] |= 0x20;
	object->setStatus(status, false);

	void *ai = *(void **)((char *)object + 0x204);
	if (data->m_aiCommand > 0)
	{
		if (ai)
			((BfmeInnerCPB *)((char *)ai + 0x20))->bfmeOneCPB(
				data->m_aiCommand, 2);
	}
	else if (ai)
	{
		((AICommandInterface *)((char *)ai + 0x20))->aiIdle(rva001F1620Source);
	}
}
