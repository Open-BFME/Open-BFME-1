// ?ignoreObstacle@AIUpdateInterface@@QAEXPBVObject@@@Z
// partial score=0.76 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/STLport-4.5.3/stlport
// stlport
#include <hash_map>
typedef int ObjectID;
static const ObjectID INVALID_ID = 0;

class AsciiString
{
public:
	const char *str() const { return m_data ? m_data + 8 : ""; }
	char *m_data;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	char m_prefix[4];
	const Overridable *m_next;
};

class ThingTemplate : public Overridable
{
public:
	char m_pad08[0x20 - 8];
	AsciiString m_name;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *value = m_template;
		if (value && value->m_next)
			value = reinterpret_cast<const ThingTemplate *>(value->m_next->getFinalOverride());
		return value;
	}
	const ObjectID getID() const { return m_id; }

	char m_prefix[4];
	ThingTemplate *m_template;
	char m_pad08[0x74 - 8];
	ObjectID m_id;
};

typedef void (__cdecl *CritterLog)(void *, const char *, ...);
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

class ObjectLookup
{
public:
	__declspec(noinline) Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_ID)
			return 0;
		ObjectHash::iterator it = m_objects.find(id);
		if (it == m_objects.end())
			return 0;
		return (*it).second;
	}
private:
	typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectHash;
	char m_pad[0xB0];
	ObjectHash m_objects;
};
extern ObjectLookup *TheGameLogic;

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
	char m_prefix[8];
	Object *m_object;
	char m_pad0c[0x164 - 0x0c];
	ObjectID m_ignoreObstacleID;
};

void AIUpdateInterface::ignoreObstacle(const Object *obj)
{
	if (g_012F0239)
	{
		if (obj)
		{
			if (g_012ED4FC)
				((CritterLog)j_0003a17a)(g_012ED4FC,
					"  CritterDesync - Critter %s(%d) set to ignore %s(%d)",
					m_object->getTemplate()->m_name.str(), m_object->getID(),
					obj->getTemplate()->m_name.str(), obj->getID());
		}
		else
		{
			Object *old = TheGameLogic->findObjectByID(m_ignoreObstacleID);
			if (old)
			{
				if (g_012ED4FC)
					((CritterLog)j_0003a17a)(g_012ED4FC,
						"  CritterDesync - Critter %s(%d) set to ignore NOTHING. Was previously ignoring %s(%d)",
						m_object->getTemplate()->m_name.str(), m_object->getID(),
						obj->getTemplate()->m_name.str(), obj->getID(),
						old->getTemplate()->m_name.str(), old->getID());
			}
			else
			{
				void *sink = g_012ED4FC;
				if (sink)
					((CritterLog)j_0003a17a)(sink,
						"  CritterDesync - Critter %s(%d) set to ignore NOTHING. Was previously ignoring NOTHING",
						m_object->getTemplate()->m_name.str(), m_object->getID(),
						obj->getTemplate()->m_name.str(), obj->getID());
			}
		}
	}
	m_ignoreObstacleID = obj ? obj->getID() : INVALID_ID;
}
