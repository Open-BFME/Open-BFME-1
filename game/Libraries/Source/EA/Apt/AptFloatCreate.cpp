// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The retail body at 0x008A4CD0 creates pooled Apt float values.
// AptActionInterpreter::aptMax and the Math callbacks call its named
// Rva008A4EA0MakeFloat entry, which the retail REL32 target pins to this body.

#pragma comment(linker, "/alternatename:?d_008a4cd0@@YAXXZ=?Rva008A4EA0MakeFloat@@YAPAVAptValue@@M@Z")

struct Rva008D2950Node
{
	void *m_vtable;
	unsigned int m_flags;
	union
	{
		Rva008D2950Node *m_next;
		float m_value;
	};
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	Rva008D2950Node **m_items;

	__forceinline void addPooled(Rva008D2950Node *node)
	{
		int &count = m_count;
		if (count >= m_capacity)
		{
			node->m_flags &= 0xbfffffff;
		}
		else
		{
			m_items[count] = node;
			count++;
		}
	}
};

extern Rva008D2950Node *Rva008D2950Head;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);

class AptValue
{
public:
	virtual ~AptValue();
	unsigned int m_flags;
};

class AptFloat : public AptValue
{
public:
	union
	{
		AptFloat *m_next;
		float m_value;
	};
};

AptValue * __cdecl Rva008A4EA0MakeFloat(float value)
{
	AptFloat *object = (AptFloat *)Rva008D2950Head;

	if (object != 0)
	{
		Rva008D2950Head = (Rva008D2950Node *)object->m_next;
		g_rva8CD130IdleHook->addPooled((Rva008D2950Node *)object);
		object->m_value = value;
		return object;
	}

	object = (AptFloat *)Rva008C5D70Alloc(12);

	if (object != 0)
	{
		*(void **)object = (void *)0x01135D68;
		object->m_flags = (object->m_flags & 0xf0008006) | 0x40008006;
		g_rva8CD130IdleHook->addPooled((Rva008D2950Node *)object);
		*(void **)object = (void *)0x01136698;
		object->m_value = value;
		return object;
	}

	return 0;
}
