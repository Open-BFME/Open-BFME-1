// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 0x00892F00 -- Rva00893030Manager::rva00892F00
//
// Receiver.  The sole retail caller, 0x00894660+0x3A, loads ECX from
// ?g_rva00893030Manager@@3PAVRva00893030Manager@@A (0x013377D4) before the
// call at +0x4B, so this is a __thiscall member of that manager.  The body
// walks the manager's singly linked list from the head at +0x00 through the
// {payload,next} node that ?find008958D0@Rva00893030Manager (0x008958D0,
// Rva00893030ManagerFind.cpp) also walks.
//
// Arguments.  The same caller builds `BfmeElemCU[0x60]` with the vector
// constructor iterator (??0BfmeElemCU@@QAE@XZ 0x00892B80, destructor pin
// 0x000463AD) and pushes the array and 0x60; `ret 8` covers both.  The
// count is never read in the release body.
//
// Element.  Each node payload is copied into a refcounted temporary
// (increment 0x00894D80), assigned into the next array slot with a
// self-assignment test (decrement 0x00894D90 / bfmeDropA 0x00895320 on the
// old value, increment on the new one), and the temporary is released.
//
// Shape.  The indexed store `out[i++]` is what makes MSVC strength-reduce to
// a fresh pointer spilled into the dead parameter slot (the redundant
// `mov [esp+0x1c],eax` before the loop); `*out++` omits it.  The self test
// is spelled `&other != this` to get retail's `cmp ecx,esi` operand order.
//
// Method name stays address-derived: the caller is an anonymous ?d_ dump.

class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *value);
};

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

void bfmeDropA(void *value);

class BfmeDropObjectA;

class BfmeElemCU
{
public:
	BfmeElemCU(BfmeDropObjectA *value) : m_value(value)
	{
		if (m_value)
			Rva00894D80Accessor::increment((unsigned int *)m_value);
	}

	~BfmeElemCU()
	{
		if (m_value && Rva00894D90Accessor::decrement((unsigned int *)m_value) == 0)
			bfmeDropA(m_value);
	}

	BfmeElemCU &operator=(const BfmeElemCU &other)
	{
		if (&other != this)
		{
			if (m_value && Rva00894D90Accessor::decrement((unsigned int *)m_value) == 0)
				bfmeDropA(m_value);
			m_value = other.m_value;
			if (m_value)
				Rva00894D80Accessor::increment((unsigned int *)m_value);
		}
		return *this;
	}

	BfmeDropObjectA *m_value;
};

class Rva00893030Node
{
public:
	BfmeDropObjectA *m_object;	// +0x00
	Rva00893030Node *m_next;	// +0x04
};

class Rva00893030Manager
{
public:
	void rva00892F00(BfmeElemCU *out, int count);

private:
	Rva00893030Node *m_head;	// +0x00
};

void Rva00893030Manager::rva00892F00(BfmeElemCU *out, int count)
{
	int i = 0;
	for (Rva00893030Node *n = m_head; n; n = n->m_next)
		out[i++] = BfmeElemCU(n->m_object);
}
