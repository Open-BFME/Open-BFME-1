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

// Retail's free-list head at 0x013387CC is the global this TU spells
// Rva008D2950Head; Rva008D29A0Link.cpp defines it as ?g_rva008D29A0, a
// Rva008D29A0*. Only the pointer value is used here, so the defining name is
// referenced by its own class name (forward declared, never defined here).
class Rva008D29A0;
extern Rva008D29A0 *g_rva008D29A0;
// Both retail loads (RVA 008A4CDE and 008A4D3E) read VA 01337810,
// the GC-root registry pointer defined and data-verified in Apt.cpp.
// AptBooleanCreate uses this same canonical four-byte provider.
extern Rva00899560Pool *g_rva01337810GcRoots;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
// These vftables are emitted by Rva00899560AptValueCtor.cpp and
// Rva008A4C00AptFloatValueCtor.cpp at VAs 0x01135D68 and 0x01136698.
extern "C" const char __identifier("??_7Rva00899560Value@@6B@")[];
extern "C" const char __identifier("??_7Rva008A4C00Value@@6B@")[];

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
	AptFloat *object = (AptFloat *)g_rva008D29A0;

	if (object != 0)
	{
		g_rva008D29A0 = (Rva008D29A0 *)object->m_next;
		g_rva01337810GcRoots->addPooled((Rva008D2950Node *)object);
		object->m_value = value;
		return object;
	}

	object = (AptFloat *)Rva008C5D70Alloc(12);

	if (object != 0)
	{
		*(void **)object = (void *)__identifier("??_7Rva00899560Value@@6B@");
		object->m_flags = (object->m_flags & 0xf0008006) | 0x40008006;
		g_rva01337810GcRoots->addPooled((Rva008D2950Node *)object);
		*(void **)object = (void *)__identifier("??_7Rva008A4C00Value@@6B@");
		object->m_value = value;
		return object;
	}

	return 0;
}
