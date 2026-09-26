// ?scan@Rva0023FED0MemberScanBase@@QAEXPAV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@00@Z
// partial score=0.16 date=2026-09-21
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Opaque member-list scan: walks an _STL::list<Object *> embedded at this-0xAC
// (a secondary-base this-pointer; no witnessed offset ties this to Object or Team,
// so identity stays address-derived) and buckets each member's Object::m_id
// (witnessed Object+0x74, confidence 1.00) into one of three caller-supplied
// _STL::vector<ObjectID> outputs, based on the still-unresolved comparison
// helper at retail 0x003FD7D0 (called only for byte-shape/ABI; its own body
// remains a dump) and Path::bfmeHasMissingWaypoint (matched,
// PathHasMissingWaypoint.cpp) plus TheTerrainLogic::getWaypointByID (vtable
// slot 0x80, same TerrainLogic shape as PathHasMissingWaypoint.cpp).
//
// Derived from python3 tools/dis_retail.py 0x0023FED0 316.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ObjectID { INVALID_OBJECT_ID = 0 };

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WaypointID;
static const WaypointID INVALID_WAYPOINT_ID = 0x7fffffff;

class TerrainLogic
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot01();
	virtual void bfmeSlot02();
	virtual void bfmeSlot03();
	virtual void bfmeSlot04();
	virtual void bfmeSlot05();
	virtual void bfmeSlot06();
	virtual void bfmeSlot07();
	virtual void bfmeSlot08();
	virtual void bfmeSlot09();
	virtual void bfmeSlot10();
	virtual void bfmeSlot11();
	virtual void bfmeSlot12();
	virtual void bfmeSlot13();
	virtual void bfmeSlot14();
	virtual void bfmeSlot15();
	virtual void bfmeSlot16();
	virtual void bfmeSlot17();
	virtual void bfmeSlot18();
	virtual void bfmeSlot19();
	virtual void bfmeSlot20();
	virtual void bfmeSlot21();
	virtual void bfmeSlot22();
	virtual void bfmeSlot23();
	virtual void bfmeSlot24();
	virtual void bfmeSlot25();
	virtual void bfmeSlot26();
	virtual void bfmeSlot27();
	virtual void bfmeSlot28();
	virtual void bfmeSlot29();
	virtual void bfmeSlot30();
	virtual void bfmeSlot31();
	virtual void *getWaypointByID(WaypointID waypointID);
};

extern TerrainLogic *TheTerrainLogic;

class Object;

// Output of the unresolved comparison helper at 0x003FD7D0. Only the fields this
// body reads are given real names; the two unread dwords keep the buffer's proven
// 36-byte size (frame slots esp+0x14..esp+0x37 in the retail disassembly).
struct Rva0023FED0CompareOut
{
	UnsignedInt m_unused0;
	float m_posA[3];
	float m_posB[3];
	UnsignedInt m_unused2;
	WaypointID m_waypointId;
};

class Path
{
public:
	Bool bfmeHasMissingWaypoint(void) const;
	// retail 0x003FD7D0, still an unresolved dump; called here only for its
	// proven __thiscall(Path*, Object*, void*, CompareOut*, int) shape.
	void rva0023fed0Compare(Object *member, void *goalField, Rva0023FED0CompareOut *out, int zero) const;
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_pad0[0x74];
	ObjectID m_id;               // Object+0x74, layout_witness confidence 1.00
	unsigned char m_pad1[0x204 - 0x74 - 4];
	void *m_updateCache;         // Object+0x204, not witnessed; address-derived only
};

// STLport's list<T> header node: {next, prev, data}; the list object itself
// doubles as the sentinel, so list.end() is the list object's own address.
struct Rva0023FED0Node
{
	Rva0023FED0Node *m_next;
	Rva0023FED0Node *m_prev;
	Object *m_data;
};

class Rva0023FED0MemberScanBase
{
public:
	void scan(_STL::vector<ObjectID> *needRepath, _STL::vector<ObjectID> *lookupFailed, _STL::vector<ObjectID> *ok);

private:
	unsigned char m_pad[4];
};

static Rva0023FED0Node *sentinelOf(Rva0023FED0MemberScanBase *self)
{
	return *reinterpret_cast<Rva0023FED0Node **>(reinterpret_cast<char *>(self) - 0xAC);
}

void Rva0023FED0MemberScanBase::scan(_STL::vector<ObjectID> *needRepath, _STL::vector<ObjectID> *lookupFailed, _STL::vector<ObjectID> *ok)
{
	Rva0023FED0Node *sentinel = sentinelOf(this);
	Rva0023FED0Node *node = sentinel->m_next;

	if (node == sentinel)
		return;

	do
	{
		Object *member = node->m_data;
		if (!member)
			goto next;

		char *upd = *reinterpret_cast<char **>(reinterpret_cast<char *>(member) + 0x204);
		if (!upd)
			goto next;

		{
			Path *pathPtr = *reinterpret_cast<Path **>(upd + 0x140);
			ObjectID id = member->getID();

			if (!pathPtr)
			{
				ok->push_back(id);
				goto next;
			}

			void *goalField = *reinterpret_cast<void **>(upd + 0x1cc);
			Rva0023FED0CompareOut out;
			pathPtr->rva0023fed0Compare(member, goalField, &out, 0);

			if (out.m_posA[0] == out.m_posB[0] && out.m_posA[1] == out.m_posB[1] && out.m_posA[2] == out.m_posB[2])
			{
				ok->push_back(id);
				goto next;
			}

			{
				WaypointID waypointId = out.m_waypointId;
				if (waypointId == INVALID_WAYPOINT_ID || TheTerrainLogic->getWaypointByID(waypointId) != 0)
				{
					if (pathPtr->bfmeHasMissingWaypoint())
						needRepath->push_back(id);
					else
						ok->push_back(id);
				}
				else
				{
					lookupFailed->push_back(id);
				}
			}
		}

	next:
		node = node->m_next;
	} while (node != sentinel);
}
