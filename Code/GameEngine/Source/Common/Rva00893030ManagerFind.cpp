// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 0x008958D0 -- Rva00893030Manager::find008958D0
//
// Identity: the callers at 0x00895A00 and 0x00895D30 both load their
// Rva00893030Manager receiver into ECX before the call; the matched remove
// body at 0x00895200 and the matched destructor at 0x00895260 witness the
// manager's singly linked list head at +0x00 and the {object,next} node.
// BfmeDropObjectA (refcount at +0x00, 0x18 bytes) is witnessed by the landed
// Rva00895430RefRangeCopy.cpp / BfmeCopyBackVPD.cpp bodies.  The method name
// stays address-derived: no caller, vtable slot or literal names it.
//
// ABI: this is NOT a void out-parameter lookup.  It returns a one-pointer
// refcounted handle BY VALUE -- the hidden sret pointer is the first stack
// argument (ret 8 = sret + key) and MSVC must leave it in EAX on every exit,
// which is exactly why retail reloads [esp+0x18] into EAX in both exit blocks
// and falls back to ECX for the refcount scratch.  The handle's destructor is
// what puts the dead `mov dword ptr [esp+0x10], 0` cleanup flag in the
// prologue.  The same by-value handle shape is witnessed on the caller side
// at 0x00895A00 and by the landed BfmeHolderDB in Bfme5ThirtyFour.cpp.
extern "C" int memcmp(const void *a, const void *b, unsigned int n);

#pragma intrinsic(memcmp)

struct BfmeStringData3AF0
{
public:
	unsigned short m_word0;
	unsigned short m_length;
	unsigned short m_word4;
	unsigned short m_word6;
	char m_data[1];
};

class BfmeStrVKI
{
public:
	BfmeStringData3AF0 *m_data;
};

class BfmeString3AF0
{
public:
	BfmeStringData3AF0 *m_data;
};

class BfmeDropObjectA
{
public:
	int m_refCount;						// +0x00
	BfmeString3AF0 m_string;				// +0x04
};

class Rva00893030Node
{
public:
	BfmeDropObjectA *m_object;				// +0x00
	Rva00893030Node *m_next;				// +0x04
};

__forceinline BfmeStringData3AF0 *loadStringData008958D0(
	BfmeStringData3AF0 *volatile *pp)
{
	return *pp;
}

class RefHandle008958D0
{
public:
	RefHandle008958D0(void)
	{
		m_object = 0;
	}

	RefHandle008958D0(BfmeDropObjectA *o)
	{
		m_object = o;

		if (o != 0)
			++o->m_refCount;
	}

	~RefHandle008958D0(void)
	{
		if (m_object != 0)
			--m_object->m_refCount;
	}

	BfmeDropObjectA *m_object;				// +0x00
};

class Rva00893030Manager
{
public:
	RefHandle008958D0 find008958D0(BfmeStrVKI *key);

private:
	Rva00893030Node *m_head;				// +0x00
};

// ?find008958D0@Rva00893030Manager@@QAE?AVRefHandle008958D0@@PAVBfmeStrVKI@@@Z
RefHandle008958D0 Rva00893030Manager::find008958D0(BfmeStrVKI *key)
{
	Rva00893030Node *n = m_head;

	if (n != 0)
	{
		BfmeStringData3AF0 *k = key->m_data;
		int len = k->m_length;

		do
		{
			BfmeStringData3AF0 *s = loadStringData008958D0(
				&n->m_object->m_string.m_data);

			if (len == s->m_length)
			{
				if (k == s || memcmp(k->m_data, s->m_data, len) == 0)
					return RefHandle008958D0(n->m_object);
			}

			n = n->m_next;
		}
		while (n != 0);
	}

	return RefHandle008958D0();
}
