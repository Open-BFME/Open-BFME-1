// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /G6 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Include /Iinputs/reference/shims/sweep
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object;
class Player;

class PlayerList
{
public:
	Player *getNthPlayer(Int index);
};

extern PlayerList *ThePlayerList;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *m_next;
};

class PlayerFilter002A1780 : public PartitionFilter
{
public:
	PlayerFilter002A1780(Player *player) : m_08(player) {}
	virtual ~PlayerFilter002A1780() {}
	virtual bool allow(Object *);
	virtual Int getPlayerMask();

	Player *m_08;
};

class ExperienceTracker
{
public:
	Bool gainExpForLevel(Int levels, Bool scale, Bool feedback);
};

struct BfmeWideResultItem
{
	Object *m_object;
	UnsignedInt m_distance;
};

struct BfmeWideResultPayload
{
	std::vector<BfmeWideResultItem> m_items;
	BfmeWideResultItem *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	BfmeWideResultPayload *m_value;

	~BfmeWideResult()
	{
		BfmeWideResultPayload *&payload = m_value;
		--payload->m_refCount;
		if (payload->m_refCount == 0)
			delete payload;
	}

	Object *next()
	{
		if (m_value->m_cursor == m_value->m_items.end())
			return 0;
		BfmeWideResultItem *cursor = m_value->m_cursor;
		Object *object = cursor->m_object;
		m_value->m_cursor = cursor + 1;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int position, Int radius, Int mode,
		Int filter, Int sortMode);
};

extern BfmeWideForwardC *ThePartitionManager;

struct BfmeVec1268
{
public:
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class VictorySystem
{
public:
	void bfmeNotifyCell(UnsignedInt playerIndex, BfmeVec1268 *pos);

private:
	char m_pad00[0x1c];
	Int m_field1c;
	Int m_pad20;
	Int m_playerParameterIndex[16];
};

void VictorySystem::bfmeNotifyCell(UnsignedInt playerIndex, BfmeVec1268 *pos)
{
	if ((m_playerParameterIndex[playerIndex] & 0x80000000) != 0)
		return;

	PlayerFilter002A1780 filter(ThePlayerList->getNthPlayer(playerIndex));
	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		(Int)pos, m_field1c, 1, (Int)&filter, 0);
	BfmeWideResultItem *end = result.m_value->m_items.end();
	BfmeWideResultItem *cursor = result.m_value->m_cursor;
	if (cursor != end)
	{
		Object *object = cursor->m_object;
		++cursor;
		result.m_value->m_cursor = cursor;
		while (object != 0)
		{
			ExperienceTracker *tracker =
				*(ExperienceTracker **)((char *)object + 0x210);
			if (tracker != 0)
				tracker->gainExpForLevel(1, 1, 0);
			end = result.m_value->m_items.end();
			cursor = result.m_value->m_cursor;
			if (cursor == end)
				break;
			object = cursor->m_object;
			++cursor;
			result.m_value->m_cursor = cursor;
		}
	}
}
