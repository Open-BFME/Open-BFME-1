// ?rva001F1620@BezierProjectileBehavior@@QAEX_N@Z
// partial score=0.96 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
//
// BezierProjectileBehavior primary-interface reset, retail 0x001F1620,
// 449 bytes.  The caller at 0x001F1CE0 selects this routine after the
// projectile reaches its final path point and the module data requests the
// kill path.

#include <string.h>

typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	UnsignedInt m_bits[(NUM_BITS + 31) / 32];
};

typedef BitFlags<320> ModelConditionFlags;
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
extern volatile float g_bfmeDirectionWeight1285;

class Object
{
public:
	void setLayer(PathfindLayerEnum layer);
	void setPosition(const Coord3D *position);
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void notifyModelConditionChanged();
	void kill(DamageType damage, DeathType death);

	char m_pad00[0x38];
	volatile Coord3D m_position;
	char m_pad44[0xCC];
	UnsignedInt m_conditionWords[10];
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

struct ListNode
{
	ListNode *m_next;
	ListNode *m_previous;
};

BezierPathPod *copyBezierPath(BezierPathPod *first, BezierPathPod *last,
	BezierPathPod *result, const RandomAccessIteratorTag &tag, int *distance);

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

class BfmeInnerCPB
{
public:
	void bfmeOneCPB(int one, int two);
};

class AICommandInterface
{
public:
	void aiIdle(int commandSource);
};

class BezierProjectileBehavior
{
public:
	void rva001F1620(Bool flag);

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
	position.z = object->m_position.z + g_bfmeDirectionWeight1285;

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
	list = *(ListNode * volatile *)((char *)this + 0x7c);
	ModelConditionFlags clear;
	ModelConditionFlags set;
	list->m_next = list;
	list = *(ListNode * volatile *)((char *)this + 0x7c);
	list->m_previous = list;
	set.m_bits[4] = 0x30000;
	object->clearAndSetModelConditionFlags(set, clear);

	BezierProjectileBehaviorModuleData *data = m_moduleData;
	if (data->m_killInsteadOfDestroy)
	{
		if ((object->m_conditionWords[3] & 0x80000) == 0)
		{
			object->m_conditionWords[3] |= 0x80000;
			object->notifyModelConditionChanged();
		}
		object->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
		ObjectStatusMaskType status;
		status.m_bits[0] |= 0x20;
		object->setStatus(status, false);
	}

	void *ai = *(void **)((char *)object + 0x204);
	if (data->m_aiCommand > 0)
	{
		if (ai)
			((BfmeInnerCPB *)((char *)ai + 0x20))->bfmeOneCPB(
				data->m_aiCommand, 2);
	}
	else if (ai)
	{
		((AICommandInterface *)((char *)ai + 0x20))->aiIdle(2);
	}
}
