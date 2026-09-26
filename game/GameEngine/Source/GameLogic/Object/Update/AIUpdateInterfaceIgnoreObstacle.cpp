// ?ignoreObstacle@AIUpdateInterface@@QAEXPBVObject@@@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME AIUpdateInterface::ignoreObstacle, RVA 0x002739F0, 523 bytes: ZH store wrapped in CritterDesync logging.
// Thing::m_template is OVERRIDE<ThingTemplate>; its inlined operator* reads through &obj->m_template.
#include "ascii_string.h"

template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

typedef int ObjectID;
static const ObjectID INVALID_ID = 0;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_next)
			return m_next->getFinalOverride();
		return this;
	}
	char m_prefix[4];
	const Overridable *m_next;
};

class ThingTemplate : public Overridable
{
public:
	char m_pad08[0x20 - 8];
	AsciiString m_name;
};

template <class T> class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator*(); }
private:
	const T *m_overridable;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const ObjectID getID() const { return m_id; }

	char m_prefix[4];
	OVERRIDE<ThingTemplate> m_template;
	char m_pad08[0x74 - 8];
	ObjectID m_id;
};

typedef void (__cdecl *CritterLog)(void *, const char *, ...);
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

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
