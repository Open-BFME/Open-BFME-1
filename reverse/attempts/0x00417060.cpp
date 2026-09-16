// ?rva00417060@Rva00417060@@QBEPAXXZ
// partial score=0.65 date=2026-09-16
// Scratch-only native reconstruction for retail RVA 0x00417060 (99 bytes).
// The names below are address-derived because this probe makes no identity
// claim.  The paired 0x00416FE0 body establishes the table layout and the
// first finder slot; this body uses the next finder slot and an out-parameter.
// cl: /DNDEBUG /MD /EHsc

class Rva00417060Query;
class Rva00417060Entry;
class Rva00417060Parent;

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;

	const Overridable *getFinalOverride() const;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

class Rva00417060Query
{
public:
	virtual void rva00417060QuerySlot00();
	virtual void rva00417060QuerySlot04();
	virtual bool rva00417060QuerySlot08(void **result);
};

class Rva00417060Entry
{
public:
	virtual void rva00417060EntrySlot00();
	virtual void rva00417060EntrySlot04();
	virtual void rva00417060EntrySlot08();
	virtual void rva00417060EntrySlot0c();
	virtual void rva00417060EntrySlot10();
	virtual void rva00417060EntrySlot14();
	virtual void rva00417060EntrySlot18();
	virtual void rva00417060EntrySlot1c();
	virtual void rva00417060EntrySlot20();
	virtual void rva00417060EntrySlot24();
	virtual void rva00417060EntrySlot28();
	virtual Rva00417060Query *rva00417060EntrySlot2c();
};

class Rva00417060Parent : public Overridable
{
public:
	unsigned char m_rva00417060Pad08[0x428];
	void *m_rva00417060Result;
};

class Rva00417060
{
public:
	void *rva00417060() const;

private:
	void *m_rva00417060Head;
	Rva00417060Parent *m_rva00417060Parent;
	unsigned char m_rva00417060Pad08[0x150];
	Rva00417060Entry **m_rva00417060Entries;
};

void *Rva00417060::rva00417060() const
{
	void *result;
	Rva00417060Entry **entry = m_rva00417060Entries;

	if (entry != 0)
	{
		do
		{
			Rva00417060Entry *current = *entry;
			if (current == 0)
				break;

			Rva00417060Query *query = current->rva00417060EntrySlot2c();
			if (query != 0 && query->rva00417060QuerySlot08(&result))
				return result;

			++entry;
		}
		while (entry != 0);
	}

	Rva00417060Parent *parent = m_rva00417060Parent;
	if (parent == 0)
		return parent->m_rva00417060Result;

	if (parent->m_nextOverride != 0)
		parent = (Rva00417060Parent *)parent->m_nextOverride->getFinalOverride();

	return parent->m_rva00417060Result;
}
