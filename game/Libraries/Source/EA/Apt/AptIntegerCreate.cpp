// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// EA Apt integer factory.  Its callers are the named integer-producing Apt
// handlers, and the body is the pooled Apt value constructor at 0x008A11E0.

#pragma comment(linker, "/alternatename:?d_008a11e0@@YAXXZ=?Create@AptInteger@@SAPAV1@H@Z")

struct Rva008D2A30Node
{
	void *m_vtable;
	unsigned int m_flags;
	union
	{
		Rva008D2A30Node *m_next;
		int m_value;
	};
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	Rva008D2A30Node **m_items;

	__forceinline void addPooled(Rva008D2A30Node *node)
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

// Retail AptInteger::Create reads the adjacent pool head at 0x013387D0, which is
// the defining Rva008D2A10 list (game/GameEngine/Source/Common/Rva008D2A10Link.cpp);
// it has no header, so forward-declare it and spell the reference with its
// defining type.  AptBoolean and the Rva008D2A30 chain use the distinct
// 0x013387D4 head.
class Rva008D2A10;
extern Rva008D2A10 *g_rva008D2A10;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern "C" const void *bfmeVftAptValue[];
#pragma comment(linker, "/alternatename:_bfmeVftAptValue=??_7AptValue@@6B@")
extern "C" const void *bfmeVftAptInteger[];
#pragma comment(linker, "/alternatename:_bfmeVftAptInteger=??_7AptInteger@@6B@")
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);

class AptValue
{
public:
	virtual ~AptValue();
	unsigned int m_flags;
};

class AptInteger : public AptValue
{
public:
	static AptInteger *Create(int value);

	union
	{
		AptInteger *m_next;
		int m_value;
	};
};

AptInteger *AptInteger::Create(int value)
{
	AptInteger *object = (AptInteger *)g_rva008D2A10;

	if (object != 0)
	{
		g_rva008D2A10 = (Rva008D2A10 *)object->m_next;
		g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
		object->m_value = value;
		return object;
	}

	object = (AptInteger *)Rva008C5D70Alloc(12);

	if (object != 0)
	{
		*(void **)object = (void *)bfmeVftAptValue;
		object->m_flags = (object->m_flags & 0xf0008007) | 0x40008007;
		g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
		*(void **)object = (void *)bfmeVftAptInteger;
		object->m_value = value;
		return object;
	}

	return 0;
}
