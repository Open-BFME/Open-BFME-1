// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ze

struct lua_State;
struct Rva00990030Range;

unsigned Rva00990030Lookup(Rva00990030Range *, int);
extern "C" const char *lua_tostring(lua_State *, int);

struct BfmeListAllocator
{
	unsigned char m_data;
};

struct BfmeListNode
{
	BfmeListNode *m_next;
	BfmeListNode *m_previous;
	int m_value;
};

void *callJ3775e(const char *eventName);

struct BfmeCallJ19
{
	void invoke();
};

struct BfmeCallJ131
{
	void invoke();
};

struct BfmeCallJ167
{
	void invoke(BfmeListAllocator *allocator);
};

struct BfmeCallJE68
{
	void invoke();
};

struct BfmeDelayedLuaEvent
{
	void setFromLua(lua_State *state, int index);

	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();

	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

struct BfmeListInt
{
	void *m_node;

	BfmeListInt(BfmeListAllocator *allocator)
	{
		reinterpret_cast<BfmeCallJ167 *>(this)->invoke(allocator);
	}

	~BfmeListInt()
	{
		reinterpret_cast<BfmeCallJE68 *>(this)->invoke();
	}
};

#define SLOT(N) virtual int slot##N() = 0

class HordeContainInterface
{
public:
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25); SLOT(26); SLOT(27); SLOT(28); SLOT(29); SLOT(30); SLOT(31);
	SLOT(32); SLOT(33); SLOT(34); SLOT(35); SLOT(36); SLOT(37); SLOT(38); SLOT(39);
	SLOT(40); SLOT(41); SLOT(42); SLOT(43); SLOT(44); SLOT(45); SLOT(46); SLOT(47);
	SLOT(48); SLOT(49); SLOT(50); SLOT(51); SLOT(52); SLOT(53); SLOT(54); SLOT(55);
	SLOT(56); SLOT(57); SLOT(58); SLOT(59);
	virtual void getMemberIDs(BfmeListInt *memberIDs) = 0;
};

class ContainModuleInterface
{
public:
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25);
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

#undef SLOT

class Object
{
private:
	unsigned char m_prefix[0x1fc];

public:
	ContainModuleInterface *m_contain;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

struct LuaDrawableState
{
	unsigned char m_data[0x78];
};

extern LuaDrawableState *g_obj12F060C;
struct BfmeCallJ63
{
	void *invoke(void *event);
};

struct BfmeCallJ3D
{
	void invoke(void *event, int objectID, BfmeDelayedLuaEventList *eventList);
};

// The Lua registration at 0x002EC990 binds this body to
// HordeBroadcastEventToMembers.
int HordeBroadcastEventToMembers(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup(reinterpret_cast<Rva00990030Range *>(state), 1);
	if (objectID == 0)
		return 0;

	Object *object = TheGameLogic->findObjectByID(objectID);
	if (object == 0 || object->m_contain == 0)
		return 0;

	HordeContainInterface *horde = object->m_contain->getHordeContainInterface();
	if (horde != 0)
	{
		BfmeDelayedLuaEventList eventList;
		const char *eventName = lua_tostring(state, 2);
		if (eventName == 0)
			return 0;

		void *event = callJ3775e(eventName);
		void *eventData = reinterpret_cast<BfmeCallJ63 *>(g_obj12F060C)->invoke(event);
		if (eventData != 0)
		{
			eventList.m_events[0].setFromLua(state, 3);
			BfmeListAllocator allocator;
			BfmeListInt memberIDs(&allocator);
			horde->getMemberIDs(&memberIDs);

			BfmeListNode *sentinel = static_cast<BfmeListNode *>(memberIDs.m_node);
			for (BfmeListNode *node = sentinel->m_next; node != sentinel; node = node->m_next)
			{
				int memberID = node->m_value;
				reinterpret_cast<BfmeCallJ3D *>(g_obj12F060C)->invoke(eventData, memberID, &eventList);
			}
		}
	}

	return 0;
}
