// ?rva008B2EA0Create@@YAPAVRva008B2EA0Node@@XZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct AptStringBlock
{
	unsigned short m_refs;
	unsigned short m_length;
};

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

class Rva008A9B00
{
public:
	void *operator new(unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}

	void operator delete(void *) {}

	Rva008A9B00();

	void *m_vtable;
	unsigned int m_flags;
	AptStringBlock *m_string;
	Rva008A9B00 *m_next;
};

struct AptValueRegistry
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(Rva008A9B00 *object)
	{
		int index = m_count;
		int capacity = m_capacity;
		if (index >= capacity)
		{
			object->m_flags &= ~0x40000000u;
			return;
		}
		m_entries[index] = object;
		++m_count;
	}
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned int length);
};

// The shared empty EA string block at 0x012D5298 is defined once, with its
// proven type, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  It is
// named here through a file-local view cast at each use so the DIR32 target is
// the one retail address.
class EAStringC
{
public:
	class StringDataC;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

static inline AptStringBlock *rva012D5298Block()
{
	return (AptStringBlock *)&g_rva012D5298Empty;
}
// Retail 0x01337810: use the existing data owner; retain the local pointee view.
extern struct Rva00899560Pool *g_rva01337810GcRoots;
// Retail 0x01338478: use the existing data owner; retain the local pointee view.
extern struct Rva008C3B60Node *g_rva01338478NodeHead;

class Rva008B2EA0Node;

Rva008B2EA0Node *rva008B2EA0Create()
{
	Rva008A9B00 *object = reinterpret_cast<Rva008A9B00 *>(g_rva01338478NodeHead);
	if (object)
	{
		g_rva01338478NodeHead = reinterpret_cast<Rva008C3B60Node *>(static_cast<Rva008A9B00 *>(object->m_next));
		reinterpret_cast<AptValueRegistry *>(g_rva01337810GcRoots)->addOrClear(object);
		if (object->m_string != rva012D5298Block())
			((BfmeStrVKK *)&object->m_string)->bfmeTruncVKK(0);
	}
	else
	{
		object = new Rva008A9B00;
	}
	return (Rva008B2EA0Node *)object;
}
