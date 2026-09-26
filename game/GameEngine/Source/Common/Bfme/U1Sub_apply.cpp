// cl: /DNDEBUG /MD /EHsc
// Open-BFME: U1Sub::apply, retail 0x005C21D0, 84 bytes.
//
// A subscription move: drop whatever this one is attached to, take the other's
// target, and splice this into that target's list -- head at +0x98, tail at
// +0x9C in the target, next at +0x04 and previous at +0x08 in the link itself.
//
// The body ends by leaving `this' in eax, so it hands back a reference; the
// ledger's harvested name spells the return void, which a call site cannot see.
// The row is claimed under the spelling the bytes support.

class U1CachedHolder;

class U1Target
{
public:
	unsigned char m_unmodelled_000[0x98];
	class U1Sub *m_tail;					// +0x98
	class U1Sub *m_head;					// +0x9C
};

class U1CachedHolder
{
public:
	U1Target *m_target;					// +0x00
};

class U1Sub
{
public:
	U1Sub &apply(U1CachedHolder *other);

	// Shape only: called on this when it is already attached, and named for
	// what it must do before the target is replaced.
	void _bfme_detach(void);				// ILT 0x0002129C

private:
	U1Target *m_target;					// +0x00
	U1Sub *m_next;						// +0x04
	U1Sub *m_prev;						// +0x08
};

U1Sub &U1Sub::apply(U1CachedHolder *other)
{
	if (this != (U1Sub *)other)
	{
		if (m_target)
			_bfme_detach();

		U1Target *target = other->m_target;
		m_target = target;
		if (target)
		{
			m_next = target->m_head;
			m_prev = 0;
			target->m_head = this;
			if (m_next)
				m_next->m_prev = this;
			else
				m_target->m_tail = this;
		}
	}

	return *this;
}
