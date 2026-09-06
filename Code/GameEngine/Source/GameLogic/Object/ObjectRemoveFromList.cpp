// cl: /O2 /Ob1 /DNDEBUG /MD
// BFME1 retail 0x001BECF0: unlink an Object from the intrusive object list.
// The BFME list carries both head and tail pointers; this is the two-argument
// variant of the one-head Zero Hour donor in Object.cpp.

class Object
{
public:
	void removeFromList(Object **pListTail, Object **pListHead);

private:
	char m_slice_pad[0x88];
	Object *m_prev;
	Object *m_next;
};

void Object::removeFromList(Object **pListTail, Object **pListHead)
{
	if (m_prev)
	{
		m_prev->m_next = m_next;
	}
	else
	{
		*pListHead = m_next;
	}

	if (m_next)
	{
		m_next->m_prev = m_prev;
	}
	else
	{
		*pListTail = m_prev;
	}

	m_next = 0;
	m_prev = 0;
}
