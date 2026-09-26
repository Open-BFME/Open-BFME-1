// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: U1Sub::_bfme_detach, retail 0x001DA3F0, 63 bytes. The body
// carried only a machine byte-dump row; the ILT pin at 0x0002129C names it, and
// U1Sub::apply at 0x005C21D0 -- already ledgered -- calls it on this before
// taking a new target.
//
// It is the unsplice that matches the splice apply performs: the same list,
// with next at +0x04 and previous at +0x08 in the link and the target's tail at
// +0x98 and head at +0x9C. Each neighbour is repaired, or the target's end
// pointer is moved when there is no neighbour on that side, and the link is
// left with both of its own pointers cleared.
//
// The two clearing stores are written once and appear in both arms of the
// second test, which is this compiler's single-exit shaping.

class U1Sub;

class U1Target
{
public:
	unsigned char m_unmodelled_000[0x98];
	U1Sub *m_tail;						// +0x98
	U1Sub *m_head;						// +0x9C
};

class U1Sub
{
public:
	void _bfme_detach(void);

private:
	U1Target *m_target;					// +0x00
	U1Sub *m_next;						// +0x04
	U1Sub *m_prev;						// +0x08
};

// ?_bfme_detach@U1Sub@@QAEXXZ
void U1Sub::_bfme_detach(void)
{
	if (m_next)
		m_next->m_prev = m_prev;
	else
		m_target->m_tail = m_prev;

	if (m_prev)
		m_prev->m_next = m_next;
	else
		m_target->m_head = m_next;

	m_next = 0;
	m_prev = 0;
}
