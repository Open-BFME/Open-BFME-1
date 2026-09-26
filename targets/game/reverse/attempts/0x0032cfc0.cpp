// ?evaluateTypeSighted@ScriptConditions@@IAE_NPAVParameter@@00@Z
// partial score=0.26 date=2026-09-20
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Byte-matched BFME reconstruction of the TYPE_SIGHTED condition body.
// stlport

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned short PlayerMaskType;
typedef float Real;

class AsciiString
{
public:
	void *m_data;
};

class Parameter;
class Player;
class Object;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_beforeName[0x18];
	AsciiString m_name;
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_beforePosition[0x30];

	Real getVisionRange() const;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(Parameter *parameter) = 0;

	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes();
	Bool isInSet(const AsciiString &objectType) const;
};

class ObjectTypesTemp
{
public:
	ObjectTypes *m_types;

	ObjectTypesTemp();
	~ObjectTypesTemp()
	{
		if (m_types)
			delete m_types;
	}
};

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *memory, unsigned int size);
};
}

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);

	volatile unsigned int m_vptr;
	PartitionFilter *m_next;
};

class Rva001DCBB0Filter : public PartitionFilter
{
public:
	Rva001DCBB0Filter(Object *object, UnsignedByte match);
	~Rva001DCBB0Filter() { m_vptr = 0x01083B5C; }

	Player *m_player;
	UnsignedByte m_match;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object)
	{
		m_next = 0;
		m_vptr = 0x01085DD0;
		m_object = object;
	}
	~Rva0025ED50ObjectFilter() { m_vptr = 0x01083B5C; }

	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter()
	{
		m_next = 0;
		m_vptr = 0x01083B80;
	}
	~Rva0025ED50RootFilter() { m_vptr = 0x01083B5C; }
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
	{
		m_next = 0;
		m_vptr = 0x0109688C;
		m_player = player;
		m_match = match;
	}
	~PartitionFilterPlayer() { m_vptr = 0x01083B5C; }

	const Player *m_player;
	Bool m_match;
};

struct Rva0032CFC0Entry
{
	Object *object;
	unsigned unknown04;
};

class WideResultHandle
{
	public:
	Rva0032CFC0Entry *m_begin;
	Rva0032CFC0Entry *m_end;
	Rva0032CFC0Entry *m_endOfStorage;
	Rva0032CFC0Entry *m_cursor;
	unsigned int m_refCount;
};

class BfmeWideResult
{
public:
	WideResultHandle *m_value;

	Object *next(Object *&object)
	{
		Rva0032CFC0Entry *current = m_value->m_cursor;
		Rva0032CFC0Entry *end = m_value->m_end;
		if (current == end)
			return 0;
		object = (current++)->object;
		m_value->m_cursor = current;
		return object;
	}
	__forceinline ~BfmeWideResult()
	{
		WideResultHandle *value = m_value;
		if (--value->m_refCount == 0)
		{
			void *begin = value->m_begin;
			if (begin)
			{
				int size = (int)((char *)value->m_endOfStorage -
					(char *)begin);
				size = (size >> 3) << 3;
				if (size > 0x80)
					::operator delete(begin);
				else
					_STL::__node_alloc<true, 0>::_M_deallocate(begin, size);
			}
			::operator delete(value);
		}
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

class ScriptConditions
{
protected:
	Bool evaluateTypeSighted(Parameter *itemParameter,
		Parameter *playerParameter, Parameter *typeParameter);
	static void objectTypesFromParam(Parameter *, ObjectTypes *);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern BfmeWideForwardC *ThePartitionManager;

Bool ScriptConditions::evaluateTypeSighted(Parameter *itemParameter,
	Parameter *playerParameter, Parameter * volatile typeParameter)
{
	Object *object = TheScriptEngine->getUnitNamed(itemParameter);
	if (!object)
		return false;

	PlayerMaskType playerMask =
		TheScriptEngine->unidentified_0034DB40(playerParameter);
	if (!playerMask)
		return false;

	while (playerMask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		ObjectTypesTemp types;
		objectTypesFromParam(*(Parameter * volatile *)&typeParameter,
			types.m_types);

		Rva001DCBB0Filter relationshipFilter(object, 0);
		Rva0025ED50ObjectFilter objectFilter(object);
		Rva0025ED50RootFilter rootFilter;
		PartitionFilterPlayer playerFilter(player, true);

		Real visionRange = object->getVisionRange();
		int visionRangeBits = *(int *)&visionRange;
		BfmeWideResult iterator =
			ThePartitionManager->bfmeForwardWideC(
				(int)((char *)object + 0x38),
				visionRangeBits, 0,
				(int)playerFilter.link(rootFilter.link(
					relationshipFilter.link(&objectFilter))), (int)player);

		Object *other;
		while (iterator.next(other))
		{
			ThingTemplate *thingTemplate = other->m_template;
			if (thingTemplate && thingTemplate->m_nextOverride)
				thingTemplate = (ThingTemplate *)
					thingTemplate->m_nextOverride->getFinalOverride();
			if (types.m_types->isInSet(thingTemplate->m_name))
				return true;
		}
	}

	return false;
}
