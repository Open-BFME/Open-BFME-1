// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME: retail 0x00610AF0, 167B. STLport-style copy over a 16-byte
// intrusive-list node. Address-derived identity; no W3DAnimationInfo name
// is inferred from a pre-existing pin.

struct GenNode_00610af0;

struct GenOwner_00610af0
{
	char m_pad[0x98];
	GenNode_00610af0 *m_head;
	GenNode_00610af0 *m_tail;
};

struct GenNode_00610af0
{
	GenOwner_00610af0 *m_owner;
	GenNode_00610af0 *m_prev;
	GenNode_00610af0 *m_next;
	unsigned int m_extra;

	void unlink(void)
	{
		if (m_owner != 0)
		{
			if (m_prev != 0)
				m_prev->m_next = m_next;
			else
				m_owner->m_head = m_next;

			if (m_next != 0)
				m_next->m_prev = m_prev;
			else
				m_owner->m_tail = m_prev;

			m_prev = 0;
			m_next = 0;
		}
	}

	void setOwner(GenOwner_00610af0 *owner)
	{
		m_owner = owner;
		if (owner != 0)
		{
			m_prev = owner->m_tail;
			m_next = 0;
			owner->m_tail = this;
			if (m_prev != 0)
				m_prev->m_next = this;
			else
				m_owner->m_head = this;
		}
	}

	GenNode_00610af0 &operator=(const GenNode_00610af0 &o)
	{
		if (this != &o)
		{
			unlink();
			setOwner(o.m_owner);
		}
		m_extra = o.m_extra;
		return *this;
	}
};

GenNode_00610af0 *gen_copy_00610af0(GenNode_00610af0 *first, GenNode_00610af0 *last, GenNode_00610af0 *result)
{
	for (int n = last - first; n > 0; --n)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}
