// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?getMetaMapRec@MetaMap@@IAEPAVMetaMapRec@@W4Type@GameMessage@@@Z: Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp
// Lift the MetaMap::getMetaMapRec __emit thunk to clean C++.
//
// Verbatim Zero Hour MetaEvent.cpp: look for an existing record for this message
// type, and failing that allocate one, fill in the defaults and push it on the
// front of the list.
//
// Retail pins the record layout: m_next at +0x00, m_meta +0x04, m_key +0x08,
// m_transition +0x0C, m_modState +0x10, m_usableIn +0x14, m_category +0x18 and
// the two UnicodeStrings at +0x1C/+0x20, giving the 0x24 byte allocation. The
// list head lives at MetaMap+0x08, and CATEGORY_MISC is 6 -- the one non-zero
// default, read straight off the store.
//
// ZH allocates with newInstance(); retail calls plain operator new, so the null
// check and the two string constructors sit inside the allocation branch while
// the field assignments follow the merge. clear() on a UnicodeString folds with
// the wide-string destructor body, which is why both calls land on one address.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type { MSG_INVALID = 0 };
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(void) : m_data(0) {}

	void clear(void);										///< retail body at 0x008881D0

private:
	void *m_data;
};

enum { MK_NONE = 0 };
enum MappableKeyTransition { DOWN = 0 };
enum MappableKeyModState { NONE = 0 };
enum CommandUsableInType { COMMANDUSABLE_NONE = 0 };
enum MetaMapCategory { CATEGORY_MISC = 6 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h
class MetaMapRec
{
public:
	MetaMapRec *m_next;										///< retail this+0x00
	Int m_meta;												///< retail this+0x04
	Int m_key;												///< retail this+0x08
	Int m_transition;										///< retail this+0x0C
	Int m_modState;											///< retail this+0x10
	Int m_usableIn;											///< retail this+0x14
	Int m_category;											///< retail this+0x18
	UnicodeString m_description;							///< retail this+0x1C
	UnicodeString m_displayName;							///< retail this+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h
class MetaMap
{
protected:
	MetaMapRec *getMetaMapRec(GameMessage::Type t);

private:
	unsigned char m_unreconstructed_00[8];
	MetaMapRec *m_metaMaps;									///< retail this+0x08
};

// ?getMetaMapRec@MetaMap@@IAEPAVMetaMapRec@@W4Type@GameMessage@@@Z
MetaMapRec *MetaMap::getMetaMapRec(GameMessage::Type t)
{
	for (MetaMapRec *map = m_metaMaps; map; map = map->m_next)
	{
		if (map->m_meta == t)
			return map;
	}

	// not found.. create a new one.
	MetaMapRec *m = new MetaMapRec;
	m->m_meta = t;
	m->m_key = MK_NONE;
	m->m_transition = DOWN;
	m->m_modState = NONE;
	m->m_usableIn = COMMANDUSABLE_NONE;
	m->m_category = CATEGORY_MISC;
	m->m_description.clear();
	m->m_displayName.clear();
	m->m_next = m_metaMaps;
	m_metaMaps = m;

	return m;
}
