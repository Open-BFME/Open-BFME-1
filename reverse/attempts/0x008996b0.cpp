// ?Create@AptBoolean@@SAPAV1@_N@Z
// partial score=0.75 date=2026-09-06
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Create@AptBoolean@@SAPAV1@_N@Z

class AptValue;
class AptBoolean;

struct AptBooleanRegistry
{
	int m_capacity;
	int m_count;
	AptValue **m_entries;

	__forceinline int add(AptValue *value);
};

typedef void *(__cdecl *AptAllocate)(unsigned int);

inline void *operator new(unsigned int, void *place)
{
	return place;
}

#define g_aptBooleanFreeList (*(AptBoolean **)0x013387D4)
#define g_aptBooleanRegistry (*(AptBooleanRegistry **)0x01337810)
#define g_aptAllocate (*(AptAllocate *)0x01337828)

class AptValue
{
public:
	__forceinline AptValue(unsigned int kind)
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008000 | kind;
		flags |= 0x40008000 | kind;
		m_vtable = 0x01135d68;
		m_flags = flags;
		g_aptBooleanRegistry->add(this);
	}

	unsigned int m_vtable;
	unsigned int m_flags;
};

class AptBoolean : public AptValue
{
public:
	static AptBoolean *Create(bool value);
	__forceinline AptBoolean(bool value) : AptValue(5)
	{
		m_vtable = 0x011360a8;
		m_value = value;
	}

	union
	{
		AptBoolean *m_next;
		unsigned char m_value;
	};
};

__forceinline int AptBooleanRegistry::add(AptValue *value)
{
	int index = m_count;
	int capacity = m_capacity;
	if (index >= capacity)
	{
		value->m_flags &= ~0x40000000;
		return 0;
	}
	m_entries[index] = value;
	++m_count;
	return 1;
}

AptBoolean *AptBoolean::Create(bool value)
{
	AptBoolean *object = g_aptBooleanFreeList;
	if (object != 0)
	{
		AptBoolean *next = object->m_next;
		AptBooleanRegistry *registry = g_aptBooleanRegistry;
		g_aptBooleanFreeList = next;
		registry->add(object);
		object->m_value = value;
		return object;
	}

	void *raw = g_aptAllocate(12);
	object = raw != 0 ? new (raw) AptBoolean(value) : 0;
	return object;
}
