// 0x0075C1C0 -- replace the held reference and publish it to the owner at +0x34.
//
//     test [this+0x34] / je end / AddRef arg / Release [this+0x22c] /
//     store arg / call setReference@Rva0091FC90Owner
//
// AddRef is `inc [arg+4]`; Release is `dec [old+4]` then vtable slot 0 when
// the count hits zero. The owner is only a null-guard: the whole replacement
// is skipped when it is missing. Callee is the landed row at 0x0091FC90.

class Rva0091FC90Reference
{
public:
	virtual void dispose();
	int m_referenceCount;
};

class Rva0091FC90Owner
{
public:
	void setReference(Rva0091FC90Reference *reference);
};

class Gen0075C1C0
{
public:
	void setHeld(Rva0091FC90Reference *reference);

private:
	char m_pad00[0x34];
	Rva0091FC90Owner *m_owner;				// +0x34
	char m_pad38[0x1F4];					// +0x38 .. +0x22B
	Rva0091FC90Reference *m_held;				// +0x22C
};

// @?setHeld@Gen0075C1C0@@QAEXPAVRva0091FC90Reference@@@Z 0x0075C1C0
void Gen0075C1C0::setHeld(Rva0091FC90Reference *reference)
{
	if (m_owner)
	{
		if (reference)
			++reference->m_referenceCount;

		Rva0091FC90Reference *held = m_held;
		if (held)
		{
			if (--held->m_referenceCount == 0)
				held->dispose();
		}

		m_held = reference;
		m_owner->setReference(reference);
	}
}
